#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    int number = 0;
    int n = 3;
    int num[4];
    int a = 0;

    std::cout << "Введите число для проверки на то, является ли оно палиндромом: ";
    std::cin >> number;

    while (n >= 0) {
        a = number % 10;
        num[n] = a;
        number = number / 10;
        n = n - 1;
    }
    
    if (num[0] == num[3] && num[2] == num[1]) {
        std::cout << "Число является палиндромом";
    }
    else {
        std::cout << "Число не является палиндромом";
    }

    return 0;
}
