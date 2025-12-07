#pragma once
#include <cstddef>
#include <initializer_list>
#include <ostream>

class Vector {
private:
    int* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
    void reallocate(size_t new_capacity);

public:
    Vector() = default;
    explicit Vector(size_t size);
    Vector(std::initializer_list<int> list);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    int& At(size_t index);
    const int& At(size_t index) const;

    size_t Size() const;
    size_t Capacity() const;

    void PushBack(int value);
    void PopBack();
    void Clear();
    void Reserve(size_t new_capacity);
    void Swap(Vector& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
};