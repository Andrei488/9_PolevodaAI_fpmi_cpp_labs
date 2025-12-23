// cl /EHsc /I. main.cpp time_utility.cpp /Fe:train_program.exe

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "time_utility.h"
#include <iostream>
using TrainId = size_t;
using namespace time_utility;

enum class TrainType { PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED };

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train(const std::string& id_str, const std::string& type_str,
          const std::string& destination_str, const std::string& dispatch_time_str,
          const std::string& travelling_time_str) {

        id_ = std::stoull(id_str);

        if (type_str == "PASSENGER") {
            type_ = TrainType::PASSENGER;
        } else if (type_str == "FREIGHT") {
            type_ = TrainType::FREIGHT;
        } else if (type_str == "HIGH_SPEED") {
            type_ = TrainType::HIGH_SPEED;
        } else if (type_str == "SUBWAY") {
            type_ = TrainType::SUBWAY;
        } else if (type_str == "SPECIALIZED") {
            type_ = TrainType::SPECIALIZED;
        } else {
            throw std::invalid_argument("Unknown train type: " + type_str);
        }

        destination_ = destination_str;

        size_t colon_pos = dispatch_time_str.find(':');
        if (colon_pos == std::string::npos) {
            throw std::invalid_argument("Invalid time format for dispatch: " + dispatch_time_str);
        }

        size_t dispatch_hours = std::stoull(dispatch_time_str.substr(0, colon_pos));
        size_t dispatch_minutes = std::stoull(dispatch_time_str.substr(colon_pos + 1));

        dispatch_time_ = SetTime(dispatch_hours, dispatch_minutes);

        colon_pos = travelling_time_str.find(':');
        if (colon_pos == std::string::npos) {
            throw std::invalid_argument("Invalid time format for travelling: " +
                                        travelling_time_str);
        }

        size_t travel_hours = std::stoull(travelling_time_str.substr(0, colon_pos));
        size_t travel_minutes = std::stoull(travelling_time_str.substr(colon_pos + 1));

        travelling_time_ = SetTime(travel_hours, travel_minutes);
    }

    TrainId GetId() const {
        return id_;
    }
    TrainType GetType() const {
        return type_;
    }
    std::string GetDestination() const {
        return destination_;
    }
    std::time_t GetDispatchTime() const {
        return dispatch_time_;
    }
    std::time_t GetTravellingTime() const {
        return travelling_time_;
    }

    std::time_t GetArrivalTime() const {
        std::tm dep = *std::localtime(&dispatch_time_);
        std::tm travel = *std::localtime(&travelling_time_);

        dep.tm_sec += travel.tm_sec;
        if (dep.tm_sec >= 60) {
            dep.tm_min += 1;
            dep.tm_sec -= 60;
        }

        dep.tm_min += travel.tm_min;
        if (dep.tm_min >= 60) {
            dep.tm_hour += 1;
            dep.tm_min -= 60;
        }

        dep.tm_hour += travel.tm_hour;
        if (dep.tm_hour >= 24) {
            dep.tm_mday += 1;
            dep.tm_hour -= 24;
        }

        return std::mktime(&dep);
    }

    void PrintInfo() const {
        std::cout << "Train ID: " << id_ << std::endl;
        std::cout << "Type: ";
        switch (type_) {
            case TrainType::PASSENGER:
                std::cout << "PASSENGER";
                break;
            case TrainType::FREIGHT:
                std::cout << "FREIGHT";
                break;
            case TrainType::HIGH_SPEED:
                std::cout << "HIGH_SPEED";
                break;
            case TrainType::SUBWAY:
                std::cout << "SUBWAY";
                break;
            case TrainType::SPECIALIZED:
                std::cout << "SPECIALIZED";
                break;
        }
        std::cout << std::endl;
        std::cout << "Destination: " << destination_ << std::endl;
        std::cout << "Departure: ";
        PrintTime(dispatch_time_);
        std::cout << "Travel time: ";
        PrintTime(travelling_time_);
        std::cout << "Arrival: ";
        PrintTime(GetArrivalTime());
    }

    static std::string TrainTypeToString(TrainType type) {
        switch (type) {
            case TrainType::PASSENGER:
                return "PASSENGER";
            case TrainType::FREIGHT:
                return "FREIGHT";
            case TrainType::HIGH_SPEED:
                return "HIGH_SPEED";
            case TrainType::SUBWAY:
                return "SUBWAY";
            case TrainType::SPECIALIZED:
                return "SPECIALIZED";
            default:
                return "UNKNOWN";
        }
    }

    static TrainType StringToTrainType(const std::string& str) {
        if (str == "PASSENGER")
            return TrainType::PASSENGER;
        if (str == "FREIGHT")
            return TrainType::FREIGHT;
        if (str == "HIGH_SPEED")
            return TrainType::HIGH_SPEED;
        if (str == "SUBWAY")
            return TrainType::SUBWAY;
        if (str == "SPECIALIZED")
            return TrainType::SPECIALIZED;

        throw std::invalid_argument("Unknown train type: " + str);
    }

    static time_t getTimeFromString(std::string time) {
        size_t colon_pos = time.find(':');
        if (colon_pos == std::string::npos) {
            throw std::invalid_argument("Invalid time format");
        }

        size_t hours = std::stoull(time.substr(0, colon_pos));
        size_t minutes = std::stoull(time.substr(colon_pos + 1));

        time_t returnTime = SetTime(hours, minutes);
        return returnTime;
    }

    static std::vector<Train> ReadTrainsFromFile(const std::string& filename) {
        std::vector<Train> trains;
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file");
        }

        std::string id, type, destination, departure, travel_time;

        while (std::getline(file, id) && std::getline(file, type) &&
               std::getline(file, destination) && std::getline(file, departure) &&
               std::getline(file, travel_time)) {

            try {
                Train train(id, type, destination, departure, travel_time);
                trains.push_back(std::move(train));

                std::string empty_line;
                std::getline(file, empty_line);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing train data: " << e.what() << std::endl;
                std::string empty_line;
                std::getline(file, empty_line);
            }
        }

        return trains;
    }

    static void PrintAllTrains(const std::vector<Train>& trains) {
        for (const auto& train : trains) {
            train.PrintInfo();
            std::cout << "-------------------" << std::endl;
        }
    }

    static std::vector<Train> sortByDispatchTime(std::vector<Train> trains) {
        std::cout
            << "\n-----------Список поездов отсортированный по времени отправления-----------";
        std::sort(trains.begin(), trains.end(), [](const Train& a, const Train& b) {
            return a.GetDispatchTime() < b.GetDispatchTime();
        });
        return trains;
    }

    static void printTrainsFromTimeInterval(std::vector<Train> trains) {
        std::cout << "\n-----------Список поездов из определенного временного интервала-----------";
        std::string start, end;
        std::cout
            << "\nВведите интервал времени для которого надо вывести поезда (Формата ЧЧ:ММ). От: ";
        if (!(std::getline(std::cin, start))) {
            throw std::runtime_error("Can't read start of time interval");
        }
        std::cout << "До: ";
        if (!(std::getline(std::cin, end))) {
            throw std::runtime_error("Can't read end of time interval");
        }
        time_t startTime = Train::getTimeFromString(start);
        time_t endTime = Train::getTimeFromString(end);
        std::vector<Train> trainstoprint;

        for (const Train& train : trains) {
            if (train.GetDispatchTime() <= endTime && train.GetDispatchTime() >= startTime) {
                trainstoprint.push_back(train);
            }
        }
        if (trainstoprint.empty()) {
            std::cout << "Не один из поездов не подходит под заданные параметры";
        }
        PrintAllTrains(trainstoprint);
    }

    static void printTrainsGoingTo(std::vector<Train> trains) {
        std::cout << "\n-----------Список поездов по пункту назначения-----------";
        std::string destination;
        std::cout
            << "\nВведите пункт назначения для которого надо вывести поезда (Например: MOSCOW): ";
        if (!(std::getline(std::cin, destination))) {
            throw std::runtime_error("Can't read destination place");
        }

        std::vector<Train> trainstoprint;

        for (const Train& train : trains) {
            if (train.GetDestination() == destination) {
                trainstoprint.push_back(train);
            }
        }
        if (trainstoprint.empty()) {
            std::cout << "Не один из поездов не подходит под заданные параметры";
        }
        PrintAllTrains(trainstoprint);
    }

    static void printTrainsGoingToWithType(std::vector<Train> trains) {
        std::cout << "\n-----------Список поездов по пункту назначения и типу поезда-----------";
        std::string destination, type;
        std::cout
            << "\nВведите пункт назначения для которого надо вывести поезда (Например: MOSCOW): ";
        if (!(std::getline(std::cin, destination))) {
            throw std::runtime_error("Can't read destination place");
        }
        std::cout << "Введите тип поезда (Например: FREIGHT): ";
        if (!(std::getline(std::cin, type))) {
            throw std::runtime_error("Can't read type of train");
        }

        std::vector<Train> trainstoprint;
        TrainType trainType = Train::StringToTrainType(type);

        for (const Train& train : trains) {
            if (train.GetDestination() == destination && train.GetType() == trainType) {
                trainstoprint.push_back(train);
            }
        }
        if (trainstoprint.empty()) {
            std::cout << "Не один из поездов не подходит под заданные параметры";
        }
        PrintAllTrains(trainstoprint);
    }

    static void printTrainsFastestTo(std::vector<Train> trains) {
        std::cout << "\n-----------Быстрейший поезд до пункта назначения-----------";
        std::string destination;
        std::cout << "\nВведите пункт назначения до которого требуется найти быстрейший поезд "
                     "(Например: MOSCOW): ";
        if (!(std::getline(std::cin, destination))) {
            throw std::runtime_error("Can't read destination place");
        }

        std::vector<Train> trainstodestination;

        for (const Train& train : trains) {
            if (train.GetDestination() == destination) {
                trainstodestination.push_back(train);
            }
        }

        if (trainstodestination.empty()) {
            std::cout << "Не один из поездов не подходит под заданные параметры";
            return;
        }

        time_t FastestTime = trainstodestination[0].GetTravellingTime();

        for (const Train& train : trainstodestination) {
            if (train.GetTravellingTime() < FastestTime) {
                FastestTime = train.GetTravellingTime();
            }
        }

        std::vector<Train> trainstoprint;
        for (const Train& train : trainstodestination) {
            if (train.GetTravellingTime() == FastestTime) {
                trainstoprint.push_back(train);
            }
        }

        if (trainstoprint.empty()) {
            std::cout << "Не один из поездов не подходит под заданные параметры";
        }

        PrintAllTrains(trainstoprint);
    }
};