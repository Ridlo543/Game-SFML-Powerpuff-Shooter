#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Collision : public sf::RectangleShape
{
public:
    // Method untuk mengecek apakah objek ini bersentuhan dengan objek lain
    bool isColliding(Collision &other)
    {
        return this->getGlobalBounds().intersects(other.getGlobalBounds());
    }
};