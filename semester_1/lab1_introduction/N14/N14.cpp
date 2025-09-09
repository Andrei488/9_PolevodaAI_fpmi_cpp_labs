#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    long long number = 0;
    int sum = 0;

    std::cout << "Введите число для суммирования его цифр: ";
    std::cin >> number;

    int temp = number;
    while (number > 0) {
        temp = number % 10;
        sum = sum + temp;
        number = number / 10;
    }

    std::cout << "Сумма всех цифр числа равна: " << sum;

    return 0;
}