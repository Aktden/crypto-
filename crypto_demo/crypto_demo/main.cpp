#include "../include/hash_demo.h"
#include "../include/aes_demo.h"
#include "../include/utils.h"
#include <iostream>

int main() {
    try {
        printHeader("ДЕМОНСТРАЦИЯ CRYPTO++");

        std::cout << "\nВерсия Crypto++: "
            << CryptoPP::CRYPTOPP_VERSION / 100 << "."
            << (CryptoPP::CRYPTOPP_VERSION % 100) / 10 << "."
            << CryptoPP::CRYPTOPP_VERSION % 10
            << std::endl;

        // Демонстрация хеширования
        HashDemo hashDemo;
        hashDemo.demonstrateHashing();
        hashDemo.demonstrateHMAC();

        // Демонстрация AES
        AESDemo aesDemo;
        aesDemo.demonstrateAES();
        aesDemo.demonstrateAESWithPassword();

        printHeader("ПРОГРАММА ЗАВЕРШЕНА");
        printSuccess("Все операции выполнены успешно!");

    }
    catch (const std::exception& e) {
        std::cerr << "\n Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}