#include <iostream>

int main() {
    int count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;
    int count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0;
    int number, temp;

    std::cout << "Write your number: ";
    if (!(std::cin >> number) || number == 0) {
        std::cout << "You entered chepuha! :(\n";
        std::exit(1);
    }

    temp = number;
    while (temp > 0) {
        int digit = temp % 10;

        if (digit == 0) count0++;
        if (digit == 1) count1++;
        if (digit == 2) count2++;
        if (digit == 3) count3++;
        if (digit == 4) count4++;
        if (digit == 5) count5++;
        if (digit == 6) count6++;
        if (digit == 7) count7++;
        if (digit == 8) count8++;
        if (digit == 9) count9++;

        temp = temp / 10;
    }

    temp = number;
    int result = 0;
    int multiplier = 1;

    while (temp > 0) {
        int digit = temp % 10;

        if (digit == 0 && count0 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 1 && count1 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 2 && count2 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 3 && count3 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 4 && count4 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 5 && count5 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 6 && count6 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 7 && count7 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 8 && count8 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }
        if (digit == 9 && count9 % 2 != 0) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }

        temp = temp / 10;
    }

    std::cout << "Result: " << result << std::endl;
}