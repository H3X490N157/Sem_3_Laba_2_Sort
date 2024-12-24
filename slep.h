#pragma once

#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>
#include <algorithm>

inline void slep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

template <typename T>
void drawArray(sf::RenderWindow& window, const std::vector<T>& array, int width, int margin) {
    auto getValue = [](const T& value) -> float {
        if constexpr (std::is_arithmetic_v<T>) {
            return static_cast<float>(value);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return static_cast<float>(value.size());
        } else {
            // Предположим, что у класса T есть метод getHeight().
            return static_cast<float>(value.getHeight());
        }
    };

    float heightScale = static_cast<float>(window.getSize().y) / getValue(*std::max_element(array.begin(), array.end()));

    // Очистка экрана (черный фон)
    window.clear(sf::Color::Black);

    for (size_t i = 0; i < array.size(); ++i) {
        float barHeight = getValue(array[i]) * heightScale;
        sf::RectangleShape bar(sf::Vector2f(width - 2, barHeight));
        bar.setPosition(i * (width + margin), window.getSize().y - barHeight);
        window.draw(bar);
    }

    // Обновление экрана
    window.display();
    slep(100);
}

