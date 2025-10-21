#include <iostream>
#include <random>
#include <iomanip>

int getInnerArray(int& line, int& col) {
    std::cout << "Введите размеры векторов x и y: ";
    if (!(std::cin >> line >> col) || col <= 0 || line <= 0) {
        std::cout << "Введите целые положительные числа \n";
        std::exit(1);
    }
    return 0;
}

void chooseFillingType(int& enter) {
    std::cout << "\nКак бы вы хотели заполнить матрицу? Введите '1' для заполнения вручную и '0' для рандомного заполнения: ";
    if (!(std::cin >> enter) || !(enter == 0 || enter == 1)) {
        std::cout << "Введите либо 1, либо 0 \n";
        std::exit(1);
    }
}

void randomFilling(double* x, double* y, int line, int col) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int min = 0, max = 0;

    std::cout << "Введите минимальное значение и максимальное значение: ";
    if (!(std::cin >> min >> max)) {
        std::cout << "Введите числа в рамках переменной int \n";
        std::exit(1);
    }

    if (min > max) {
        std::cout << "Ошибка: минимальное значение больше максимального!" << std::endl;
        std::exit(1);
    }

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
            std::cout << "Введите целое число \n";
            std::exit(1);
        }
        i++;
    }

    i = 0;
    while (i < col) {
        std::cout << "Введите " << i + 1 << " член прогрессии y: ";
        if (!(std::cin >> y[i])) {
            std::cout << "Введите целое число \n";
            std::exit(1);
        }
        i++;
    }

    std::cout << std::endl;
}

void printArray(double* x,int line,char name) {
    int i = 0;
    std::cout << "Полученный массив "<< name <<": { ";
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
                matr[i][t] = 0;
            }
        }
    }
}

void printMatrix(double** matr, int line, int col) {
    for (int i = 0; i < line; i++) {
        std::cout << "|";
        for (int t = 0; t < col; t++) {
            std::cout << std::setw(10) << matr[i][t] << " ";
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
            column_sum += matr[i][t];
        }
        std::cout << std::setw(10) << column_sum << " ";
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int col, line;
    getInnerArray(line, col);

    double* x = new double[line];
    double* y = new double[col];

    int enter = 0;
    chooseFillingType(enter);

    switch (enter) {
    case 0: {
        randomFilling( x, y, line, col);
        break;
    }
    case 1: {
        manualFilling(x, y, line, col);
        break;
    }
    default: {
        std::cout << "Ошибка ввода" << std::endl;
        break;
    }
    }

    printArray( x, line, 'x');
    printArray( y, col, 'y');

    double** matr = new double* [line];
    createMatrix( matr, line, col);

    task(x, y, matr, line, col);
    printMatrix(matr, line, col);

    calculatingColumnSum(matr, line, col);

    delete[] x;
    delete[] y;
    for (int i = 0; i < line; i++) {
        delete[] matr[i];
    }
    delete[] matr;
}
