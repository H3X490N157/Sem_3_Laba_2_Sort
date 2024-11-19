#ifndef BATCHSORTER_H
#define BATCHSORTER_H

#include "ISorter.h"

template <typename T>
class BatchSorter : public ISorter<T> {
private:
    void BitonicSort(Sequence<T>* seq, int low, int cnt, bool ascending, int (*cmp)(const T&, const T&)) {
        if (cnt > 1) {
            int k = cnt / 2;
            BitonicSort(seq, low, k, true, cmp);
            BitonicSort(seq, low + k, k, false, cmp);
            BitonicMerge(seq, low, cnt, ascending, cmp);
        }
    }

    void BitonicMerge(Sequence<T>* seq, int low, int cnt, bool ascending, int (*cmp)(const T&, const T&)) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; ++i) {
                if (ascending == (cmp(seq->Get(i), seq->Get(i + k)) > 0)) {
                    std::swap(seq->Get(i), seq->Get(i + k));
                }
            }
            BitonicMerge(seq, low, k, ascending, cmp);
            BitonicMerge(seq, low + k, k, ascending, cmp);
        }
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->GetLength();
        BitonicSort(seq, 0, n, true, cmp);
        return seq;
    }
};

#endif // BATCHSORTER_H
