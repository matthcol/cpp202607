// Basics.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <format>
#include <print>

void playWithIntegers_sc1() {
    std::cout << "******** Play with integers ********" << std::endl;
    unsigned int xu32 = 3000000000;
    int x32 = 14;
    long x64 = 9000000000000000000;
    long long xl64 = 9000000000000000000;
    std::cout << xu32 << std::endl
        << x32 << std::endl
        << x64 << std::endl
        << xl64 << std::endl;
}

void playWithIntegers_sc2() {
    std::cout << "******** Play with integers (2) ********" << std::endl;
    std::uint8_t xu8 = 255;
    std::uint32_t xu32 = 3000000000;
    std::int32_t x32 = 14;
    std::int64_t x64 = 9000000000000000000;
    std::uint64_t xl64 = 9000000000000000000;
    std::cout
        //<< ((std::uint16_t) xu8) << "(" << sizeof(xu8) << ")" << std::endl
        << static_cast<uint16_t>(xu8) << "(" << sizeof(xu8) << ")" << std::endl
        << xu32 << "(" << sizeof(xu32) << ")" << std::endl
        << x32 << "(" << sizeof(x32) << ")" << std::endl
        << x64 << "(" << sizeof(x64) << ")" << std::endl
        << xl64 << "(" << sizeof(xl64) << ")" << std::endl;
    // C++20: https://cppreference.com/cpp/utility/format/spec
    std::cout << "With std::format function" << std::endl
        << std::format(" - {} ({})\n", xu8, sizeof(xu8))
        << std::format(" - {} ({})\n", xu32, sizeof(xu32))
        << std::format(" - {0} - {0:0x} - {0:0b} ({1})\n", xl64, sizeof(xl64))
        << std::endl
    ;

    // C++23: print
    std::println(
        "With std::print function:\n - decimal: {0}\n - hexa: {0:0x}\n - binary: {0:0b}\n - size: {1}", 
        xl64, 
        sizeof(xl64)
    );

    // C++ : auto
    auto minUint8 = std::numeric_limits<std::uint8_t>::min();
    auto maxUint8 = std::numeric_limits<std::uint8_t>::max();
    auto minInt8 = std::numeric_limits<std::int8_t>::min();
    auto maxInt8 = std::numeric_limits<std::int8_t>::max();
    auto minUint64 = std::numeric_limits<std::uint64_t>::min();
    auto maxUint64 = std::numeric_limits<std::uint64_t>::max();
    auto minInt64 = std::numeric_limits<std::int64_t>::min();
    auto maxInt64 = std::numeric_limits<std::int64_t>::max();
    std::cout
        << "* limits uint8: " << static_cast<uint16_t>(minUint8)
        << "   - " << static_cast<uint16_t>(maxUint8) << std::endl
        << "* limits int8: " << static_cast<int16_t>(minInt8)
        << "   - " << static_cast<int16_t>(maxInt8) << std::endl
        << "* limits uint64: " << minUint64
        << "   - " << maxUint64 << std::endl
        << "* limits int64: " << minInt64
        << "   - " << maxInt64 << std::endl
        ;
}

int main()
{
    playWithIntegers_sc1();
    playWithIntegers_sc2();
    return EXIT_SUCCESS; 
    // or 
    // return EXIT_FAILURE;
}