// Basics.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <format>
#include <print>
#include <cmath> // ie. <math.h> via la stdlib C++

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
    std::cout << std::endl;
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

    // C++ 11: auto
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
    std::cout << std::endl;
}

void playWithIntegers_operators() {
    std::cout << "******** Play with integers (operators) ********" << std::endl;
    std::uint32_t x = 345;
    std::uint32_t y = 678;

    // Calcul homogène => résultat même type
    // auto = std::uint32_t
    auto z = (x + y) * (x - y) / 2; // see also: unary "-" for signed integers
    auto q = x / 7;
    auto r = x % 7;

    // conv implicite (integers)
    // auto = std::uint64_t
    std::uint64_t w = 5000000000;
    auto ww = w + x;

    // conv implicite (integer => floating numbers)
    // auto = float (f), double (ff)
    auto f = x * 2.f;
    auto ff = x * 2.;

    std::cout << "Division entière: q = " << q << " ; r = " << r << std::endl;

    // operators in-place
    ++x;
    x++; // !! copy for big objects, pour les petits OK
    --x;
    x--;
    x += 5;
    x -= 2;
    x *= 2;
    x /= 3;

    // operators 'bitwise'
    std::uint8_t buffer = 5;
    std::println("{0:0d} - {0:02x} - {0:08b}", buffer);
    buffer = buffer << 1;
    std::println("{0:0d} - {0:02x} - {0:08b}", buffer);
    buffer = (buffer >> 2) | 1;  // or 0b00000001
    std::println("{0:0d} - {0:02x} - {0:08b}", buffer);
    std::println("{0:0d} - {0:02x} - {0:08b}", (buffer | 0x80) & 0x0f);
    buffer = 5;
    std::println("{0:0d} - {0:02x} - {0:08b}", buffer ^ 0xff);
    buffer = 5;
    std::println("{0:0d} - {0:02x} - {0:08b}", buffer);
    buffer = ~buffer;
    std::println("{0:0d} - {0:02x} - {0:08b}", buffer);
    std::cout << std::endl;
}

void playWithFloats_operators() {
    std::cout << "******** Play with floats (operators) ********" << std::endl;
    double x = 345.0;

    auto qf = x / 7;
    auto qi = std::floor(x / 7);
    auto r = x - qi * 7; // x % 7;
    std::cout << "Division flottante: q = " << qf << std::endl;
    std::u8string libelle = u8"Division entière";
    std::print("{}: q = {} ; r = {}\n",  reinterpret_cast<const char*>(libelle.c_str()),  qi, r);
    std::cout << std::endl;
}

void playWithComparisons() {
    std::cout << "******** Play with comparisons ********" << std::endl;
    bool q = true;
    std::cout 
        << q << " (as int), "
        << std::boolalpha  // manipulateur de flot: https://cppreference.com/cpp/header/ios
        << q << " (as bool), "
        << std::noboolalpha
        << q << " (as int), "
        << " size " << sizeof(q) << " byte" 
        << std::endl;

    std::int32_t nbPerson = 350;
    double temperature = 42.5;

    // comparisons before C++20
    std::cout << std::boolalpha
        << " == " << (nbPerson == 350) << std::endl
        << " != " << (nbPerson != 350) << std::endl
        << " < " << (nbPerson < 350) << std::endl
        << " <= " << (nbPerson <= 350) << std::endl
        << " > " << (nbPerson > 350) << std::endl
        << " >= " << (nbPerson >= 350) << std::endl
        ;

    // C++20+ : 'starship' operator ie three way comparison operator
    auto cmp1 = nbPerson <=> 350;     // std:strong_ordering
    auto cmp2 = temperature <=> 40.0; // std::partial_ordering
    temperature = std::nan("1"); // NaN
    auto cmp3 = temperature <=> 40.0;

    std::cout
        << "comparaison (int) < : " << std::is_lt(cmp1) << std::endl  // is_gt, is_lteq, is_gteq, is_eq, is_neq
        << "comparaison (double) < : " << std::is_lt(cmp2) << std::endl
        << "comparaison (double) not defined (2): " << (cmp2 == std::partial_ordering::unordered) << std::endl
        << "comparaison (double) not defined (3): " << (cmp3 == std::partial_ordering::unordered) << std::endl
        ;

}

int main()
{
    playWithIntegers_sc1();
    playWithIntegers_sc2();
    playWithIntegers_operators();
    playWithFloats_operators();
    playWithComparisons();
    return EXIT_SUCCESS; 
    // or 
    // return EXIT_FAILURE;
}