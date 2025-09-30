// N17_Static.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.

#include <iostream>
#include <random>

int main()
{
    setlocale(LC_ALL, "Russian");

    int array[10000] = { 0 };

    int n;
    std::cout << "������� �������� ����� �������: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "����� ������� ������ ���� �����, ������������� ������ \n";
        return 1;
    }

    int enter = 0;
    std::cout << "��� �� �� ������ ��������� ������? ������� '1' ��� ���������� ������� � '0' ��� ���������� ����������: ";
    if (!(std::cin >> enter) || !(enter == 0 || enter == 1)) {
        std::cout << "������� ���� 1, ���� 0 \n";
        return 1;
    }

    switch (enter) {
    case 0: {
        std::random_device rd;
        std::mt19937 gen(rd());

        int min = 0, max = 0;

        std::cout << "������� ����������� �������� � ������������ ��������: ";
        if (!(std::cin >> min >> max)) {
            std::cout << "������� ����� � ������ ���������� int \n";
            return 1;
        }

        if (min > max) {
            std::cout << "������: ����������� �������� ������ �������������!" << std::endl;
            return 1;
        }

        std::uniform_int_distribution<int> dist(min, max);

        int i = 0;
        while (i < n) {
            array[i] = dist(gen);
            i++;
        }

        std::cout << std::endl;

        break;
    }
    case 1: {
        int i = 0;

        while (i < n) {
            std::cout << "������� " << i + 1 << " ���� �������: ";
            if (!(std::cin >> array[i])) {
                std::cout << "������� ����� ����� \n";
                return 1;
            }
            i++;
        }

        std::cout << std::endl;

        break;
    }
    default: {
        std::cout << "������ �����" << std::endl;
        break;
    }
    }

    int i = 0;
    std::cout << "���������� ������: { ";
    while (i < n) {
        std::cout << array[i] << " ";
        i++;
    }
    std::cout << "}" << std::endl << "\n";

    int M = array[0];
    i = 1;
    while (i < n) {
        if (array[i] > M) {
            M = array[i];
        }
        i++;
    }
    i = 0;
    std::cout << "ID �������� � ������������ ���������: ";
    while (i < n) {
        if (array[i] == M) {
            std::cout << i << " ";
        }
        i++;
    }

    std::cout << std::endl;

    i = 0;
    int nat = 1;
    while (i < n) {
        if (array[i] == nat) {
            nat++;
            i = 0;
        }
        else {
            i++;
        }
    }

    std::cout << "���������� ����������� �����, ������������� � �������: " << nat << std::endl << "\n";

    int border;
    std::cout << "������� �����, ����� ������ �������� ����� ������������ � ������: ";
    if (!(std::cin >> border)) {
        std::cout << "������� ����� ����� \n";
        return 1;
    }

    std::cout << "�������� ��������������� ������: { ";
    for (i = 0; i < n; i++) {
        if (array[i] > border) {
            std::cout << array[i] << " ";
        }
    }
    for (i = 0; i < n; i++) {
        if (array[i] <= border) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << "}" << std::endl;
}
