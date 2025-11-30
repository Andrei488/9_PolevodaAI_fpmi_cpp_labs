#include "number_processor.h"
#include <iostream>
#include <vector>

bool isValidInput(int64_t number) {
    return number > 0;
}

void countDigits(int64_t number, int digit_count[10]) {
    int64_t temp = number;
    while (temp > 0) {
        digit_count[temp % 10]++;
        temp /= 10;
    }
}

int processNumber(int64_t number) {
    int digit_count[10] = { 0 };
    countDigits(number, digit_count);

    std::vector<int> digits;
    int64_t temp = number;

    while (temp > 0) {
        digits.insert(digits.begin(), temp % 10);
        temp /= 10;
    }

    int result = 0;
    for (int digit : digits) {
        if (digit_count[digit] % 2 != 0) {
            result = result * 10 + digit;
        }
    }

    return result;
}

int64_t getValidatedInput() {
    int64_t number;
    std::cout << "Write your number: ";

    if (!(std::cin >> number)) {
        throw "Invalid input";
    }

    if (!isValidInput(number)) {
        throw "Number must be positive";
    }

    return number;
}