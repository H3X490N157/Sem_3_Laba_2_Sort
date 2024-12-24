#ifndef QUICKSORTER_H
#define QUICKSORTER_H
#pragma once

#include "ISorter.h"
#include "slep.h"

template <typename T>
class QuickSorter : public ISorter<T> {
private:
    int Partition(std::vector<T>& vec, int low, int high, int (*cmp)(const T&, const T&), sf::RenderWindow& window) {
        T pivot = vec[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (cmp(vec[j], pivot) < 0) {
                ++i;
                std::swap(vec[i], vec[j]);
                drawArray(window, vec, i, j);
                slep(50);
            }
        }
        std::swap(vec[i + 1], vec[high]);
        drawArray(window, vec, i + 1, high);
        slep(50);
        return i + 1;
    }

    void QuickSort(std::vector<T>& vec, int low, int high, int (*cmp)(const T&, const T&), sf::RenderWindow& window) {
        if (low < high) {
            int pi = Partition(vec, low, high, cmp, window);
            QuickSort(vec, low, pi - 1, cmp, window);
            QuickSort(vec, pi + 1, high, cmp, window);
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

        sf::RenderWindow window(sf::VideoMode(800, 600), "Quick Sort Visualization");

        QuickSort(vec, 0, vec.size() - 1, cmp, window);

        // Копирование данных обратно в Sequence
        for (int i = 0; i < n; ++i) {
            seq->operator[](i) = vec[i];
        }

        return seq;
    }
};

#endif // QUICKSORTER_H
