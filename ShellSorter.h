#ifndef SHELLSORTER_H
#define SHELLSORTER_H

#include "ISorter.h"

template <typename T>
class ShellSorter : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->GetLength();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                T temp = seq->Get(i);
                int j;
                for (j = i; j >= gap && cmp(seq->Get(j - gap), temp) > 0; j -= gap) {
                    seq->Get(j) = seq->Get(j - gap);
                }
                seq->Get(j) = temp;
            }
        }
        return seq;
    }
};

#endif // SHELLSORTER_H
