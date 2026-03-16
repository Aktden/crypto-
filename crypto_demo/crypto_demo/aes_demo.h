#pragma once
#ifndef AES_DEMO_H
#define AES_DEMO_H

#include <string>
#include <cryptopp/secblock.h>

struct AESResult {
    std::string ciphertext;
    std::string decrypted;
    bool success;
};

class AESDemo {
private:
    CryptoPP::SecByteBlock generateKey();
    CryptoPP::SecByteBlock generateIV();

public:
    AESResult encryptAES(const std::string& plaintext);
    void demonstrateAES();
    void demonstrateAESWithPassword();
};

#endif