// N17_Static.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <random>

int main()
{
    setlocale(LC_ALL, "Russian");

    int array[10000] = { 0 };

    int n;
    std::cout << "Введите желаемую длину массива: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Длина массива должна быть целым, положительным числом \n";
        return 1;
    }

    int enter = 0;
    std::cout << "Как бы вы хотели заполнить массив? Введите '1' для заполнения вручную и '0' для рандомного заполнения: ";
    if (!(std::cin >> enter) || !(enter == 0 || enter == 1)) {
        std::cout << "Введите либо 1, либо 0 \n";
        return 1;
    }

    switch (enter) {
    case 0: {
        std::random_device rd;
        std::mt19937 gen(rd());

        int min = 0, max = 0;

        std::cout << "Введите минимальное значение и максимальное значение: ";
        if (!(std::cin >> min >> max)) {
            std::cout << "Введите числа в рамках переменной int \n";
            return 1;
        }

        if (min > max) {
            std::cout << "Ошибка: минимальное значение больше максимального!" << std::endl;
            return 1;
        }

        std::uniform_int_distribution<int> dist(min, max);

        int i = 0;
        while (i < n) {
            array[i] = dist(gen);
            i++;
        }

        std::cout << std::endl;

        break;
    }
    case 1: {
        int i = 0;

        while (i < n) {
            std::cout << "Введите " << i + 1 << " член массива: ";
            if (!(std::cin >> array[i])) {
                std::cout << "Введите целое число \n";
                return 1;
            }
            i++;
        }

        std::cout << std::endl;

        break;
    }
    default: {
        std::cout << "Ошибка ввода" << std::endl;
        break;
    }
    }

    int i = 0;
    std::cout << "Полученный массив: { ";
    while (i < n) {
        std::cout << array[i] << " ";
        i++;
    }
    std::cout << "}" << std::endl << "\n";

    int M = array[0];
    i = 1;
    while (i < n) {
        if (array[i] > M) {
            M = array[i];
        }
        i++;
    }
    i = 0;
    std::cout << "ID элемента с максимальным значением: ";
    while (i < n) {
        if (array[i] == M) {
            std::cout << i << " ";
        }
        i++;
    }

    std::cout << std::endl;

    i = 0;
    int nat = 1;
    while (i < n) {
        if (array[i] == nat) {
            nat++;
            i = 0;
        }
        else {
            i++;
        }
    }

    std::cout << "Наименьшее натуральное число, отсутствующее в массиве: " << nat << std::endl << "\n";

    int border;
    std::cout << "Введите число, числа больше которого будут отображаться в начале: ";
    if (!(std::cin >> border)) {
        std::cout << "Введите целое число \n";
        return 1;
    }

    std::cout << "Получили преобразованный массив: { ";
    for (i = 0; i < n; i++) {
        if (array[i] > border) {
            std::cout << array[i] << " ";
        }
    }
    for (i = 0; i < n; i++) {
        if (array[i] <= border) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << "}" << std::endl;
}
