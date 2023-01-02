// File bullet.cpp
// Fungsi-fungsi yang didefinisikan dalam file header bullet.h
#include "bullet.h"
#include <iostream>

// Constructor default untuk kelas Bullet
// Menginisialisasi tekstur bullet dan fireball
Bullet::Bullet()
{
    bulletTexture.loadFromFile("assets/Extras/bullet.png");     // Muat tekstur bullet dari file
    fireBallTexture.loadFromFile("assets/Extras/fireball.png"); // Muat tekstur fireball dari file
}

// Destructor untuk kelas Bullet
Bullet::~Bullet()
{
    // std::cout << "bullet_destroyed";
}

// Constructor dengan parameter untuk kelas Bullet
// Menginisialisasi posisi, ukuran, dan jenis bullet
Bullet::Bullet(sf::Vector2f position, int bulletType)
{
    this->bulletType = bulletType;                       // Set jenis bullet sesuai parameter
    this->setSize(sf::Vector2f(bulletSize, bulletSize)); // Set ukuran bullet
    this->setOrigin(bulletSize / 2, bulletSize / 2);     // Set titik tengah bullet
    this->setFillColor(sf::Color::Red);                  // Set warna bullet
    this->setPosition(position);                         // Set posisi awal bullet

    /// Jika jenis bullet adalah 1 (bullet biasa)
    if (this->bulletType == 1)
    {
        // Mengatur texture, origin, dan scale sprite bullet
        this->sprite.setTexture(bulletTexture);
        this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
        this->sprite.setScale(0.018, 0.018);
    }
    // Jika jenis bullet adalah 2 (fireball)
    else if (this->bulletType == 2)
    {
        // Mengatur texture, texture rect, origin, dan scale sprite fireball
        this->sprite.setTexture(fireBallTexture);
        this->sprite.setTextureRect(sf::IntRect(0, 0, 500, 160));
        this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2 + this->sprite.getGlobalBounds().width / 4, this->sprite.getGlobalBounds().height / 2);
        this->sprite.setScale(0.25, 0.25);
    }

    this->sprite.setPosition(position); // Mengatur posisi sprite bullet sesuai dengan posisi yang diberikan pada saat inisialisasi object bullet.
}

// Fungsi ini digunakan untuk mengatur sudut api
void Bullet::setFireAngle(float angle)
{
    fireAngle = angle;                                    // Atur sudut api ke angle yang diberikan
    this->sprite.setRotation(fireAngle * (180 / 3.1415)); // Atur rotasi sprite sesuai sudut api yang diberikan, dengan konversi radian ke derajat
}

// Fungsi ini digunakan untuk memperbarui posisi peluru
void Bullet::update(float dt)
{
    // Pindahkan posisi peluru dengan menggunakan vektor gerak yang dihitung dari sudut api
    this->move(std::cos(fireAngle) * dt * speed, 0);
    this->move(0, std::sin(fireAngle) * dt * speed);
    this->sprite.move(std::cos(fireAngle) * dt * speed, 0);
    this->sprite.move(0, std::sin(fireAngle) * dt * speed);
    // Jika jenis peluru adalah 2 (fireball), maka jalankan animasi fireball
    if (this->bulletType == 2)
        animateFireball(dt);
}

// Fungsi ini digunakan untuk mengatur animasi fireball
void Bullet::animateFireball(float dt)
{
    animTimer += dt; // Tambahkan waktu ke animasi timer
    // Jika animasi timer telah mencapai batas waktu animasi, lakukan perubahan texture rectangle dan reset timer
    if (animTimer > fireballAnimTime)
    {
        animTimer = 0;

        // Atur texture rectangle yang akan digunakan
        rectY += 160;
        // Jika telah mencapai frame terakhir, kembali ke frame pertama
        if (rectY > 160 * 4)
            rectY = 0;
        this->sprite.setTextureRect(sf::IntRect(0, rectY, 500, 160));
    }
}