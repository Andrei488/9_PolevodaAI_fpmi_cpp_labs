#include <iostream>
#include <random>
#include <iomanip>

int getInnerArray(int& line, int& col) {
    std::cout << "Введите размеры матрицы: ";
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

void chooseSortType(int& enter) {
    std::cout << "\nКак бы вы хотели отсортировать матрицу? Введите '1' для сортировки по возрастанию и '0' для сортировки по убыванию: ";
    if (!(std::cin >> enter) || !(enter == 0 || enter == 1)) {
        std::cout << "Введите либо 1, либо 0 \n";
        std::exit(1);
    }
}

void chooseSortMethod(int& enter) {
    std::cout << "\nКак бы вы хотели выполнить сортировку? 1 - пузырьком. 2 - шейкерная. 3 - слиянием ";
    if (!(std::cin >> enter) || !(enter == 1 || enter == 2 || enter == 3)) {
        std::cout << "Введите либо 1, либо 2, либо 3 \n";
        std::exit(1);
    }
}

void choosingMaxMin(int& min, int& max) {
    std::cout << "Введите минимальное значение и максимальное значение: ";
    if (!(std::cin >> min >> max)) {
        std::cout << "Введите числа в рамках переменной int \n";
        std::exit(1);
    }

    if (min > max) {
        std::cout << "Ошибка: минимальное значение больше максимального!" << std::endl;
        std::exit(1);
    }
}

void randomFilling(double** matr, int line, int col) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int min = 0, max = 0;

    choosingMaxMin(min, max);

    std::uniform_int_distribution<int> dist(min, max);

    for (int i = 0; i < line; i++) {
        for (int t = 0; t < col; t++) {
            matr[i][t] = dist(gen);
        }
    }

    std::cout << std::endl;
}

void manualFilling(double** matr, int line, int col) {

    for (int i = 0; i < line; i++) {
        for (int t = 0; t < col; t++) {
            std::cout << "Введите число находящееся в "<< i+1 << " строке, "<< t + 1 << " колонке: ";
            std::cin >> matr[i][t];
        }
    }

    std::cout << std::endl;
}

void createMatrix(double** matr, int line, int col) {
    for (int i = 0; i < line; i++) {
        matr[i] = new double[col];
    }
}

void printMatrix(double** matr, int line, int col) {
    for (int i = 0; i < line; i++) {
        std::cout << "|";
        for (int t = 0; t < col; t++) {
            std::cout << std::setw(3) << matr[i][t] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void bubbleSortMatrix(double** matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int i = 0; i < cols - 1; i++) {
            for (int j = 0; j < cols - i - 1; j++) {
                if (matrix[row][j] > matrix[row][j + 1]) {
                    std::swap(matrix[row][j], matrix[row][j+1]);
                }
            }
        }
    }
}

void shakerSortMatrix(double** matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        bool swapped = true;  
        int start = 0;        
        int end = cols - 1;   

        while (swapped) {
            swapped = false;

            for (int i = start; i < end; i++) {
                if (matrix[row][i] > matrix[row][i + 1]) {
                    std::swap(matrix[row][i], matrix[row][i + 1]);
                    swapped = true;
                }
            }

            if (!swapped) {
                break;
            }
            
            end--;

            swapped = false;

            for (int i = end - 1; i >= start; i--) {
                if (matrix[row][i] > matrix[row][i + 1]) {
                    std::swap(matrix[row][i], matrix[row][i + 1]);
                    swapped = true; 
                }
            }

            start++;
        }
    }
}

void merge(double arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    double* leftArr = new double[n1];
    double* rightArr = new double[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(double arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void mergeSortMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        mergeSort(matrix[i], 0, cols - 1);
    }
}

void reverseMatrix(double** matr, int line, int col) {
    for (int i = 0; i < line; i++) {
        for (int t = 0; t < col / 2; t++) {
            std::swap(matr[i][t] , matr[i][col - t -1]);
        }
    }
}

void clearMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int col, line;
    getInnerArray(line, col);

    double** matr = new double* [line];
    createMatrix( matr, line, col);

    int enter = 0;
    chooseFillingType(enter);

    switch (enter) {
    case 0: {
        randomFilling(matr, line, col);
        break;
    }
    case 1: {
        manualFilling(matr, line, col);
        break;
    }
    default: {
        std::cout << "Ошибка ввода" << std::endl;
        break;
    }
    }

    printMatrix(matr, line, col);

    int method = 0;
    chooseSortMethod(method);
    switch (method) {
    case 1: {
        bubbleSortMatrix(matr, line, col);
        break;
    }
    case 2: {
        shakerSortMatrix(matr, line, col);
        break;
    }
    case 3: {
        mergeSortMatrix(matr, line, col);
        break;
    }
    default: {
        std::cout << "Ошибка ввода";
        break;
    }
    }

    int sortType;
    chooseSortType(sortType);
    switch (sortType) {
    case 0: {
        reverseMatrix(matr, line, col);
        break;
    }
    case 1: {

        break;
    }
    default: {
        std::cout << "Ошибка ввода";
        break;
    }
    }

    printMatrix(matr, line, col);

    clearMatrix(matr, line);
}