// lab5.cpp
 
#include <string>
#include <iostream>

int main() {

    std::string text;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    size_t pos = text.find("welcome");
    if (pos != std::string::npos) {
        std::cout << "Find on id: " << pos << std::endl;
    }
}