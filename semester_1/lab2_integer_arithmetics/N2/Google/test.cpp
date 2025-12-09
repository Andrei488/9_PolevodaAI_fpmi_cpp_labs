#include "gtest/gtest.h"
#include "pch.cpp"
#include "pch.h"

//cl /EHsc test.cpp pch.cpp && test.exe

TEST(InputValidationTest, ValidPositiveNumbers) {
    EXPECT_TRUE(isValidInput(1));
    EXPECT_TRUE(isValidInput(100));
    EXPECT_TRUE(isValidInput(12345));
    EXPECT_TRUE(isValidInput(999999999));
}

TEST(InputValidationTest, InvalidNonPositiveNumbers) {
    EXPECT_FALSE(isValidInput(0));
    EXPECT_FALSE(isValidInput(-1));
    EXPECT_FALSE(isValidInput(-100));
    EXPECT_FALSE(isValidInput(-12345));
}

TEST(DigitCountingTest, CountUniqueDigits) {
    int digits[10] = { 0 };
    countDigits(123, digits);
    EXPECT_EQ(digits[0], 0);
    EXPECT_EQ(digits[1], 1);
    EXPECT_EQ(digits[2], 1);
    EXPECT_EQ(digits[3], 1);
}

TEST(DigitCountingTest, CountRepeatedDigits) {
    int digits[10] = { 0 };
    countDigits(112233, digits);
    EXPECT_EQ(digits[1], 2);
    EXPECT_EQ(digits[2], 2);
    EXPECT_EQ(digits[3], 2);
}

TEST(DigitCountingTest, CountTripleDigits) {
    int digits[10] = { 0 };
    countDigits(111222, digits);
    EXPECT_EQ(digits[1], 3);
    EXPECT_EQ(digits[2], 3);
}

TEST(DigitCountingTest, CountWithZeros) {
    int digits[10] = { 0 };
    countDigits(100, digits);
    EXPECT_EQ(digits[0], 2);
    EXPECT_EQ(digits[1], 1);
}

TEST(DigitCountingTest, CountSameDigits) {
    int digits[10] = { 0 };
    countDigits(999, digits);
    EXPECT_EQ(digits[9], 3);
}

TEST(NumberProcessingTest, SingleDigitNumbers) {
    EXPECT_EQ(processNumber(1), 1);
    EXPECT_EQ(processNumber(5), 5);
    EXPECT_EQ(processNumber(9), 9);
    EXPECT_EQ(processNumber(0), 0);
}

TEST(NumberProcessingTest, AllDigitsOddCount) {
    EXPECT_EQ(processNumber(123), 123);
    EXPECT_EQ(processNumber(13579), 13579);
    EXPECT_EQ(processNumber(111), 111);
    EXPECT_EQ(processNumber(33333), 33333);
    EXPECT_EQ(processNumber(111222333), 111222333);
}

TEST(NumberProcessingTest, AllDigitsEvenCount) {
    EXPECT_EQ(processNumber(11), 0);
    EXPECT_EQ(processNumber(1122), 0);
    EXPECT_EQ(processNumber(112233), 0);
    EXPECT_EQ(processNumber(123321), 0);
    EXPECT_EQ(processNumber(1221), 0);
    EXPECT_EQ(processNumber(1122334455), 0);
}

TEST(NumberProcessingTest, OrderPreservation) {
    EXPECT_EQ(processNumber(312), 312);
    EXPECT_EQ(processNumber(21133), 2);
    EXPECT_EQ(processNumber(1321), 32);
    EXPECT_EQ(processNumber(12341), 234);
    EXPECT_EQ(processNumber(551122), 0);
    EXPECT_EQ(processNumber(51212), 5);
}

TEST(NumberProcessingTest, RepeatedDigits) {
    EXPECT_EQ(processNumber(111), 111);
    EXPECT_EQ(processNumber(1111), 0);
    EXPECT_EQ(processNumber(11111), 11111);
    EXPECT_EQ(processNumber(222222), 0);
    EXPECT_EQ(processNumber(3333333), 3333333);
}

TEST(NumberProcessingTest, LargeNumbers) {
    EXPECT_EQ(processNumber(123456789), 123456789);
    EXPECT_EQ(processNumber(987654321), 987654321);
    EXPECT_EQ(processNumber(112233445566778899), 0);
    EXPECT_EQ(processNumber(135792468), 135792468);
}