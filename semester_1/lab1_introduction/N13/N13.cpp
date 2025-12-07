#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");

    int n = 0;
    int i = 2;

    std::cout << "Введите кол-во чисел Фибоначчи для вывода: ";
    std::cin >> n;

    int* fib = new int[n];

    fib[0] = 0;
    fib[1] = 1;

    std::cout << fib[0] << ", " << fib[1] << ", ";

    while (i < n) {
        fib[i] = fib[i - 2] + fib[i - 1];
        std::cout << fib[i] << ", ";
        i = i + 1;
    }

    return 0;
}