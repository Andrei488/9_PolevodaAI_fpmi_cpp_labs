// solve task with usage of
// dynamic arrays

// N35

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
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Длина массива должна быть целым, положительным числом \n";
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
        std::cout << "Введите " << i + 1 << " член прогрессии: ";
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

void findMaxTripleSum(int array[], int n) {
    int max = 0, maxid = 0;
    int i = 0;
    while (i < (n - 2)) {
        if ((array[i] + array[i + 1] + array[i + 2]) > max) {
            max = array[i] + array[i + 1] + array[i + 2];
            maxid = i;
        }
        i++;
    }
    std::cout << "Сумма, наибольшей цепочки, подряд идущих чисел прогрессии, равна: " << max << ". Это сумма элементов с id: " << maxid << "(" << array[maxid] << "), " << maxid + 1 << "(" << array[maxid + 1] << "), " << maxid + 2 << "(" << array[maxid + 2] << ") \n";
}

void sumAfterLastZero(int array[], int n) {
    bool ifsum = 0;
    int zeroid = 0;
    int i = n;
    while (i >= 0) {
        if (array[i] == 0) {
            zeroid = i;
            ifsum = 1;
            break;
        }
        i--;
    }
    int sum = 0;
    while (zeroid < n && ifsum) {
        sum = sum + array[zeroid];
        zeroid++;
    }
    std::cout << std::endl;
    if (ifsum) {
        std::cout << "Сумма всех чисел массива после последнего 0 равна: " << sum << std::endl;
    }
    else {
        std::cout << "Нету нулей в массиве" << std::endl;
    }
    std::cout << std::endl;
}

void rearrangeArrayByOne(int array[], int n) {
    int i = 0;
    while (i < n) {
        array[i + n] = array[i];
        i++;
    }

    int l = 0;
    for (i = 0; i < n; i++) {
        if (array[i + n] <= 1) {
            array[l] = array[i + n];
            l++;
        }
    }

    for (i = 0; i < n; i++) {
        if (array[i + n] > 1) {
            array[l] = array[i + n];
            l++;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n = getArrayLength();
    if (n == -1) return 1;

    int* array = new int[2 * n];

    int enter = getInputMethod();
    if (enter == -1) {
        delete[] array;
        return 1;
    }

    if (!fillArray(array, n, enter)) {
        delete[] array;
        return 1;
    }

    print(array, n);

    findMaxTripleSum(array, n);

    sumAfterLastZero(array, n);

    rearrangeArrayByOne(array, n);

    std::cout << "Преобразованный массив, в котором сначала выводяться все числа не превыщающие 1: \n";
    print(array, n);

    delete[] array;
}