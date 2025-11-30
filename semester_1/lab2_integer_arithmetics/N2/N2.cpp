#include "number_processor.h"
#include <iostream>

int main() {
    try {
        long long number = getValidatedInput();
        int result = processNumber(number);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const char* e) {
        std::cout << "Error: " << e << "!\n";
        return -1;
    }

    return 0;
}