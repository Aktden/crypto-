cmake_minimum_required(VERSION 3.10)
project(crypto_demo)

set(CMAKE_CXX_STANDARD 17)

# Находим библиотеку Crypto++
find_package(Cryptopp REQUIRED)

# Добавляем исполняемый файл
add_executable(crypto_demo
    src/main.cpp
    src/utils.cpp
    src/hash_demo.cpp
    src/aes_demo.cpp
)

# Подключаем заголовочные файлы
target_include_directories(crypto_demo PRIVATE include)

# Линкуем с Crypto++
target_link_libraries(crypto_demo cryptopp-static)