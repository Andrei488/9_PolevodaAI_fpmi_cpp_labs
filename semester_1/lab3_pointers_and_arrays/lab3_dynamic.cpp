// solve task with usage of
// dynamic arrays

// N35

#include <iostream>
#include <random>

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    std::cout << "������� �������� ����� �������: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "����� ������� ������ ���� �����, ������������� ������ \n";
        return 1;
    }

    int* array = new int[n];

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
            break;
        }

        std::uniform_int_distribution<int> dist(min, max);

        int i = 0;
        while (i < n) {
            array[i] = dist(gen);
            i++;
        }

        std::cout << std::endl;

        i = 0;
        std::cout << "���������� ������: { ";
        while (i < n) {
            std::cout << array[i] << " ";
            i++;
        }
        std::cout << "}" << std::endl << "\n";
        break;
    }
    case 1: {
        int i = 0;

        while (i < n) {
            std::cout << "������� " << i << " ���� ����������: ";
            if (!(std::cin >> array[i])) {
                std::cout << "������� ����� ����� \n";
                return 1;
            }
            i++;
        }

        std::cout << std::endl;

        i = 0;
        std::cout << "���������� ������: { ";
        while (i < n) {
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

    int max = 0, maxid = 0;
    int i = 0;
    while (i < (n - 2)) {
        if ((array[i] + array[i + 1] + array[i + 2]) > max) {
            max = array[i] + array[i + 1] + array[i + 2];
            maxid = i;
        }
        i++;
    }
    std::cout << "�����, ���������� �������, ������ ������ ����� ����������, �����: " << max << ". ��� ����� ��������� � id: " << maxid << "(" << array[maxid] << "), " << maxid + 1 << "(" << array[maxid + 1] << "), " << maxid + 2 << "(" << array[maxid + 2] << ") \n";

    bool ifsum = 0;
    int zeroid = 0;
    i = n;
    while (i >= 0) {
        if (array[i] == 0) {
            zeroid = i;
            ifsum = 1;
            break;
        }
        i--;
    }
    int sum = 0;
    while (zeroid < n && ifsum) {
        sum = sum + array[zeroid];
        zeroid++;
    }
    std::cout << std::endl;
    if (ifsum) {
        std::cout << "����� ���� ����� ������� ����� ���������� 0 �����: " << sum << std::endl;
    }
    else {
        std::cout << "���� ����� � �������" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "�������� ��������������� ������: { ";
    for (i = 0; i < n; i++) {
        if (array[i] <= 1) {
            std::cout << array[i] << " ";
        }
    }
    for (i = 0; i < n; i++) {
        if (array[i] > 1) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << "}" << std::endl;
}
