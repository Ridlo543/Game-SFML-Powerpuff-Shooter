#include "enemy.h"

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size, sf::Sprite sprite, sf::Sprite shaodw, int type)
{
    position = pos;
    this->setSize(size);
    this->setOrigin(this->getSize().x / 2, this->getSize().y / 2);
    this->setPosition(position);
    this->sprite = sprite;
    this->shadowSprite = shaodw;
    this->inNearestPoint = false;
    this->enemyType = type;

    switch (enemyType)
    {
    case 0:
        // mengatur warna shadow ketika musuh mati
        this->deathShadowColor = sf::Color(131, 68, 151, 255);
        break;
    case 1:
        this->deathShadowColor = sf::Color(186, 216, 96, 255);
        break;
    case 2:
        this->deathShadowColor = sf::Color(203, 176, 90, 255);
        break;
    case 3:
        this->deathShadowColor = sf::Color(216, 100, 96, 255);
        break;
    default:
        break;
    }
}

int Enemy::getHealth(void)
{
    return health;
}

// memperbarui posisi musuh
void Enemy::update(float dt, sf::Vector2f playerPos, Weapons &w, Camera &camera)
{
    flipped = (playerPos.x < this->getPosition().x) ? true : false;

    auto i = w.bullets.begin();
    while (i != w.bullets.end())
    {
        if (this->isColliding(*i))
        {
            this->health -= 50;
            camera.triggerShake = true;
            i = w.bullets.erase(i);
        }
        else
            i++;
    }
}

// membuat musuh di layar
void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(*this);
}