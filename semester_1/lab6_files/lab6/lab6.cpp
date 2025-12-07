// lab6 N2

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<std::string> read(std::ifstream& in) {
    std::vector<std::string> lines;
    std::string line;

    if (!in.is_open()) {
        throw "Файл не открылся";
    } 
    if (in.peek() == std::ifstream::traits_type::eof()) {
        throw "Файл пустой";
    }

    while (getline(in, line)) {
        lines.push_back(line);
    }

    if (lines.empty()) {
        throw "Не удалось считать текст с файла";
    }

    return lines;
}

std::string getWord(std::vector<std::string>& lines) {
    std::string word = lines[0];

    size_t start = word.find_first_not_of(" ");
    if (start != std::string::npos) {
        word = word.substr(start);
    }

    size_t end = word.find_last_not_of(' ');
    if (end != std::string::npos) {
        word = word.substr(0, end + 1);
    }

    return word;
}

std::vector<std::string> extractWords(std::vector<std::string> lines) {
    std::vector<std::string> words;

    for (size_t i = 1; i < lines.size(); i++) {
        std::string line = lines[i];
        size_t start = 0;
        size_t end = line.find_first_of(" ");

        while (end != std::string::npos) {
            if (end > start) {
                words.push_back(line.substr(start, end - start));
            }
            start = end + 1;
            end = line.find_first_of(" ", start);
        }

        if (start < line.length()) {
            words.push_back(line.substr(start));
        }
    }

    return words;
}

size_t calculatingNumOfWordInText(size_t& quantity, std::string word, std::vector<std::string> words) {
    quantity = 0;
    for (int i = 0; i < words.size(); i++) {
        if (word == words[i]) {
            quantity++;
        }
    }
    
    return quantity;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string input_file = "input.txt";
    std::string output_file = "output.txt";

    try {
        std::ifstream in(input_file);

        std::vector<std::string> lines = read(in);

        std::string word = getWord(lines);
        std::vector<std::string> words = extractWords(lines);
        size_t quantity = calculatingNumOfWordInText(quantity, word, words);

        std::ofstream out(output_file);

        out << "Слово из первой строчки встретилось в тексте " << quantity << " раз.";
    }
    catch (std::string msg) {
        std::cout << msg;
    }

    std::cout << "Программа завершена успешно, результат находится в файле output.txt\n";
}