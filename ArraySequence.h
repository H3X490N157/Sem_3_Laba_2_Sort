#include "sequence.h"
#include <stdexcept>
#include <iostream>

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    T* data;      
    int size;         
    int capacity;     

    void Resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    ArraySequence() : data(nullptr), size(0), capacity(0) {}

    ~ArraySequence() {
        delete[] data;
    }

    T& GetFirst() override {
        if (size == 0) throw std::out_of_range("Пусто");
        return data[0];
    }

    T& GetLast() override {
        if (size == 0) throw std::out_of_range("Пусто");
        return data[size - 1];
    }

    T& Get(int index) override {
        if (index < 0 || index >= size) throw std::out_of_range("Некорректный индекс");
        return data[index];
    }

    T& operator[](int index) override {
        return Get(index);
    }

    int GetLength() override {
        return size;
    }

    void Append(T item) override {
        if (size == capacity) {
            Resize((capacity == 0) ? 1 : capacity * 2);
        }
        data[size++] = item;
    }

    void Prepend(T item) override {
        if (size == capacity) {
            Resize((capacity == 0) ? 1 : capacity * 2);
        }
        for (int i = size; i > 0; --i) {
            data[i] = data[i - 1];
        }
        data[0] = item;
        ++size;
    }

    void InsertAt(T item, int index) override {
        if (index < 0 || index > size) throw std::out_of_range("Некорректный индекс");
        if (size == capacity) {
            Resize((capacity == 0) ? 1 : capacity * 2);
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = item;
        ++size;
    }
};
