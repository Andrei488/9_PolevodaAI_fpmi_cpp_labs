#pragma once
#include <initializer_list>
#include <stdexcept>
#include <ostream>

class Vector {
private:
    int* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 20;

    void reallocate(size_t new_capacity);

public:
    Vector();
    Vector(size_t size);
    Vector(std::initializer_list<int> list);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    void swap(Vector& other) noexcept;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    int& at(size_t index);
    const int& at(size_t index) const;

    size_t size() const;
    size_t capacity() const;

    void push_back(int value);
    void pop_back();
    void clear();
    void reserve(size_t new_capacity);

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);

    ~Vector();
};