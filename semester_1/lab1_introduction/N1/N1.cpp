#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");

    int a, b, d;

    std::cout << "Введите числа a, b, d: ";
    if (!(std::cin >> a >> b >> d)) {
        std::cout << "Neverni vvod";
        std::exit(52);
    }

    while (a + d <= b) {
            if (a % 3 == 0) {
                std::cout << a << " ";
                a = a + d;
            }
            else {
                a = a + d;
            }
    }

    return 0;
}