#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    int number = 0;
    int n = 5;
    int num[6];
    int a = 0;
    int first3 = 0;
    int second3 = 0;

    std::cout << "Введите число для проверки на то, является ли оно счастливым: ";
    std::cin >> number;

    while (n >= 0) {
        a = number % 10;
        num[n] = a;
        number = number / 10;

        n = n - 1;
    }

    first3 = num[0] + num[1] + num[2];
    second3 = num[3] + num[4] + num[5];

    if (first3 == second3) {
        std::cout << "Чиcло является счастливым";
    }
    else {
        std::cout << "Число не является счастливым";
    }

    return 0;
}
