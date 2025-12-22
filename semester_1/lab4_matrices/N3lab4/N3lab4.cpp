#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

void getInnerArray(int& line, int& col) {
    std::cout << "Введите размеры векторов x и y: ";
    if (!(std::cin >> line >> col) || col <= 0 || line <= 0) {
        throw "Введите целые положительные числа";
    }
}

void chooseFillingType(int& enter) {
    std::cout << "\nКак бы вы хотели заполнить матрицу? Введите '1' для заполнения вручную и '0' для рандомного заполнения: ";
    if (!(std::cin >> enter) || !(enter == 0 || enter == 1)) {
        throw "Введите либо 1, либо 0";
    }
}

void choosingMaxMin(int& max, int& min) {
    std::cout << "Введите минимальное значение и максимальное значение: ";
    if (!(std::cin >> min >> max)) {
        throw "Введите числа в рамках переменной int";
    }

    if (min > max) {
        throw "Минимальное значение больше максимального";
    }
}

void randomFilling(double* x, double* y, int line, int col, std::mt19937& gen) {
    int min = 0, max = 0;
    choosingMaxMin(max, min);

    std::uniform_int_distribution<int> dist(min, max);

    for (int i = 0; i < line; i++) {
        x[i] = dist(gen);
    }
    for (int i = 0; i < col; i++) {
        y[i] = dist(gen);
    }
    std::cout << std::endl;
}

void manualFilling(double* x, double* y, int line, int col) {
    int i = 0;
    while (i < line) {
        std::cout << "Введите " << i + 1 << " член прогрессии x: ";
        if (!(std::cin >> x[i])) {
            throw "Введите целое число";
        }
        i++;
    }

    i = 0;
    while (i < col) {
        std::cout << "Введите " << i + 1 << " член прогрессии y: ";
        if (!(std::cin >> y[i])) {
            throw "Введите целое число";
        }
        i++;
    }
    std::cout << std::endl;
}

void cleanup(double* x, double* y, double** matr, int line) {
    if (x) delete[] x;
    if (y) delete[] y;
    if (matr) {
        for (int i = 0; i < line; i++) {
            if (matr[i]) delete[] matr[i];
        }
        delete[] matr;
    }
}

void printArray(double* x, int line, char name) {
    int i = 0;
    std::cout << "Полученный массив " << name << ": { ";
    while (i < line) {
        std::cout << x[i] << " ";
        i++;
    }
    std::cout << "}" << std::endl << "\n";
}

void createMatrix(double** matr, int line, int col) {
    for (int i = 0; i < line; i++) {
        matr[i] = new double[col];
    }
}

void task(double* x, double* y, double** matr, int line, int col) {
    for (int i = 0; i < line; i++) {
        for (int t = 0; t < col; t++) {
            if ((x[i] + y[t]) != 0) {
                matr[i][t] = 1.0 / (x[i] + y[t]);
            }
            else {
                matr[i][t] = INFINITY;
            }
        }
    }
}

void printMatrix(double** matr, int line, int col) {
    for (int i = 0; i < line; i++) {
        std::cout << "|";
        for (int t = 0; t < col; t++) {
            if (std::isinf(matr[i][t])) {
                std::cout << std::setw(10) << "inf" << " ";
            }
            else {
                std::cout << std::setw(10) << matr[i][t] << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void calculatingColumnSum(double** matr, int line, int col) {
    std::cout << " ";
    for (int t = 0; t < col; t++) {
        double column_sum = 0.0;
        for (int i = 0; i < line; i++) {
            if (!std::isinf(matr[i][t])) {
                column_sum += matr[i][t];
            }
            else {
                column_sum = INFINITY;
                break;
            }
        }
        if (std::isinf(column_sum)) {
            std::cout << std::setw(10) << "inf" << " ";
        }
        else {
            std::cout << std::setw(10) << column_sum << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    double* x = nullptr;
    double* y = nullptr;
    double** matr = nullptr;
    int line = 0, col = 0;

    try {
        std::random_device rd;
        std::mt19937 gen(rd());

        getInnerArray(line, col);

        x = new double[line];
        y = new double[col];

        int enter = 0;
        chooseFillingType(enter);

        switch (enter) {
        case 0:
            randomFilling(x, y, line, col, gen);
            break;
        case 1:
            manualFilling(x, y, line, col);
            break;
        default:
            throw "Ошибка ввода";
        }

        printArray(x, line, 'x');
        printArray(y, col, 'y');

        matr = new double* [line];
        for (int i = 0; i < line; i++) {
            matr[i] = new double[col];
        }

        task(x, y, matr, line, col);
        printMatrix(matr, line, col);
        calculatingColumnSum(matr, line, col);
    }
    catch (const char* errorMessage) {
        std::cout << "ОШИБКА: " << errorMessage << std::endl;
        cleanup(x, y, matr, line);
    }
    catch (...) {
        std::cout << "Неизвестная ошибка!" << std::endl;
        cleanup(x, y, matr, line);
    }

    cleanup(x, y, matr, line);

    return 0;
}