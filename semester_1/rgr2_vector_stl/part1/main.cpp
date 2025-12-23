//cl /EHsc main.cpp
//main.exe

#include <vector>
#include <iostream>
#include <sstream>
#include <numeric>
#include <cmath>
#include <algorithm>

std::vector<int> inputVector() {
    std::cout << "Введите элементы вектора через пробел: ";
    std::vector<int> vec;
    std::string line;

    if (!std::getline(std::cin, line)) {
        throw std::runtime_error("Ошибка чтения ввода");
    }

    if (line.empty()) {
        throw std::runtime_error("Вы не ввели ни единого числа");
    }

    std::istringstream numbers(line);
    int a;
    while (numbers >> a) {
        vec.push_back(a);
    }
    return vec;
}

int accumulate(std::vector<int> vec) {
    if (vec.empty()) {
        throw std::runtime_error("Вектор пуст, невозможно вычислить сумму");
    }
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    return sum;
}

int getSearchNumber() {
    int a;
    std::cout << "Количество вхождений какого числа вы хотите посчитать: ";
    if (!(std::cin >> a)) {
        throw std::runtime_error("Не удалочь получить искомое число");
    }
    return a;
}

void countEntryOfNumber(std::vector<int> vector, int searchNumber) {
    int counter = 0;
    for (int num : vector) {
        if (num == searchNumber) {
            counter++;
        }
    }
    std::cout << "Число " << searchNumber << " встречается " << counter << " раз(а)\n";
}

int getAverage(std::vector<int> vector) {
    int sum = accumulate(vector);
    int average = sum / vector.size();
    return average;
}

void printVector(std::vector<int> vector) {
    std::cout << "{ ";
    for (int num : vector) {
        std::cout << num << " ";
    }
    std::cout << "}";
}

std::vector<int> countNumbersGreaterThan(std::vector<int> vector) {
    std::cout << "\nПодсчет чисел больше заданного значения. Текущий вектор: ";
    printVector(vector);
    std::cout << std::endl;

    if (vector.empty()) {
        throw std::runtime_error("Вектор пуст, операция невозможна.");
    }

    std::cout << "Введите значение n для сравнения: ";
    int n;
    if (!(std::cin >> n)) {
        throw std::runtime_error("Некорректный ввод значения n");
    }

    int count = 0;
    for (int num : vector) {
        if (num > n) {
            count++;
        }
    }

    std::cout << "Количество чисел больше " << n << ": " << count << "\n";

    return vector;
}

std::vector<int> replaceZeros(std::vector<int>& vector) {
    std::cout << "\nЗаменяем нули средним арифметическим. Текущий вектор: ";
    printVector(vector);
    int average = getAverage(vector);
    for (int& num : vector) {
        if (num == 0) {
            num = average;
        }
    }
    std::cout << "\nИзмененный массив: ";
    printVector(vector);
    std::cout << std::endl;
    return vector;
}

std::vector<int> addIntervalSumToAll(std::vector<int> vector) {
    std::cout << "\nДобавление суммы интервала ко всем элементам. Текущий вектор: ";
    printVector(vector);
    std::cout << std::endl;

    if (vector.empty()) {
        throw std::runtime_error("Вектор пуст, операция добавления суммы интервала невозможна.");
    }

    std::cout << "Введите индекс начала интервала (от 0 до " << vector.size() - 1 << "): ";
    int startId;
    if (!(std::cin >> startId)) {
        throw std::runtime_error("Некорректный ввод начала интервала");
    }

    std::cout << "Введите индекс конца интервала (от " << startId + 1 << " до " << vector.size() << "): ";
    int endId;
    if (!(std::cin >> endId)) {
        throw std::runtime_error("Некорректный ввод конца интервала");
    }

    if (startId < 0 || endId > vector.size() || startId >= endId) {
        throw std::runtime_error("Некорректный интервал индексов");
    }

    int intervalSum = 0;
    for (int i = startId; i < endId; ++i) {
        intervalSum += vector[i];
    }
    std::cout << "Сумма элементов в интервале = " << intervalSum << "\n";

    for (int& num : vector) {
        num += intervalSum;
    }

    std::cout << "Результат: ";
    printVector(vector);
    std::cout << std::endl;

    return vector;
}

std::vector<int> replaceEvenAbsoluteValues(std::vector<int> vector) {
    std::cout << "\nЗамена чисел с четным модулем на разность max-min. Текущий вектор: ";
    printVector(vector);
    std::cout << std::endl;

    if (vector.empty()) {
        throw std::runtime_error("Вектор пуст, операция невозможна.");
    }

    int maxElement = *std::max_element(vector.begin(), vector.end());
    int minElement = *std::min_element(vector.begin(), vector.end());
    int difference = maxElement - minElement;

    std::cout << "Максимальный элемент: " << maxElement << "\n";
    std::cout << "Минимальный элемент: " << minElement << "\n";
    std::cout << "Их разность: " << difference << "\n";

    int replacementsCount = 0;
    for (int& num : vector) {
        if (std::abs(num) % 2 == 0) {
            num = difference;
            replacementsCount++;
        }
    }

    std::cout << "Заменено " << replacementsCount << " элемент(ов)\n";
    std::cout << "Результат: ";
    printVector(vector);
    std::cout << std::endl;

    return vector;
}

std::vector<int> removeDuplicateAbsoluteValues(std::vector<int> vector) {
    std::cout << "\nУдаление дубликатов по модулю. Текущий вектор: ";
    printVector(vector);
    std::cout << std::endl;

    if (vector.empty()) {
        throw std::runtime_error("Вектор пуст, операция невозможна.");
    }

    std::vector<int> result;
    std::vector<int> seenAbsValues;

    for (int num : vector) {
        int absValue = std::abs(num);
        bool found = false;

        for (int seen : seenAbsValues) {
            if (seen == absValue) {
                found = true;
                break;
            }
        }

        if (!found) {
            seenAbsValues.push_back(absValue);
            result.push_back(num);
        }
    }

    int removedCount = vector.size() - result.size();
    std::cout << "Удалено " << removedCount << " элемент(ов)\n";
    std::cout << "Результат: ";
    printVector(result);
    std::cout << std::endl;

    return result;
}

void writeLog(std::vector<int> vector, const int& searchNumber) {
    try {
        std::cout << "Сумма чисел: " << accumulate(vector) << "\n";
        std::cout << "Общее количество чисел: " << vector.size() << "\n";
        countEntryOfNumber(vector, searchNumber);
    }
    catch (const std::exception& e) {
        throw;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        std::vector<int> vector = inputVector();
        int searchNumber = getSearchNumber();
        writeLog(vector, searchNumber);
        vector = countNumbersGreaterThan(vector);
        vector = replaceZeros(vector);
        vector = addIntervalSumToAll(vector);
        vector = replaceEvenAbsoluteValues(vector);
        vector = removeDuplicateAbsoluteValues(vector);
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка" << std::endl;
        return 2;
    }
    return 0;
}