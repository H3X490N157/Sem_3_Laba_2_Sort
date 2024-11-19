#include <iostream>
#include "ArraySequence.h"
#include "ShellSorter.h"
#include "BatchSorter.h"
#include "QuickSorter.h"

struct Person {
    std::string name;
    double height;

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " (" << p.height << " cm)";
        return os;
    }
};

int CompareByHeight(const Person& p1, const Person& p2) {
    if (p1.height < p2.height) return -1; // p1 меньше p2
    if (p1.height > p2.height) return 1;  // p1 больше p2
    return 0;                             // p1 и p2 равны
}

// Обёртка для приведения типов (принимает по значению, как требует Sort)
int CompareByHeightWrapper(const Person& a, const Person& b) {
    return CompareByHeight(a, b);
}


int main() {
    ArraySequence<Person> people;
    people.Append({"Alice", 165.5});
    people.Append({"Bob", 175.0});
    people.Append({"Charlie", 160.0});
    people.Append({"Dave", 180.0});

    // Вывод исходных данных
    std::cout << "Original data:\n";
    for (int i = 0; i < people.GetLength(); ++i) {
        std::cout << people.Get(i) << "\n";
    }

    // Сортировка QuickSort
    QuickSorter<Person> quickSorter;
    ArraySequence<Person> quickSortedPeople = people; // Создаем копию
    quickSorter.Sort(&quickSortedPeople, CompareByHeightWrapper);
    std::cout << "\nQuick Sort:\n";
    for (int i = 0; i < quickSortedPeople.GetLength(); ++i) {
        std::cout << quickSortedPeople.Get(i) << "\n";
    }

    // Сортировка ShellSort
    ShellSorter<Person> shellSorter;
    ArraySequence<Person> shellSortedPeople = people; // Создаем копию
    shellSorter.Sort(&shellSortedPeople, CompareByHeightWrapper);
    std::cout << "\nShell Sort:\n";
    for (int i = 0; i < shellSortedPeople.GetLength(); ++i) {
        std::cout << shellSortedPeople.Get(i) << "\n";
    }

    // Сортировка BatcherSort
    BatchSorter<Person> batchSorter;
    ArraySequence<Person> batchSortedPeople = people; // Создаем копию
    batchSorter.Sort(&batchSortedPeople, CompareByHeightWrapper);
    std::cout << "\nBatcher Sort:\n";
    for (int i = 0; i < batchSortedPeople.GetLength(); ++i) {
        std::cout << batchSortedPeople.Get(i) << "\n";
    }

    return 0;
}
