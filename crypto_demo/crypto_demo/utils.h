#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cryptopp/secblock.h>

// Цвета для консоли
void printHeader(const std::string& title);
void printSubHeader(const std::string& title);
void printSuccess(const std::string& message);
void printInfo(const std::string& message);
void printSeparator();

// Утилиты для преобразования
std::string bytesToHex(const byte* data, size_t len);
std::string bytesToHex(const CryptoPP::SecByteBlock& data);
std::string bytesToBase64(const std::string& data);

// Простой таймер
class SimpleTimer {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::string name;
public:
    SimpleTimer(const std::string& n);
    ~SimpleTimer();
    double elapsedMs();
};

#endif