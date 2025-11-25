#include <iostream>
#include <algorithm>

int findGcd(int a, int b) {
    while (b != 0) {
        if (b > a) {
            std::swap(a, b);
        }

        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void optimizeFraction(int& a, int& b) {
    int gcd = findGcd(a, b);
    a = a / gcd;
    b = b / gcd;
}

struct Fraction {
    int num_, del_;
    Fraction(int a = 0, int b = 1) {
        num_ = a;
        del_ = b;
    }

    Fraction(const Fraction& other) {
        num_ = other.num_;
        del_ = other.del_;
    }

    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            num_ = other.num_;
            del_ = other.del_;
        }
        return *this;
    }

    Fraction operator+ (const Fraction& other) {
        int tempnum_ = other.num_;
        int tempdel_ = other.del_;
        num_ = num_ * other.del_;
        tempnum_ = other.num_ * del_;
        tempdel_ = del_ * other.del_;
        num_ = num_ + tempnum_;
        del_ = tempdel_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator+= (const Fraction& other) {
        int tempnum_ = other.num_;
        int tempdel_ = other.del_;
        num_ = num_ * other.del_;
        tempnum_ = other.num_ * del_;
        tempdel_ = del_ * other.del_;
        num_ = num_ + tempnum_;
        del_ = tempdel_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator++(int) {
        num_ = num_ + del_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator- (const Fraction& other) {
        int tempnum_ = other.num_;
        int tempdel_ = other.del_;
        num_ = num_ * other.del_;
        tempnum_ = other.num_ * del_;
        tempdel_ = del_ * other.del_;
        num_ = num_ - tempnum_;
        del_ = tempdel_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator-= (const Fraction& other) {
        int tempnum_ = other.num_;
        int tempdel_ = other.del_;
        num_ = num_ * other.del_;
        tempnum_ = other.num_ * del_;
        tempdel_ = del_ * other.del_;
        num_ = num_ - tempnum_;
        del_ = tempdel_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator--(int) {
        num_ = num_ - del_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator* (const Fraction& other) {
        num_ = num_ * other.num_;
        del_ = del_ * other.del_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator*= (const Fraction& other) {
        num_ = num_ * other.num_;
        del_ = del_ * other.del_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator/ (const Fraction& other) {
        num_ = num_ * other.del_;
        del_ = del_ * other.num_;
        optimizeFraction(num_, del_);
        return *this;
    }

    Fraction operator/= (const Fraction& other) {
        num_ = num_ * other.del_;
        del_ = del_ * other.num_;
        optimizeFraction(num_, del_);
        return *this;
    }

    bool operator> (const Fraction& f) {
        double a, b;
        a = double(num_) / double(del_);
        b = double(f.num_) / double(f.del_);
        if (a > b) {
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator>= (const Fraction& f) {
        double a, b;
        a = double(num_) / double(del_);
        b = double(f.num_) / double(f.del_);
        if (a >= b) {
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator< (const Fraction& f) {
        double a, b;
        a = double(num_) / double(del_);
        b = double(f.num_) / double(f.del_);
        if (a < b) {
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator<= (const Fraction& f) {
        double a, b;
        a = double(num_) / double(del_);
        b = double(f.num_) / double(f.del_);
        if (a <= b) {
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator== (const Fraction& f) {
        double a, b;
        a = double(num_) / double(del_);
        b = double(f.num_) / double(f.del_);
        if (a == b) {
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator!= (const Fraction& f) {
        double a, b;
        a = double(num_) / double(del_);
        b = double(f.num_) / double(f.del_);
        if (a != b) {
            return 1;
        }
        else {
            return 0;
        }
    }

    operator int() const {
        return num_ / del_;
    }

    operator double() const {
        return static_cast<double>(num_) / del_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.num_ << "/" << f.del_;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& f) {
        char slashCollector;
        is >> f.num_ >> slashCollector >> f.del_;
        return is;
    }
};

bool compareFractionsUp(const Fraction& a, const Fraction& b) {
    return a.num_ * b.del_ < b.num_ * a.del_;
}

bool compareFractionsDown(const Fraction& a, const Fraction& b) {
    return a.num_ * b.del_ > b.num_ * a.del_;
}

void outputArray(Fraction* array, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Fraction f(5, 3);
    Fraction f1(4, 3);

    int size = 3;
    Fraction array[] = { Fraction(1, 2), Fraction(3, 4), Fraction(2, 5) };
    outputArray(array, size);
    std::sort(array, array + size, compareFractionsUp);
    std::cout << "Отсортировано по возрастанию: ";
    outputArray(array, size);
    std::sort(array, array + size, compareFractionsDown);
    std::cout << "Отсортировано по убыванию: ";
    outputArray(array, size);
}
