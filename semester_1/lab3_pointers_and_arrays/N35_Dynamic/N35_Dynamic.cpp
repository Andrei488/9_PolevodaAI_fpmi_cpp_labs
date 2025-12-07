#include <iostream>
#include <random>

void print(double* a, int n) {
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

bool fillArrayRandom(double* array, int n, std::mt19937& gen) {
    double min = 0, max = 0;

    std::cout << "Введите минимальное значение и максимальное значение: ";
    if (!(std::cin >> min >> max)) {
        std::cout << "Введите числа \n";
        return false;
    }

    if (min > max) {
        std::cout << "Ошибка: минимальное значение больше максимального!" << std::endl;
        return false;
    }

    std::uniform_real_distribution<double> dist(min, max);

    int i = 0;
    while (i < n) {
        array[i] = dist(gen);
        i++;
    }

    std::cout << std::endl;
    return true;
}

bool fillArrayManual(double* array, int n) {
    int i = 0;

    while (i < n) {
        std::cout << "Введите " << i + 1 << " член прогрессии: ";
        if (!(std::cin >> array[i])) {
            std::cout << "Введите число \n";
            return false;
        }
        i++;
    }

    std::cout << std::endl;
    return true;
}

bool fillArray(double* array, int n, int method, std::mt19937& gen) {
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

void findMaxTripleSum(double* array, int n) {
    double max = 0;
    int maxid = 0;
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

void sumAfterLastZero(double* array, int n) {
    bool ifsum = 0;
    int zeroid = 0;
    int i = n - 1;
    while (i >= 0) {
        if (array[i] == 0) {
            zeroid = i;
            ifsum = 1;
            break;
        }
        i--;
    }
    double sum = 0;
    if (ifsum) {
        for (int j = zeroid + 1; j < n; j++) {
            sum += array[j];
        }
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

void rearrangeArrayByOne(double* array, int n) {
    for (int i = 0; i < n; i++) {
        if (array[i] <= 1) {
            double temp = array[i];
            int j = i;
            while (j > 0 && array[j - 1] > 1) {
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

    int n = getArrayLength();
    if (n == -1) return 1;

    double* array = new double[n];

    int enter = getInputMethod();
    if (enter == -1) {
        delete[] array;
        return 1;
    }

    if (!fillArray(array, n, enter, gen)) {
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