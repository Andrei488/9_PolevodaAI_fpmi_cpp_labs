#include "number_processor.h"
#include <iostream>
#include <cassert>

void TestIsValidInput() {
    std::cout << "TestIsValidInput... ";

    assert(isValidInput(1) == true);
    assert(isValidInput(100) == true);
    assert(isValidInput(12345) == true);
    assert(isValidInput(999999999) == true);
    assert(isValidInput(0) == false);
    assert(isValidInput(-1) == false);
    assert(isValidInput(-100) == false);
    assert(isValidInput(-12345) == false);

    std::cout << "PASSED\n";
}

void TestCountDigits() {
    std::cout << "TestCountDigits... ";

    int digits[10] = { 0 };

    countDigits(123, digits);
    assert(digits[0] == 0);
    assert(digits[1] == 1);
    assert(digits[2] == 1);
    assert(digits[3] == 1);

    for (int i = 0; i < 10; i++) digits[i] = 0;
    countDigits(112233, digits);
    assert(digits[1] == 2);
    assert(digits[2] == 2);
    assert(digits[3] == 2);

    for (int i = 0; i < 10; i++) digits[i] = 0;
    countDigits(111222, digits);
    assert(digits[1] == 3);
    assert(digits[2] == 3);

    for (int i = 0; i < 10; i++) digits[i] = 0;
    countDigits(100, digits);
    assert(digits[0] == 2);
    assert(digits[1] == 1);

    for (int i = 0; i < 10; i++) digits[i] = 0;
    countDigits(999, digits);
    assert(digits[9] == 3);

    std::cout << "PASSED\n";
}

void TestSingleDigitNumbers() {
    std::cout << "TestSingleDigitNumbers... ";

    assert(processNumber(1) == 1);
    assert(processNumber(5) == 5);
    assert(processNumber(9) == 9);
    assert(processNumber(0) == 0);

    std::cout << "PASSED\n";
}

void TestAllDigitsOddCount() {
    std::cout << "TestAllDigitsOddCount... ";

    assert(processNumber(123) == 123);
    assert(processNumber(13579) == 13579);
    assert(processNumber(111) == 111);
    assert(processNumber(33333) == 33333);
    assert(processNumber(111222333) == 111222333);

    std::cout << "PASSED\n";
}

void TestAllDigitsEvenCount() {
    std::cout << "TestAllDigitsEvenCount... ";

    assert(processNumber(11) == 0);
    assert(processNumber(1122) == 0);
    assert(processNumber(112233) == 0);
    assert(processNumber(123321) == 0);
    assert(processNumber(1221) == 0);
    assert(processNumber(1122334455) == 0);

    std::cout << "PASSED\n";
}

void TestOrderPreservation() {
    std::cout << "TestOrderPreservation... ";

    assert(processNumber(312) == 312);
    assert(processNumber(21133) == 2);
    assert(processNumber(1321) == 32);
    assert(processNumber(12341) == 234);
    assert(processNumber(551122) == 0);
    assert(processNumber(51212) == 5);

    std::cout << "PASSED\n";
}

void TestRepeatedDigits() {
    std::cout << "TestRepeatedDigits... ";

    assert(processNumber(111) == 111);
    assert(processNumber(1111) == 0);
    assert(processNumber(11111) == 11111);
    assert(processNumber(222222) == 0);
    assert(processNumber(3333333) == 3333333);

    std::cout << "PASSED\n";
}

void TestLargeNumbers() {
    std::cout << "TestLargeNumbers... ";

    assert(processNumber(123456789) == 123456789);
    assert(processNumber(987654321) == 987654321);
    assert(processNumber(112233445566778899) == 0);
    assert(processNumber(135792468) == 135792468);

    std::cout << "PASSED\n";
}

int main() {
    std::cout << "=== STARTING COMPREHENSIVE UNIT TESTS ===\n\n";

    TestIsValidInput();
    TestCountDigits();
    TestSingleDigitNumbers();
    TestAllDigitsOddCount();
    TestAllDigitsEvenCount();
    TestOrderPreservation();
    TestRepeatedDigits();
    TestLargeNumbers();

    std::cout << "\n=== ALL TESTS PASSED ===\n";
    return 0;
}