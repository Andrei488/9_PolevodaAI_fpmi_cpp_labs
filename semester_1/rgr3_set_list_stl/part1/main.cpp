#include <iostream>
#include <set>
#include <cmath>
#include <stdexcept>

std::set<int> create_numbers_set(int n) {
    if (n < 2) {
        throw std::invalid_argument("N должно быть не меньше 2");
    }

    std::set<int> numbers;
    for (int i = 2; i <= n; ++i) {
        numbers.insert(i);
    }
    return numbers;
}

void remove_multiples(std::set<int>& numbers, int current_prime, int n) {
    int multiple = current_prime * current_prime;
    while (multiple <= n) {
        numbers.erase(multiple);
        multiple += current_prime;
    }
}

std::set<int> sieve_of_eratosthenes(int n) {
    try {
        if (n < 2) {
            return {};
        }

        std::set<int> numbers = create_numbers_set(n);

        auto it = numbers.begin();
        while (it != numbers.end()) {
            int current_prime = *it;

            if (current_prime * current_prime > n) {
                break;
            }

            remove_multiples(numbers, current_prime, n);
            ++it;
        }

        return numbers;
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Ошибка в sieve_of_eratosthenes: " + std::string(e.what()));
    }
}

void print_primes(const std::set<int>& primes, int n) {
    std::cout << "Простые числа до " << n << ":\n";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
}

int get_user_input() {
    int n;
    std::cout << "Введите число N: ";
    std::cin >> n;

    if (std::cin.fail() || n < 1) {
        throw std::invalid_argument("Некорректный ввод. Пожалуйста, введите положительное целое число.");
    }

    return n;
}

int main() {
    setlocale(LC_ALL, ".1251");
    try {
        int n = get_user_input();
        std::set<int> primes = sieve_of_eratosthenes(n);
        print_primes(primes, n);
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}