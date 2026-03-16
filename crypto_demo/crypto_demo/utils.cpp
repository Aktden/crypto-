#include "../include/utils.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>

// ANSI цвета
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string CYAN = "\033[36m";
const std::string BOLD = "\033[1m";

void printHeader(const std::string& title) {
    std::cout << "\n" << BOLD << BLUE << std::string(50, '=') << RESET << std::endl;
    std::cout << BOLD << CYAN << "  🔐 " << title << RESET << std::endl;
    std::cout << BOLD << BLUE << std::string(50, '=') << RESET << std::endl;
}

void printSubHeader(const std::string& title) {
    std::cout << "\n" << BOLD << YELLOW << "  📌 " << title << RESET << std::endl;
    std::cout << YELLOW << std::string(30, '-') << RESET << std::endl;
}

void printSuccess(const std::string& message) {
    std::cout << GREEN << "  ✅ " << message << RESET << std::endl;
}

void printInfo(const std::string& message) {
    std::cout << CYAN << "  ℹ️  " << message << RESET << std::endl;
}

void printSeparator() {
    std::cout << std::string(40, '-') << std::endl;
}

std::string bytesToHex(const byte* data, size_t len) {
    std::string hex;
    CryptoPP::StringSource(data, len, true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(hex)
        )
    );
    return hex;
}

std::string bytesToHex(const CryptoPP::SecByteBlock& data) {
    return bytesToHex(data.data(), data.size());
}

std::string bytesToBase64(const std::string& data) {
    std::string base64;
    CryptoPP::StringSource(data, true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink(base64)
        )
    );
    return base64;
}

SimpleTimer::SimpleTimer(const std::string& n) : name(n) {
    start = std::chrono::high_resolution_clock::now();
}

SimpleTimer::~SimpleTimer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "  ⏱️  " << name << ": " << duration.count() / 1000.0 << " ms" << std::endl;
}

double SimpleTimer::elapsedMs() {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
}