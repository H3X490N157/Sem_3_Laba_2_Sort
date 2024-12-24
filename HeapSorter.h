#ifndef HEAPSORTER_H
#define HEAPSORTER_H
#pragma once

#include "ISorter.h"
#include "slep.h"

template <typename T>
class HeapSorter : public ISorter<T> {
private:
    void Heapify(std::vector<T>& vec, int n, int i, int (*cmp)(const T&, const T&), sf::RenderWindow& window) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && cmp(vec[left], vec[largest]) > 0)
            largest = left;

        if (right < n && cmp(vec[right], vec[largest]) > 0)
            largest = right;

        if (largest != i) {
            std::swap(vec[i], vec[largest]);
            drawArray(window, vec, i, largest);
            slep(50);

            Heapify(vec, n, largest, cmp, window);
        }
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->GetLength();
        std::vector<T> vec(n);

        // Копирование данных из Sequence в vector
        for (int i = 0; i < n; ++i) {
            vec[i] = seq->Get(i);
        }

        sf::RenderWindow window(sf::VideoMode(800, 600), "Heap Sort Visualization");

        // Построение кучи
        for (int i = n / 2 - 1; i >= 0; --i) {
            Heapify(vec, n, i, cmp, window);
        }

        // Сортировка
        for (int i = n - 1; i > 0; --i) {
            std::swap(vec[0], vec[i]);
            drawArray(window, vec, 0, i);
            slep(50);

            Heapify(vec, i, 0, cmp, window);
        }

        // Копирование данных обратно в Sequence
        for (int i = 0; i < n; ++i) {
            seq->operator[](i) = vec[i];
        }

        return seq;
    }
};

#endif // HEAPSORTER_H
