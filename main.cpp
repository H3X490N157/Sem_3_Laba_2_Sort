#include <iostream>
#include <vector>
#include <cassert>
#include "ArraySequence.h" 
#include "HeapSorter.h"    
#include "ShellSorter.h"   
#include "QuickSorter.h"   
#include "ISorter.h"       

// Функция для вывода последовательности
template <typename T>
void printSequence(const Sequence<T>* seq) {
    for (int i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i) << " ";
    }
    std::cout << "\n";
}

template <typename T>
void checkSorted(const Sequence<T>* seq) {
    for (int i = 1; i < seq->GetLength(); ++i) {
        assert(seq->Get(i-1) <= seq->Get(i) && "Ошибка сортировки!");
    }
    std::cout << "Успешно отсортировано\n";
}

template <typename T>
int compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Тестирование различных сортировок
template <typename T>
void testSorting(ISorter<T>& sorter, const char* sorterName) {
    std::cout << "Testing " << sorterName << "...\n";

    // Тест 1: Пустая последовательность
    ArraySequence<T> emptySequence;
    sorter.Sort(&emptySequence, compare);
    checkSorted(&emptySequence);

    // Тест 2: Одноэлементная последовательность
    ArraySequence<T> singleElementSequence;
    singleElementSequence.Append(42);
    sorter.Sort(&singleElementSequence, compare);
    checkSorted(&singleElementSequence);

    // Тест 3: Уже отсортированная последовательность
    ArraySequence<T> sortedSequence;
    sortedSequence.Append(1);
    sortedSequence.Append(2);
    sortedSequence.Append(3);
    sorter.Sort(&sortedSequence, compare);
    checkSorted(&sortedSequence);

    // Тест 4: Обратная последовательность
    ArraySequence<T> reversedSequence;
    reversedSequence.Append(3);
    reversedSequence.Append(2);
    reversedSequence.Append(1);
    sorter.Sort(&reversedSequence, compare);
    checkSorted(&reversedSequence);

    // Тест 5: Случайная последовательность
    ArraySequence<T> randomSequence;
    randomSequence.Append(10);
    randomSequence.Append(2);
    randomSequence.Append(8);
    randomSequence.Append(5);
    randomSequence.Append(3);
    randomSequence.Append(-2281337);
    sorter.Sort(&randomSequence, compare);
    checkSorted(&randomSequence);\

    ArraySequence<T> anotherSequence;
    anotherSequence.Append('Wow');
    anotherSequence.Append('I hate BTS');
    sorter.Sort(&anotherSequence, compare);
    checkSorted(&anotherSequence);

}

int main() {
    HeapSorter<int> heapSorter;
    ShellSorter<int> shellSorter;
    QuickSorter<int> quickSorter;

    testSorting(heapSorter, "HeapSort");
    testSorting(shellSorter, "ShellSort");
    testSorting(quickSorter, "QuickSort");

    std::cout << "All tests passed successfully!\n";
    return 0;
}
