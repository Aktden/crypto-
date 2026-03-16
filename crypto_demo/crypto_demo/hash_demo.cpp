#include "../include/hash_demo.h"
#include "../include/utils.h"
#include <cryptopp/sha.h>
#include <cryptopp/md5.h>
#include <cryptopp/hmac.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <iostream>

std::string HashDemo::computeSHA256(const std::string& data) {
    CryptoPP::SHA256 hash;
    std::string result;

    CryptoPP::StringSource(data, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(result)
            )
        )
    );

    return result;
}

std::string HashDemo::computeSHA1(const std::string& data) {
    CryptoPP::SHA1 hash;
    std::string result;

    CryptoPP::StringSource(data, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(result)
            )
        )
    );

    return result;
}

std::string HashDemo::computeMD5(const std::string& data) {
    CryptoPP::MD5 hash;
    std::string result;

    CryptoPP::StringSource(data, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(result)
            )
        )
    );

    return result;
}

void HashDemo::demonstrateHashing() {
    printSubHeader("Хеширование данных");

    std::string message = "Hello, Crypto++!";
    printInfo("Исходное сообщение: \"" + message + "\"");
    printSeparator();

    SimpleTimer timer("SHA-256");
    std::string sha256 = computeSHA256(message);
    std::cout << "  SHA-256: " << sha256 << std::endl;
    std::cout << "  Длина: " << sha256.length() / 2 << " байт" << std::endl;

    std::string sha1 = computeSHA1(message);
    std::cout << "\n  SHA-1:   " << sha1 << std::endl;
    std::cout << "  Длина: " << sha1.length() / 2 << " байт" << std::endl;

    std::string md5 = computeMD5(message);
    std::cout << "\n  MD5:     " << md5 << std::endl;
    std::cout << "  Длина: " << md5.length() / 2 << " байт" << std::endl;
}

void HashDemo::demonstrateHMAC() {
    printSubHeader("HMAC-SHA256 аутентификация");

    std::string message = "Важное сообщение";
    std::string key = "секретный_ключ";

    printInfo("Сообщение: \"" + message + "\"");
    printInfo("Ключ: \"" + key + "\"");

    CryptoPP::SecByteBlock keyBlock((const byte*)key.data(), key.size());
    std::string hmac;

    CryptoPP::HMAC<CryptoPP::SHA256> hmacObj(keyBlock, keyBlock.size());

    SimpleTimer timer("HMAC-SHA256");
    CryptoPP::StringSource(message, true,
        new CryptoPP::HashFilter(hmacObj,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hmac)
            )
        )
    );

    std::cout << "  HMAC: " << hmac << std::endl;
    printSuccess("Аутентификация создана");
}