#include <iostream>
#include <string>

void inputNumber(std::string& num) {
    std::cout << "Введите число для сложения: ";
    getline(std::cin, num);
}

void calculatingSum(const std::string& num1, const std::string& num2, std::string& sum, int length) {
    int temp = 0;

    for (int i = length - 1; i >= 0; i--) {
        int a = num1[i] - '0';
        int b = num2[i] - '0';

        int total = a + b + temp;

        if (total >= 10) {
            sum[i] = (total % 10) + '0';
            temp = 1;
        }
        else {
            sum[i] = total + '0';
            temp = 0;
        }
    }

    if (temp > 0) {
        sum = "1" + sum;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string num1, num2, sum;

    inputNumber(num1);
    inputNumber(num2);

    int length = num1.length();
    sum = num1;

    calculatingSum(num1, num2, sum, length);

    std::cout << "Результат: " << sum << std::endl;

    return 0;
}
