#ifndef HeapSORTER_H
#define HeapSORTER_H
#pragma once 
#include "ISorter.h"

template <typename T>
class HeapSorter : public ISorter<T> {
private:
    void Heapify(T* arr, int n, int i, int (*cmp)(const T&, const T&)) {
        int largest = i;          // Инициализируем наибольший элемент как корень
        int left = 2 * i + 1;     // Левый потомок
        int right = 2 * i + 2;    // Правый потомок

        // Если левый потомок больше корня
        if (left < n && cmp(arr[left], arr[largest]) > 0)
            largest = left;

        // Если правый потомок больше текущего наибольшего
        if (right < n && cmp(arr[right], arr[largest]) > 0)
            largest = right;

        // Если наибольший элемент не корень
        if (largest != i) {
            std::swap(arr[i], arr[largest]); // Меняем местами

            // Рекурсивно вызываем Heapify для затронутого поддерева
            Heapify(arr, n, largest, cmp);
        }
    }

public:
    // Переопределяем Sort, принимая абстрактный тип Sequence<T>, а не ArraySequence
    Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->GetLength();

        // Создаем массив для сортировки
        T* Heap = new T[n];
        for (int i = 0; i < n; i++) {
            Heap[i] = seq->Get(i); // Копируем элементы
        }

        // Строим кучу (перегруппируем массив)
        for (int i = n / 2 - 1; i >= 0; i--) {
            Heapify(Heap, n, i, cmp);
        }

        // Один за другим извлекаем элементы из кучи
        for (int i = n - 1; i > 0; i--) {
            // Перемещаем текущий корень в конец
            std::swap(Heap[0], Heap[i]);

            // Вызываем Heapify на уменьшенной куче
            Heapify(Heap, i, 0, cmp);
        }

        // Перезаписываем отсортированные элементы в последовательность
        // Прямо через индексатор или аналогичный метод
        ArraySequence<T>* arraySeq = dynamic_cast<ArraySequence<T>*>(seq);
        if (arraySeq) {
            for (int i = 0; i < n; i++) {
                (*arraySeq)[i] = Heap[i];  // Индексация через оператор [] (предполагаем, что есть индексатор)
            }
        }

        delete[] Heap; // Освобождаем память
        return seq; // Возвращаем обновленную последовательность
    }
};

#endif // HeapSORTER_H