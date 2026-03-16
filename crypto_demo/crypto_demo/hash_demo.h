#pragma once
#ifndef HASH_DEMO_H
#define HASH_DEMO_H

#include <string>

class HashDemo {
public:
    std::string computeSHA256(const std::string& data);
    std::string computeSHA1(const std::string& data);
    std::string computeMD5(const std::string& data);

    void demonstrateHashing();
    void demonstrateHMAC();
};

#endif