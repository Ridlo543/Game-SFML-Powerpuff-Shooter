#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Entity : public sf::RectangleShape
{
public:
    // Method untuk mengecek apakah objek ini bersentuhan dengan objek lain
    bool isColliding(Entity &other)
    {
        return this->getGlobalBounds().intersects(other.getGlobalBounds());
    }
};