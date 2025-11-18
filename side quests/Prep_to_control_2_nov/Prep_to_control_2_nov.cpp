#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void getSize(int& l, int& c, std::ifstream& in) {
    if (!(in.is_open())) {
        throw "Входной файл не открылся";
    }
    if (in.peek() == std::ifstream::traits_type::eof()) {
        throw "Файл пустой";
    }
    if (!(in >> l >> c)) {
        throw "Не удалось получить размеры матрицы";
    }
}

void createMatrix(std::vector<std::vector<int>>& matrix,const int& lines,const int& cols, std::ifstream& in) {
    matrix.resize(lines, std::vector<int>(cols));

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            int a;
            in >> a;
            matrix[i][j] = a;
        }
    }
}

int findingLowestLine(std::vector<std::vector<int>>& matrix, const int& lines, const int& cols) {
    int minline = 2147483647, minlineid = 0;

    for (int i = 0; i < lines; i++) {

        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < minline || matrix[i][j] > 0) {
                minline = matrix[i][j];
                minlineid = i;
            }
        }
    }

    return minlineid;
}

void output(std::vector<std::vector<int>>& matrix, const int& lines, const int& cols, std::ofstream& out, const int& minlineid) {
    out << "\n****************************************\n";
    for (int j = 0; j < cols; j++) {
        out << matrix[minlineid][j] << " ";
    }
    out << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string input_file = "IN.txt";
    std::string output_file = "IN.txt";

    std::ifstream in(input_file);
    std::ofstream out(output_file, std::ios::app);

    try {
        int lines, cols;
        getSize(lines, cols, in);

        std::vector<std::vector<int>> matrix;
        createMatrix(matrix, lines, cols, in);

        int minlineid = findingLowestLine(matrix, lines, cols);

        output(matrix, lines, cols, out, minlineid);
    }
    catch(const char* msg) {
        std::cout << msg;
    }
    catch (...) {
        std::cerr << "Ошибка";
    }
}
