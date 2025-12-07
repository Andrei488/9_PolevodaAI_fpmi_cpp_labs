#include <vector_impl.h>
#include <initializer_list>
#include <stdexcept>
#include <ostream>


void Vector::reallocate(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    for (size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

Vector::Vector(size_t size) : size_(size), capacity_(size > 0 ? size : 0) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = 0;
        }
    }
}

Vector::Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(list.size()) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        size_t i = 0;
        for (int value : list) {
            data_[i++] = value;
        }
    }
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        if (capacity_ > 0) {
            data_ = new int[capacity_];
            for (size_t i = 0; i < size_; i++) {
                data_[i] = other.data_[i];
            }
        } else {
            data_ = nullptr;
        }
    }
    return *this;
}

void Vector::Swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

int& Vector::operator[](size_t index) {
    return data_[index];
}

const int& Vector::operator[](size_t index) const {
    return data_[index];
}

int& Vector::At(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

const int& Vector::At(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

size_t Vector::Size() const {
    return size_;
}

size_t Vector::Capacity() const {
    return capacity_;
}

void Vector::PushBack(int value) {
    if (size_ >= capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(new_capacity);
    }
    data_[size_++] = value;
}

void Vector::PopBack() {
    if (size_ > 0) {
        size_--;
    }
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        reallocate(new_capacity);
    }
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size_; i++) {
        os << vec.data_[i];
        if (i != vec.size_ - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

Vector::~Vector() {
    delete[] data_;
}