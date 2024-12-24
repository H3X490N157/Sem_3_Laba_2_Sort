#ifndef SHELLSORTER_H
#define SHELLSORTER_H
#pragma once

#include "ISorter.h"
#include "slep.h"


template <typename T>
class ShellSorter : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->GetLength();
        std::vector<T> vec(n);

        // Копирование данных из Sequence в vector
        for (int i = 0; i < n; ++i) {
            vec[i] = seq->Get(i);
        }

        sf::RenderWindow window(sf::VideoMode(800, 600), "Shell Sort Visualization");

        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                T temp = vec[i];
                int j;
                for (j = i; j >= gap && cmp(vec[j - gap], temp) > 0; j -= gap) {
                    vec[j] = vec[j - gap];
                    drawArray(window, vec, j, j - gap);
                    slep(50);
                }
                vec[j] = temp;
                drawArray(window, vec, j, i);
                slep(50);
            }
        }

        // Копирование данных обратно в Sequence
        for (int i = 0; i < n; ++i) {
            seq->operator[](i) = vec[i];
        }

        return seq;
    }
};

#endif // SHELLSORTER_H
