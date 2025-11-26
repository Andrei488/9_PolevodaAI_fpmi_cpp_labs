#include "vector_impl.h"
#pragma once
#include <initializer_list>
#include <stdexcept>
#include <ostream>

class Vector {
private:
    int* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 20;

    void reallocate(size_t new_capacity) {
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Vector() {
        data_ = new int[capacity_];
    }

    Vector(size_t size) : size_(size), capacity_(2 * size) {
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = 0;
        }
    }

    Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(2 * list.size()) {
        data_ = new int[capacity_];
        size_t i = 0;
        for (int value : list) {
            data_[i++] = value;
        }
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    Vector& operator=(const Vector& other) {
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

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    int& operator[](size_t index) {
        return data_[index];
    }

    const int& operator[](size_t index) const {
        return data_[index];
    }

    int& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const int& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void push_back(int value) {
        if (size_ >= capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
        }
    }

    void clear() {
        size_ = 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            reallocate(new_capacity);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
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

    ~Vector() {
        delete[] data_;
    }
};
