#include "time_utility.h"
#include "train.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

void DemonstrateTimeUtility() {
    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);

    std::cout << "t2: ";
    PrintTime(t2);

    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        DemonstrateTimeUtility();

        std::vector<Train> trains = Train::ReadTrainsFromFile("TrainInput.txt");

        if (trains.empty()) {
            std::cout << "No trains were loaded from the file." << std::endl;
        } else {
            Train::PrintAllTrains(trains);
        }

        std::cout << "\n\nСписок поездов отсортированный по времени отправления: \n";
        trains = Train::sortByDispatchTime(trains);
        Train::PrintAllTrains(trains);

        Train::printTrainsFromTimeInterval(trains);

        Train::printTrainsGoingTo(trains);

        Train::printTrainsGoingToWithType(trains);

        Train::printTrainsFastestTo(trains);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}