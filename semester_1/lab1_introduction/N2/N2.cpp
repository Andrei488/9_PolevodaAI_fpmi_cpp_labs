#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");

    int even = 0;
    int odd = 1;
    int n = 0;
    int a = 1;

    std::cout << "Введите число n: ";
    std::cin >> n;

    while (a <= n) {
        if (a % 2 == 0) {
            even = even + a;
        }
        else {
            odd = odd * a;
        }

        a++;
    }

    std::cout << "Сумма четных чисел: " << even << std::endl;
    std::cout << "Произведение нечентных чисел: " << odd;

    return 0;
}