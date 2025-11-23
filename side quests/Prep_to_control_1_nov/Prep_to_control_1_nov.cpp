// Prep_to_control_2_nov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isNumber(std::string& word) {
    for (int i = 0; i < word.length(); i++) {
        if (!isDigit(word[i])) {
            return 0;
        }
    }
    return 1;
}

std::string getDelimeters(std::ifstream& in) {
    std::string delimeters;
    if (!(in.is_open())) {
        throw "Входной файл не открылся";
    }
    if (in.peek() == std::ifstream::traits_type::eof()) {
        throw "Файл пустой";
    }
    if (!getline(in, delimeters)) {
        throw "Не удалось получить";
    }
    return delimeters;
}

std::vector<int> extractNumbers(std::vector<std::string>& words) {
    std::vector<int> numbers;
    for (int i = 0; i < words.size(); i++) {
        if (isNumber(words[i])) {
            int a = std::stoi(words[i]);
            numbers.push_back(a);
        }
    }
    return numbers;
}

bool isSimple(int a) {
    for (int i = 2; i <= (a / 2); i++) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}

std::vector<std::string> extractWords(std::string& line, std::string& delimeters) {
    std::vector<std::string> words;
    size_t start = 0;

    while (start < line.length()) {
        start = line.find_first_not_of(delimeters, start);
        if (start == std::string::npos) break;

        size_t end = line.find_first_of(delimeters, start);

        if (end == std::string::npos) {
            words.push_back(line.substr(start));
            break;
        }
        else {
            words.push_back(line.substr(start, end - start));
            start = end + 1;
        }
    }

    return words;
}

void builder(std::ifstream& in, std::ofstream& out, std::string& delimeters) {
    std::string line;
    while (getline(in, line)) {
        std::vector<std::string> words = extractWords(line, delimeters);
        std::vector<int> numbers = extractNumbers(words);
        int min = 0, max = 0;
        for (int i = 0; i < numbers.size(); i++) {
            if (isSimple(numbers[i])) {
                if (min == 0 && max == 0) {
                    min = numbers[i];
                    max = numbers[i];
                }
                if (numbers[i] > max) {
                    max = numbers[i];
                }
                if (numbers[i] < min) {
                    min = numbers[i];
                }
            }
        }
        if (min == max) {
            out << '*' << line << "\n";
        }
        else {
            std::string maxString = std::to_string(max);
            std::string minString = std::to_string(min);

            size_t minPos = line.find(minString);
            size_t maxPos = line.find(maxString);

            line.replace(minPos, minString.length(), maxString);
            line.replace(maxPos, maxString.length(), minString);

            out << line << "\n";
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string input_file = "IN.txt";
    std::string output_file = "OUT.txt";

    std::ifstream in(input_file);
    std::ofstream out(output_file);

    try {
        int lines, cols;
        std::string delimeters = getDelimeters(in);

        builder(in, out, delimeters);
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    catch (...) {
        std::cerr << "Ошибка";
    }
}
