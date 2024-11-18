#include "shared_pointer.h"
#include "DynamicArray.h"
#include "DynamicArray_tests.h"
#include "shared_pointer_tests.h"
#include "unique_pointer_tests.h"

void menu_base() {
    std::cout << "Меню:\n";
    std::cout << "1. Запустить всех тесты\n";
    std::cout << "2. Запустить тесты по названию\n";
    std::cout << "3. Создать свой тест для shared_pointer или unique_pointer\n";
    std::cout << "4 или любой иной вариант. Выход\n";
}

void full_tests_runs() {
    test_shared_pointer_constructor();
    test_shared_pointer_copy_constructor();
    test_shared_pointer_move_constructor();
    test_shared_pointer_assignment();
    test_shared_ptr_funcs();
    test_shared_ptr_compare();
    test_weak();
    test_move();
    test_swap();
    test_unique_pointer_constructor();
    test_unique_pointer_move_constructor();
    test_unique_ptr_funcs();
    test_unique_ptr_compare();
    test_DynamicArray_constructors();
    test_DynamicArray_set();
    test_DynamicArray_comparator();
    std::cout << "Это - успех!" << std::endl;
}

void test_named() {
    std::string test;
    std::cout << "Введите название теста без (): ";
    std::cin >> test;

    if (test == "test_shared_pointer_constructor") {
        test_shared_pointer_constructor();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_shared_pointer_copy_constructor") {
        test_shared_pointer_copy_constructor();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_shared_pointer_move_constructor") {
        test_shared_pointer_move_constructor();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_shared_pointer_assignment") {
        test_shared_pointer_assignment();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_shared_ptr_funcs") {
        test_shared_ptr_funcs();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_shared_ptr_compare") {
        test_shared_ptr_compare();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_weak") {
        test_weak();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_move") {
        test_move();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_swap") {
        test_swap();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_unique_pointer_constructor") {
        test_unique_pointer_constructor();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_unique_pointer_move_constructor") {
        test_unique_pointer_move_constructor();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_unique_ptr_funcs") {
        test_unique_ptr_funcs();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_unique_ptr_compare") {
        test_unique_ptr_compare();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_DynamicArray_constructors") {
        test_DynamicArray_constructors();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_DynamicArray_set") {
        test_DynamicArray_set();
        std::cout << "Это - успех!" << std::endl;
    } else if (test == "test_DynamicArray_comparator") {
        test_DynamicArray_comparator();
        std::cout << "Это - успех!" << std::endl;
    } else {
        std::cout << "Неправильной название теста" << std::endl;
    }
}

void shared_pointer_custom_test(shared_ptr<int>& ptr) {
    int choice;
    do {
        std::cout << "\nОперации в shared_pointer:\n";
        std::cout << "1. Получить значение\n";
        std::cout << "2. Установить новое значение\n";
        std::cout << "3. Скопировать\n";
        std::cout << "4. Выход\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Значение: " << *ptr << std::endl;
                break;
            case 2: {
                int value;
                std::cout << "Введите новое значение: ";
                std::cin >> value;
                *ptr = value;
                std::cout << "Успешный ввод значения." << std::endl;
                break;
            }
            case 3: {
                shared_ptr<int> copyPtr = ptr;
                std::cout << "Копия создана. Счётчик: " << copyPtr.get_usage_count() << std::endl;
                break;
            }
            default:
                choice = 4;
                break;
        }
    } while (choice != 4);
}

void manipulateUniquePointer(unique_ptr<int>& ptr) {
    int choice;
    do {
        std::cout << "\nОперации с unique pointerами:\n";
        std::cout << "1. Получить значение\n";
        std::cout << "2. Установить значение\n";
        std::cout << "3. Сбросить значение\n";
        std::cout << "4. Выход\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Значение: " << *ptr << std::endl;
                break;
            case 2: {
                int value;
                std::cout << "Введите новое значение: ";
                std::cin >> value;
                *ptr = value;
                std::cout << "Успешное изменение значения." << std::endl;
                break;
            }
            case 3:
                if (ptr == nullptr){
                    std::cout << "Указатель уже nullptr. Нет необходимости" << std::endl;
                    break;
                }
                ptr.reset();
                std::cout << "Указатель сброшен." << std::endl;
                break;
            case 4:
                break;
            default:
                std::cout << "Неправильный номер, попробуйте снова." << std::endl;
        }
    } while (choice != 4);
}

void create_custom_test() {
    int choice;
    std::cout << "Выберите, что создать\n";
    std::cout << "1. shared_pointer\n";
    std::cout << "2. unique_pointer\n";
    std::cin >> choice;

    if (choice == 1) {
        auto ptr = shared_ptr<int>(new int);
        std::cout << "Для создания shared введите его значение: ";
        std::cin >> *ptr;
        shared_pointer_custom_test(ptr);
    } else if (choice == 2) {
        auto ptr = unique_ptr<int>(new int);
        std::cout << "Для создания unique введите его значение ";
        std::cin >> *ptr;
        manipulateUniquePointer(ptr);
    } 
     else {
        std::cout << "Некорректный выбор" << std::endl;
    }
}

int main() {
    int choice;
    do {
        menu_base();
        std::cin >> choice;
        switch (choice) {
            case 1:
                full_tests_runs();
                break;
            case 2:
                test_named();
                break;
            case 3:
                create_custom_test();
                break;
            default:
                std::cout << "До свидания)" << std::endl;
                choice = 4;
        }
    } while (choice != 4);

    return 0;
}
