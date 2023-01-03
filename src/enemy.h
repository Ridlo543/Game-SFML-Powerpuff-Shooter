#pragma once
#include "weapon.h"

class Enemy : public Collision
{
private:
    sf::Vector2f position;
    int health = 100;

public:
    sf::Sprite sprite, shadowSprite;
    int currWalkTex = 0, maxWalkTex = 8;
    float walkAnimTime = 0.08f, walkAnimTimer = 0.f;
    bool flipped = false;
    bool inNearestPoint = false;
    int enemyType; // untuk record sprite type
    sf::Color deathShadowColor;

    Enemy(sf::Vector2f pos, sf::Vector2f size, sf::Sprite sprite, sf::Sprite shaodw, int type);

    int getHealth(void);                                                       // fungsi untuk mendapatkan health
    void update(float dt, sf::Vector2f playerPos, Weapons &w, Camera &camera); // fungsi untuk mengupdate posisi enemy dan menangani animasi
    void draw(sf::RenderWindow &window);                                       // fungsi untuk menggambar sprite enemy
};