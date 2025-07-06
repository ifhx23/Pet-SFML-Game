#pragma once

#include <cmath>
#include <SFML/System.hpp>
// Функція для нормалізації вектора
inline sf::Vector2f normalize(const sf::Vector2f& v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0)
        return v / length;
    else
        return sf::Vector2f(0.f, 0.f);  // або обробити нульовий вектор іншим способом
}