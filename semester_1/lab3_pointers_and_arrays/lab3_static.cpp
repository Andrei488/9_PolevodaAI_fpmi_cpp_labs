// solve task with usage of
// static arrays

// N17

#include <iostream>
#include <random>

int main()
{
    setlocale(LC_ALL, "Russian");

    int array[10] = { 0 };
    std::cout << "Default: array[10]\n";

    int enter = 0;
    std::cout << "��� �� �� ������ ��������� ������? ������� '1' ��� ���������� ������� � '0' ��� ���������� ����������: ";
    std::cin >> enter;

    switch (enter) {
    case 0: {
        std::random_device rd;
        std::mt19937 gen(rd());

        int min = 0, max = 0;

        std::cout << "������� ����������� �������� � ������������ ��������: ";
        std::cin >> min >> max;

        if (min > max) {
            std::cout << "������: ����������� �������� ������ �������������!" << std::endl;
            return 1;
        }

        std::uniform_int_distribution<int> dist(min, max);

        int i = 0;
        while (i < 10) {
            array[i] = dist(gen);
            i++;
        }

        std::cout << std::endl;

        i = 0;
        std::cout << "���������� ������: { ";
        while (i < 10) {
            std::cout << array[i] << " ";
            i++;
        }
        std::cout << "}" << std::endl << "\n";
        break;
    }
    case 1: {
        int i = 0;

        while (i < 10) {
            std::cout << "������� " << i << " ���� ����������: ";
            std::cin >> array[i];
            i++;
        }

        std::cout << std::endl;

        i = 0;
        std::cout << "���������� ������: { ";
        while (i < 10) {
            std::cout << array[i] << " ";
            i++;
        }
        std::cout << "}" << std::endl << "\n";

        break;
    }
    default: {
        std::cout << "������ �����" << std::endl;
        break;
    }
    }

    int M = array[0];
    int i = 1;
    while (i < 10) {
        if (array[i] > M) {
            M = array[i];
        }
        i++;
    }
    i = 0;
    std::cout << "ID �������� � ������������ ���������: ";
    while (i < 10) {
        if (array[i] == M) {
            std::cout << i << " ";
        }
        i++;
    }

    std::cout << std::endl;

    i = 1;
    bool loop = 1;
    for (; loop; i++) {
        if (i != array[0] && i != array[1] && i != array[2] && i != array[3] && i != array[4] && i != array[5] && i != array[6] && i != array[7] && i != array[8] && i != array[9]) {
            std::cout << "���������� ����������� �����, ������������� � �������: " << i << std::endl << "\n";
            loop = 0;
        }
    }

    int border;
    std::cout << "������� �����, ����� ������ �������� ����� ������������ � ������: ";
    std::cin >> border;

    std::cout << "�������� ��������������� ������: { ";
    for (i = 0; i < 10; i++) {
        if (array[i] >= border) {
            std::cout << array[i] << " ";
        }
    }
    for (i = 0; i < 10; i++) {
        if (array[i] < border) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << "}" << std::endl;
}
