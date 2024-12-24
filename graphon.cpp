#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

// Функция для паузы (имитация анимации)
inline void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Визуализация массива
inline void drawArray(sf::RenderWindow &window, const std::vector<int> &array, int highlight1 = -1, int highlight2 = -1) {
    window.clear(sf::Color::Black);

    float width = window.getSize().x / static_cast<float>(array.size());
    float heightScale = window.getSize().y / *std::max_element(array.begin(), array.end());

    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(width - 2, array[i] * heightScale));
        bar.setPosition(i * width, window.getSize().y - bar.getSize().y);

        // Выделение элементов
        if (i == highlight1 || i == highlight2)
            bar.setFillColor(sf::Color::Red);
        else
            bar.setFillColor(sf::Color::White);

        window.draw(bar);
    }

    window.display();
}

// Пузырьковая сортировка с визуализацией
void bubbleSort(std::vector<int> &array, sf::RenderWindow &window) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        for (size_t j = 0; j < array.size() - i - 1; ++j) {
            drawArray(window, array, j, j + 1);
            sleep(50); // Пауза для анимации

            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                drawArray(window, array, j, j + 1);
                sleep(50); // Пауза для анимации
            }
        }
    }
}

int main() {
    // Инициализация массива
    std::vector<int> array = {100, 300, 200, 400, 50, 250, 150, 350};

    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Visualization");

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Запуск визуализации сортировки
        bubbleSort(array, window);

        // Отображение отсортированного массива
        drawArray(window, array);
        sleep(3000); // Задержка перед завершением
        window.close();
    }

    return 0;
}