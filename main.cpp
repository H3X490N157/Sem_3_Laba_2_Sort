#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include "ArraySequence.h" 
#include "HeapSorter.h"    
#include "ShellSorter.h"   
#include "QuickSorter.h"   
#include "ISorter.h"       
#include "printer.h"
#include "comparator.h"

template <typename T>
void checkSorted(const Sequence<T>* seq) {
    for (int i = 1; i < seq->GetLength(); ++i) {
        assert(seq->Get(i-1) <= seq->Get(i) && "Ошибка сортировки!");
    }
    std::cout << "Успешно отсортировано\n";
}

// Тестирование различных сортировок
template <typename T>
void testSorting(ISorter<T>& sorter, const char* sorterName) {
    std::cout << "Проверка " << sorterName << "...\n";

    // Тест 1: Пустая последовательность
    ArraySequence<T> emptySequence;
    sorter.Sort(&emptySequence, compare);
    checkSorted(&emptySequence);
    printSequence(&emptySequence);

    ArraySequence<T> singleElementSequence;
    singleElementSequence.Append(42);
    sorter.Sort(&singleElementSequence, compare);
    checkSorted(&singleElementSequence);
    printSequence(&singleElementSequence);

    ArraySequence<T> sortedSequence;
    sortedSequence.Append(1);
    sortedSequence.Append(2);
    sortedSequence.Append(3);
    sorter.Sort(&sortedSequence, compare);
    checkSorted(&sortedSequence);
    printSequence(&sortedSequence);

    ArraySequence<T> reversedSequence;
    reversedSequence.Append(3);
    reversedSequence.Append(2);
    reversedSequence.Append(1);
    sorter.Sort(&reversedSequence, compare);
    checkSorted(&reversedSequence);
    printSequence(&reversedSequence);

    ArraySequence<T> randomSequence;
    randomSequence.Append(10);
    randomSequence.Append(2);
    randomSequence.Append(8);
    randomSequence.Append(5);
    randomSequence.Append(3);
    randomSequence.Append(-2281337);
    sorter.Sort(&randomSequence, compare);
    checkSorted(&randomSequence);
    printSequence(&randomSequence);

}

// Тестирование строковых последовательностей
void testSorting(ISorter<std::string>& sorter, const char* sorterName) {
    std::cout << "Testing " << sorterName << " with strings...\n";

    ArraySequence<std::string> emptySequence;
    sorter.Sort(&emptySequence, compare<std::string>);
    checkSorted(&emptySequence);
    printSequence(&emptySequence);

    ArraySequence<std::string> singleElementSequence;
    singleElementSequence.Append("I am alone. HELLp");
    sorter.Sort(&singleElementSequence, compare<std::string>);
    checkSorted(&singleElementSequence);
    printSequence(&singleElementSequence);

    ArraySequence<std::string> reversedSequence;
    reversedSequence.Append("Cherry");
    reversedSequence.Append("Banana");
    reversedSequence.Append("Apple");
    sorter.Sort(&reversedSequence, compare<std::string>);
    checkSorted(&reversedSequence);
    printSequence(&reversedSequence);

    ArraySequence<std::string> randomSequence;
    randomSequence.Append("Zebra");
    randomSequence.Append("Apple");
    randomSequence.Append("Orange");
    randomSequence.Append("Banana");
    randomSequence.Append("Lemon");
    randomSequence.Append("Берёзовый сок");
    randomSequence.Append("Я не люблю BTS");
    sorter.Sort(&randomSequence, compare<std::string>);
    checkSorted(&randomSequence);
    printSequence(&randomSequence);
}



int main() {
    HeapSorter<int> heapSorter;
    ShellSorter<int> shellSorter;
    QuickSorter<int> quickSorter;


    HeapSorter<std::string> stringHeapSorter;
    ShellSorter<std::string> stringShellSorter;
    QuickSorter<std::string> stringQuickSorter;

    testSorting(heapSorter, "HeapSort");
    testSorting(shellSorter, "ShellSort");
    testSorting(quickSorter, "QuickSort");


    testSorting(stringHeapSorter, "HeapSort для строк");
    testSorting(stringShellSorter, "ShellSort для строк");
    testSorting(stringQuickSorter, "QuickSort для строк");

    std::cout << "Тесты пройдены\n";
    return 0;
}
