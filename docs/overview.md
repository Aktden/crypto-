#  Обзор проекта

## О библиотеке Crypto++

**Crypto++** (CryptoPP) — бесплатная библиотека с открытым исходным кодом для криптографии на C++, созданная **Wei Dai** в 1995 году. Распространяется под лицензией **Boost Software License**.

- Официальный сайт: https://cryptopp.com
- GitHub: https://github.com/weidai11/cryptopp



## Архитектура библиотеки

Crypto++ построена на концепции **пайплайнов (filter chains)** — данные последовательно проходят через цепочку объектов-фильтров:
```
StringSource → StreamTransformationFilter → StringSink
```

Это позволяет гибко комбинировать алгоритмы: шифрование, хеширование, кодирование в одной цепочке.



## Что реализовано в проекте

### Модуль HashDemo

Демонстрирует вычисление хеш-дайджестов и аутентификацию сообщений.

| Алгоритм | Размер дайджеста | Статус |
|---|---|---|
| SHA-256 | 256 бит (32 байта) |  Безопасен |
| SHA-1 | 160 бит (20 байт) |  Устарел |
| MD5 | 128 бит (16 байт) |  Устарел |
| HMAC-SHA256 | 256 бит (32 байта) |  Безопасен |

### Модуль AESDemo

Демонстрирует симметричное шифрование и деривацию ключей.

| Функция | Описание |
|---|---|
| AES-128 CBC | Шифрование со случайным ключом и IV |
| PBKDF2-HMAC-SHA256 | Деривация ключа из пароля (10 000 итераций) |

### Утилиты (Utils)

| Функция | Описание |
|---|---|
| `bytesToHex()` | Перевод байт в HEX-строку |
| `bytesToBase64()` | Перевод байт в Base64-строку |
| `SimpleTimer` | Замер времени выполнения операций |
| Цветной вывод | ANSI-цвета в консоли |


## Структура проекта
```
crypto_demo/
├── include/
│   ├── aes_demo.h
│   ├── hash_demo.h
│   └── utils.h
├── src/
│   ├── main.cpp
│   ├── aes_demo.cpp
│   ├── hash_demo.cpp
│   └── utils.cpp
├── CMakeLists.txt
└── crypto_demo.vcxproj
```


## Используемые компоненты Crypto++

| Компонент | Заголовок | Назначение |
|---|---|---|
| AES | `<cryptopp/aes.h>` | Блочный шифр |
| CBC Mode | `<cryptopp/modes.h>` | Режим шифрования |
| SHA-256 / SHA-1 | `<cryptopp/sha.h>` | Хеш-функции |
| MD5 | `<cryptopp/md5.h>` | Хеш-функция |
| HMAC | `<cryptopp/hmac.h>` | Аутентификация |
| PBKDF2 | `<cryptopp/pwdbased.h>` | Деривация ключа |
| AutoSeededRandomPool | `<cryptopp/osrng.h>` | Генерация ключей |
| HexEncoder / Base64Encoder | `<cryptopp/hex.h>`, `<cryptopp/base64.h>` | Кодирование |
| SecByteBlock | `<cryptopp/secblock.h>` | Безопасный буфер |
