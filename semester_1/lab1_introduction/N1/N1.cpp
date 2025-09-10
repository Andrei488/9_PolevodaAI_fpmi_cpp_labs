#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");

    int a, b, d;

    std::cout << "Введите число a: ";
    std::cin >> a;

    std::cout << "Введите число b: ";
    std::cin >> b;

    std::cout << "Введите число d: ";
    std::cin >> d;

    if (b > a) {
        while (a + d <= b) {
            if (a % 3 == 0) {
                std::cout << a << " ";
                a = a + d;
            }
            else {
                a = a + d;
            }
        }
    }
    else {
        while (b + d <= a) {
            if (a % 3 == 0) {
                if (!a== 0) {
                    std::cout << a << " ";
                }
                a = a + d;
            }
            else {
                a = a + d;
            }
        }
    }

    return 0;
}