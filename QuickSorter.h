#ifndef QUICKSORTER_H
#define QUICKSORTER_H

#include "ISorter.h"

template <typename T>
class QuickSorter : public ISorter<T> {
private:
    void QuickSort(Sequence<T>* seq, int low, int high, int (*cmp)(const T&, const T&)) {
        if (low < high) {
            int pivotIndex = Partition(seq, low, high, cmp);
            QuickSort(seq, low, pivotIndex - 1, cmp);
            QuickSort(seq, pivotIndex + 1, high, cmp);
        }
    }

    int Partition(Sequence<T>* seq, int low, int high, int (*cmp)(const T&, const T&)) {
        T pivot = seq->Get(high);
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (cmp(seq->Get(j), pivot) < 0) {
                ++i;
                std::swap(seq->Get(i), seq->Get(j));
            }
        }
        std::swap(seq->Get(i + 1), seq->Get(high));
        return i + 1;
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        QuickSort(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};

#endif // QUICKSORTER_H
