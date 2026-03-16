#include "../include/aes_demo.h"
#include "../include/utils.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>
#include <iostream>

CryptoPP::SecByteBlock AESDemo::generateKey() {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    rng.GenerateBlock(key, key.size());
    return key;
}

CryptoPP::SecByteBlock AESDemo::generateIV() {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    rng.GenerateBlock(iv, iv.size());
    return iv;
}

AESResult AESDemo::encryptAES(const std::string& plaintext) {
    AESResult result;

    try {
        auto key = generateKey();
        auto iv = generateIV();

        printInfo("Ключ: " + bytesToHex(key));
        printInfo("IV: " + bytesToHex(iv));

        // Шифрование
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;
        enc.SetKeyWithIV(key, key.size(), iv);

        SimpleTimer timer("AES шифрование");
        CryptoPP::StringSource(plaintext, true,
            new CryptoPP::StreamTransformationFilter(enc,
                new CryptoPP::StringSink(result.ciphertext)
            )
        );

        // Дешифрование
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec;
        dec.SetKeyWithIV(key, key.size(), iv);

        CryptoPP::StringSource(result.ciphertext, true,
            new CryptoPP::StreamTransformationFilter(dec,
                new CryptoPP::StringSink(result.decrypted)
            )
        );

        result.success = (result.decrypted == plaintext);

    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        result.success = false;
    }

    return result;
}

void AESDemo::demonstrateAES() {
    printSubHeader("AES-128 CBC шифрование");

    std::string plaintext = "Секретное сообщение для AES!";
    printInfo("Исходный текст: " + plaintext);
    printSeparator();

    auto result = encryptAES(plaintext);

    if (result.success) {
        std::cout << "  Зашифровано (hex): "
            << bytesToHex((byte*)result.ciphertext.data(), result.ciphertext.size())
            << std::endl;
        std::cout << "  Зашифровано (base64): "
            << bytesToBase64(result.ciphertext)
            << std::endl;
        std::cout << "  Размер: " << result.ciphertext.size() << " байт" << std::endl;
        std::cout << "  Расшифровано: " << result.decrypted << std::endl;
        printSuccess("Шифрование и дешифрование успешны!");
    }
}

void AESDemo::demonstrateAESWithPassword() {
    printSubHeader("Шифрование с паролем (PBKDF2)");

    std::string plaintext = "Данные, защищенные паролем";
    std::string password = "MyPassword123";

    printInfo("Исходный текст: " + plaintext);
    printInfo("Пароль: " + password);

    try {
        // Генерируем соль
        CryptoPP::AutoSeededRandomPool rng;
        CryptoPP::SecByteBlock salt(16);
        rng.GenerateBlock(salt, salt.size());

        // Генерируем ключ из пароля
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf2;

        pbkdf2.DeriveKey(key, key.size(), 0,
            (byte*)password.data(), password.size(),
            salt, salt.size(), 10000);

        printInfo("Соль: " + bytesToHex(salt));
        printInfo("Сгенерированный ключ: " + bytesToHex(key));

        // Шифруем
        auto iv = generateIV();
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;
        enc.SetKeyWithIV(key, key.size(), iv);

        std::string ciphertext;
        CryptoPP::StringSource(plaintext, true,
            new CryptoPP::StreamTransformationFilter(enc,
                new CryptoPP::StringSink(ciphertext)
            )
        );

        std::cout << "  Зашифровано: "
            << bytesToHex((byte*)ciphertext.data(), ciphertext.size())
            << std::endl;

        printSuccess("Шифрование с паролем выполнено");

    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}