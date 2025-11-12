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

    return lines;
}

std::string getWord(std::vector<std::string>& lines) {
    std::string word = lines[0];
    return word;
}

std::vector<std::string> extractWords(std::vector<std::string> lines) {

}
int main()
{
    std::string input_file = "input.txt";
    std::string output_file = "output.txt";

    try {
        std::ifstream in(input_file);

        std::vector<std::string> lines = read(in);

        std::string word = getWord(lines);
        std::vector<std::string> words = extractWords(lines);

        std::ofstream out(output_file);

        out << " ";
    }
    catch (std::string msg) {
        std::cout << msg;
    }
}