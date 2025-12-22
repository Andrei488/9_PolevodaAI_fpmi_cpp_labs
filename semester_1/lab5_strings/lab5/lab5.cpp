#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

std::string getInputText() {
    std::string text;
    std::cout << "Enter text: ";

    if (!std::getline(std::cin, text)) {
        throw std::runtime_error("Failed to read input");
    }

    if (text.empty()) {
        throw std::invalid_argument("Input text cannot be empty");
    }

    return text;
}

std::vector<std::string> extractWords(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument("Cannot extract words from empty text");
    }

    std::string delimiters = " ,./|()';!&:<>?}{[]\n\t\r";
    std::vector<std::string> words;

    size_t start = 0;
    size_t end = text.find_first_of(delimiters);

    while (end != std::string::npos) {
        if (end > start) {
            std::string word = text.substr(start, end - start);
            if (!word.empty()) {
                words.push_back(word);
            }
        }
        start = end + 1;
        end = text.find_first_of(delimiters, start);
    }

    if (start < text.length()) {
        std::string lastWord = text.substr(start);
        if (!lastWord.empty()) {
            words.push_back(lastWord);
        }
    }

    if (words.empty()) {
        throw std::runtime_error("No valid words found in text");
    }

    return words;
}

size_t findMaxLength(const std::vector<std::string>& words) {
    if (words.empty()) {
        throw std::invalid_argument("Cannot find max length in empty word list");
    }

    size_t maxLength = 0;
    for (const std::string& word : words) {
        if (word.length() > maxLength) {
            maxLength = word.length();
        }
    }

    std::cout << "Maximum word length: " << maxLength << std::endl;
    return maxLength;
}

std::vector<std::string> findLongestWords(const std::vector<std::string>& words, size_t maxLength) {
    if (words.empty()) {
        throw std::invalid_argument("Word list is empty");
    }

    if (maxLength == 0) {
        throw std::invalid_argument("Max length cannot be zero");
    }

    std::vector<std::string> longestWords;
    for (const std::string& word : words) {
        if (word.length() == maxLength) {
            longestWords.push_back(word);
        }
    }

    if (longestWords.empty()) {
        throw std::runtime_error("No words found with maximum length");
    }

    return longestWords;
}

void printWords(const std::vector<std::string>& words) {
    if (words.empty()) {
        throw std::invalid_argument("Cannot print empty word list");
    }

    std::cout << "Longest word(s): ";
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << words[i];
        if (i < words.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void FindingLongestWords(const std::string& text) {
    try {
        std::vector<std::string> words = extractWords(text);
        size_t maxLength = findMaxLength(words);
        std::vector<std::string> longestWords = findLongestWords(words, maxLength);
        printWords(longestWords);
    }
    catch (const std::exception& e) {
        std::cerr << "Processing error: " << e.what() << std::endl;
        throw;
    }
}

int main() {
    try {
        std::string text = getInputText();
        FindingLongestWords(text);
        return 0;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 2;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 3;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 4;
    }
}