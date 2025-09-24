#include <iostream>
#include <random>
#include <iomanip>

int main()
{
    setlocale(LC_ALL, "Russian");

    int col, line;
    std::cout << "Введите размеры векторов y и x: ";
    if (!(std::cin >> col >> line) || col <= 0 || line <= 0) {
        std::cout << "Введите целые положительный числа \n";
        return 1;
    }

    double* x = new double[line];
    double* y = new double[col];

    int enter = 0;
    std::cout << "Как бы вы хотели заполнить матрицу? Введите '1' для заполнения вручную и '0' для рандомного заполнения: ";
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
            break;
        }

        std::uniform_int_distribution<int> dist(min, max);

        for (int i = 0; i < line; i++) {
            x[i] = dist(gen);
        }
        for (int i = 0; i < col; i++) {
            y[i] = dist(gen);
        }

        std::cout << std::endl;
        break;
    }
    case 1: {

        int i = 0;
        while (i < line) {
            std::cout << "Введите " << i << " член прогрессии x: ";
            if (!(std::cin >> x[i])) {
                std::cout << "Введите целое число \n";
                return 1;
            }
            i++;
        }

        i = 0;
        while (i < col) {
            std::cout << "Введите " << i << " член прогрессии y: ";
            if (!(std::cin >> y[i])) {
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
    std::cout << "Полученный массив x: { ";
    while (i < line) {
        std::cout << x[i] << " ";
        i++;
    }
    std::cout << "}" << std::endl << "\n";

    i = 0;
    std::cout << "Полученный массив y: { ";
    while (i < col) {
        std::cout << y[i] << " ";
        i++;
    }
    std::cout << "}" << std::endl << "\n";

    double** matr = new double* [line];
    for (int i = 0; i < line; i++) {
        matr[i] = new double[col];
    }

    for (int i = 0; i < line; i++) {
        for (int t = 0; t < col; t++) {
            matr[i][t] = 1.0 / (x[i] + y[t]);
        }
    }

    for (int i = 0; i < line; i++) {
        std::cout << "|";
        for (int t = 0; t < col; t++) {
            std::cout << std::setw(10) << matr[i][t] << " ";
        }
        std::cout << "|" << std::endl;
    }

    std::cout << " ";
    for (int t = 0; t < col; t++) {
        double column_sum = 0.0;
        for (int i = 0; i < line; i++) {
            column_sum += matr[i][t];
        }
        std::cout << std::setw(10) << column_sum << " ";
    }
    std::cout << std::endl;

    delete[] x;
    delete[] y;
    for (int i = 0; i < line; i++) {
        delete[] matr[i];
    }
    delete[] matr;
}
