#ifndef HeapSORTER_H
#define HeapSORTER_H
#pragma once 
#include "ISorter.h"

template <typename T>
class HeapSorter : public ISorter<T> {
private:
    void Heapify(T* arr, int n, int i, int (*cmp)(const T&, const T&)) {
        int largest = i;         
        int left = 2 * i + 1;    
        int right = 2 * i + 2;    

        if (left < n && cmp(arr[left], arr[largest]) > 0)
            largest = left;

        if (right < n && cmp(arr[right], arr[largest]) > 0)
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]); 

            Heapify(arr, n, largest, cmp);
        }
    }

public:
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->GetLength();

        T* Heap = new T[n];
        for (int i = 0; i < n; i++) {
            Heap[i] = seq->Get(i); 
        }

        for (int i = n / 2 - 1; i >= 0; i--) {
            Heapify(Heap, n, i, cmp);
        }

        for (int i = n - 1; i > 0; i--) {
            std::swap(Heap[0], Heap[i]);
            Heapify(Heap, i, 0, cmp);
        }

        ArraySequence<T>* arraySeq = dynamic_cast<ArraySequence<T>*>(seq);
        if (arraySeq) {
            for (int i = 0; i < n; i++) {
                (*arraySeq)[i] = Heap[i]; 
            }
        }

        delete[] Heap;
        return seq;
    }
};

#endif // HeapSORTER_H