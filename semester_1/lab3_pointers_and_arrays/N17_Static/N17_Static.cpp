// N17_Static.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <random>

int main()
{
    setlocale(LC_ALL, "Russian");

    int array[10] = {0};
    std::cout << "Default: array[10]\n";

    int enter = 0;
    std::cout << "Как бы вы хотели заполнить массив? Введите '1' для заполнения вручную и '0' для рандомного заполнения: ";
    if (!(std::cin >> enter) || !(enter == 0 || enter == 1) ) {
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
        while (i < 10) {
            array[i] = dist(gen);
            i++;
        }

        std::cout << std::endl;

        break;
    }
    case 1: {
        int i = 0;

        while (i < 10) {
            std::cout << "Введите " << i << " член массива: ";
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
    while (i < 10) {
        std::cout << array[i] << " ";
        i++;
    }
    std::cout << "}" << std::endl << "\n";

    int M = array[0];
    i = 1;
    while (i < 10) {
        if (array[i] > M) {
            M = array[i];
        }
        i++;
    }
    i = 0;
    std::cout << "ID элемента с максимальным значением: ";
    while (i < 10) {
        if (array[i] == M) {
            std::cout << i << " ";
        }
        i++;
    }

    std::cout << std::endl;

    i = 1;
    bool loop = 1;
    for (;loop ; i++) {
        if (i != array[0] && i != array[1] && i != array[2] && i != array[3] && i != array[4] && i != array[5] && i != array[6] && i != array[7] && i != array[8] && i != array[9]) {
            std::cout << "Наименьшее натуральное число, отсутствующее в массиве: " << i << std::endl << "\n";
            loop = 0;
        }
    }

    int border;
    std::cout << "Введите число, числа больше которого будут отображаться в начале: ";
    if (!(std::cin >> border)) {
        std::cout << "Введите целое число \n";
        return 1;
    }

    std::cout << "Получили преобразованный массив: { ";
    for (i = 0; i < 10; i++) {
        if (array[i] >= border) {
            std::cout << array[i] << " ";
        }
    }
    for (i = 0; i < 10; i++) {
        if (array[i] < border) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << "}" << std::endl;
}
