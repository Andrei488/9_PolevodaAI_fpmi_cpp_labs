#include <iostream>
#include <random>

void print(int* a, int n) {
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

bool findMinMax(int& min, int& max) {
    std::cout << "Введите минимальное значение и максимальное значение: ";
    if (!(std::cin >> min >> max)) {
        std::cout << "Введите числа в рамках переменной int \n";
        return false;
    }

    if (min > max) {
        std::cout << "Ошибка: минимальное значение больше максимального!" << std::endl;
        return false;
    }

    if (min < 1) {
        std::cout << "Ошибка: попытка сгенерировать не натуральное число" << std::endl;
        return false;
    }

    return true;
}

bool fillArrayRandom(int* array, int n, std::mt19937& gen) {
    int min = 0, max = 0;

    if (findMinMax(min, max) == false) {
        return false;
    }

    std::uniform_int_distribution<int> dist(min, max);

    for (int i = 0; i < n; i++) {
        array[i] = dist(gen);
    }

    std::cout << std::endl;
    return true;
}

bool fillArrayManual(int* array, int n) {
    int i = 0;

    while (i < n) {
        std::cout << "Введите " << i + 1 << " член массива: ";
        if (!(std::cin >> array[i]) || array[i] < 1) {
            std::cout << "Введите целое натуральное число \n";
            return false;
        }
        i++;
    }

    std::cout << std::endl;
    return true;
}

bool fillArray(int* array, int n, int method, std::mt19937& gen) {
    switch (method) {
    case 0:
        return fillArrayRandom(array, n, gen);
    case 1:
        return fillArrayManual(array, n);
    default:
        std::cout << "Ошибка ввода" << std::endl;
        return false;
    }
}

void findMaxElements(int* array, int n) {
    int M = array[0];
    int i = 1;
    while (i < n) {
        if (array[i] > M) {
            M = array[i];
        }
        i++;
    }
    i = 0;
    std::cout << "Номер элемента с максимальным значением: ";
    while (i < n) {
        if (array[i] == M) {
            std::cout << i + 1 << " ";
        }
        i++;
    }

    std::cout << std::endl;
}

int findMissingNatural(int* array, int n) {
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

void rearrangeArray(int* array, int n, int border) {
    for (int i = 0; i < n; i++) {
        if (array[i] > border) {
            int temp = array[i];
            int j = i;
            while (j > 0 && array[j - 1] <= border) {
                array[j] = array[j - 1];
                j--;
            }
            array[j] = temp;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::random_device rd;
    std::mt19937 gen(rd());

    int const maxLength = 2000;
    int array[maxLength] = { 0 };

    int n = getArrayLength();
    if (n == -1) return 1;

    int enter = getInputMethod();
    if (enter == -1) return 1;

    if (!fillArray(array, n, enter, gen)) return 1;

    print(array, n);

    findMaxElements(array, n);

    int nat = findMissingNatural(array, n);
    std::cout << "Наименьшее натуральное число, отсутствующее в массиве: " << nat << std::endl << "\n";

    int border = getBorder();
    if (border == -1) return 1;

    rearrangeArray(array, n, border);

    print(array, n);
}
