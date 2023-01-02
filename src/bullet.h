// file bullet.h
#pragma once
#include "collision.h"
#include <cmath>

// deklarasi texture yang akan digunakan untuk bullet dan fireball
static sf::Texture bulletTexture;
static sf::Texture fireBallTexture;

// kelas Bullet merupakan turunan dari kelas Entity
class Bullet : public Entity
{
private:
    float bulletSize = 15.f;        // ukuran bullet
    float speed = 1000.f;           // kecepatan bullet
    float fireAngle = 0.f;          // sudut peluru terhadap sumbu x
    int bulletType = 0;             // tipe peluru (0 = peluru biasa, 1 = fireball)
    int rectY = 0;                  // frame yang sedang ditampilkan pada sprite fireball
    float fireballAnimTime = 0.05f; // waktu yang diperlukan untuk mengubah frame pada sprite fireball
    float animTimer = 0.f;          // timer untuk mengatur frame pada sprite fireball

public:
    // sprite untuk menampilkan bullet atau fireball
    sf::Sprite sprite;

    Bullet();  // default constructor
    ~Bullet(); // destructor

    Bullet(sf::Vector2f position, int bulletType); // constructor dengan parameter

    void setFireAngle(float angle); // setter untuk sudut peluru terhadap sumbu x
    void update(float dt);          // update posisi peluru
    void animateFireball(float dt); // animasi pada sprite fireball
};
