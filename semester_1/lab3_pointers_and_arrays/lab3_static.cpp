// N17_Static.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <random>

void print(int a[], int n) {
    int i = 0;
    std::cout << "Полученный массив: { ";
    while (i < n) {
        std::cout << a[i] << " ";
        i++;
    }
    std::cout << "}" << std::endl << "\n";
}

int getArrayLength() {
    int n;
    std::cout << "Введите желаемую длину массива: ";
    if (!(std::cin >> n) || n <= 0 || n > 1000) {
        std::cout << "Длина массива должна быть целым, положительным числом, не более 1000 \n";
        return -1;
    }
    return n;
}

int getInputMethod() {
    int enter = 0;
    std::cout << "Как бы вы хотели заполнить массив? Введите '1' для заполнения вручную и '0' для рандомного заполнения: ";
    if (!(std::cin >> enter) || !(enter == 0 || enter == 1)) {
        std::cout << "Введите либо 1, либо 0 \n";
        return -1;
    }
    return enter;
}

bool fillArrayRandom(int array[], int n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int min = 0, max = 0;

    std::cout << "Введите минимальное значение и максимальное значение: ";
    if (!(std::cin >> min >> max)) {
        std::cout << "Введите числа в рамках переменной int \n";
        return false;
    }

    if (min > max) {
        std::cout << "Ошибка: минимальное значение больше максимального!" << std::endl;
        return false;
    }

    std::uniform_int_distribution<int> dist(min, max);

    int i = 0;
    while (i < n) {
        array[i] = dist(gen);
        i++;
    }

    std::cout << std::endl;
    return true;
}

bool fillArrayManual(int array[], int n) {
    int i = 0;

    while (i < n) {
        std::cout << "Введите " << i + 1 << " член массива: ";
        if (!(std::cin >> array[i])) {
            std::cout << "Введите целое число \n";
            return false;
        }
        i++;
    }

    std::cout << std::endl;
    return true;
}

bool fillArray(int array[], int n, int method) {
    switch (method) {
    case 0:
        return fillArrayRandom(array, n);
    case 1:
        return fillArrayManual(array, n);
    default:
        std::cout << "Ошибка ввода" << std::endl;
        return false;
    }
}

void findMaxElements(int array[], int n) {
    int M = array[0];
    int i = 1;
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
}

int findMissingNatural(int array[], int n) {
    int i = 0;
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
    return nat;
}

int getBorder() {
    int border;
    std::cout << "Введите число, числа больше которого будут отображаться в начале: ";
    if (!(std::cin >> border)) {
        std::cout << "Введите целое число \n";
        return -1;
    }
    return border;
}

void rearrangeArray(int array[], int n, int border) {
    int i = 0;
    while (i < n) {
        array[i + n] = array[i];
        i++;
    }

    int l = 0;
    for (i = 0; i < n; i++) {
        if (array[i + n] > border) {
            array[l] = array[i + n];
            l++;
        }
    }

    for (i = 0; i < n; i++) {
        if (array[i + n] <= border) {
            array[l] = array[i + n];
            l++;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int array[2000] = { 0 };

    int n = getArrayLength();
    if (n == -1) return 1;

    int enter = getInputMethod();
    if (enter == -1) return 1;

    if (!fillArray(array, n, enter)) return 1;

    print(array, n);

    findMaxElements(array, n);

    int nat = findMissingNatural(array, n);
    std::cout << "Наименьшее натуральное число, отсутствующее в массиве: " << nat << std::endl << "\n";

    int border = getBorder();
    if (border == -1) return 1;

    rearrangeArray(array, n, border);

    print(array, n);
}