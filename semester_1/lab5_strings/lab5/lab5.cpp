#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> extractWords(const std::string& text) {
    std::string delimeters = " ,./|()';!&:<>?}{[]\n\t\r";
    std::vector<std::string> words;

    size_t start = 0;
    size_t end = text.find_first_of(delimeters);

    while (end != std::string::npos) {
        if (end > start) {
            words.push_back(text.substr(start, end - start));
        }
        start = end + 1;
        end = text.find_first_of(delimeters, start);
    }

    if (start < text.length()) {
        words.push_back(text.substr(start));
    }

    return words;
}

size_t findMaxLength(const std::vector<std::string>& words) {
    size_t maxLength = 0;
    for (const std::string& word : words) {
        if (word.length() > maxLength) {
            maxLength = word.length();
        }
    }
    return maxLength;
}

std::vector<std::string> findLongestWords(const std::vector<std::string>& words, size_t maxLength) {
    std::vector<std::string> longestWords;
    for (const std::string& word : words) {
        if (word.length() == maxLength) {
            longestWords.push_back(word);
        }
    }
    return longestWords;
}

void printWords(const std::vector<std::string>& words) {
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << words[i];
        if (i < words.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void FindingLongestWords(const std::string& text) {
    std::vector<std::string> words = extractWords(text);
    size_t maxLength = findMaxLength(words);
    std::vector<std::string> longestWords = findLongestWords(words, maxLength);
    printWords(longestWords);
}

int main() {
    std::string text;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    FindingLongestWords(text);
    return 0;
}