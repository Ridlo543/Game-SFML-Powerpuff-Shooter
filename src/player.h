// file player.h
#pragma once
#include "enemyManager.h"

class Player : public Entity
{
private:
    sf::Vector2f position;    // posisi saat ini dari pemain
    sf::Vector2f movementDir; // arah pergerakan dari pemain
    sf::Vector2f windowSize;  // ukuran window game
    float moveSpeed = 400.f;  // kecepatan pergerakan dari pemain
    int health = 100;         // kesehatan dari pemain
    int characterType = 0;    // tipe karakter dari pemain (0, 1, atau 2)

    // sprites dan textures
    // terdapat 3 karakter. Sehingga ada 3 set texture.
    sf::Texture idleTexture[3], walkTexture[3], deathTexture[3], shadowTex;
    sf::Sprite idleSprite, walkSprite, deathSprite;
    sf::SoundBuffer deathSoundBuf, hurtSoundBuf;
    sf::Sound deathSound, hurtSound;

    std::string charTexureFileName = "assets/characters/"; // nama file dari texture karakter

    int subTexRectSize = 75;               // ukuran dari setiap sub-texture
    int currIdleTex = 0, maxIdleTex = 6;   // indeks saat ini dan maksimum indeks untuk animasi idle
    int currWalkTex = 0, maxWalkTex = 8;   // indeks saat ini dan maksimum indeks untuk animasi berjalan
    int currDeathTex = 0, maxDeathTex = 8; // indeks saat ini dan maksimum indeks untuk animasi kematian

    // ukuran skala sprite, offset posisi sprite, dan ukuran hitbox
    sf::Vector2f scaleSize = sf::Vector2f(1, 1), spritePosOffset = sf::Vector2f(0, 0), colRectSize = sf::Vector2f(50, 75);
    // animasi
    bool playerIdle = true, flipped = false, gunBehindPlayer = false, hitAnimated = true, deathAnimEnd = false;
    float idleAnimTime = 0.2f, idleAnimTimer = 0.f;
    float walkAnimTime = 0.07f, walkAnimTimer = 0.f;
    float deathAnimTime = 0.08f, deathAnimTimer = 0.f;
    float deathSceneKeepTimer = 0;

public:
    sf::Sprite playerSprite, shadow;
    bool isDead = false;         // apakah player sudah mati
    bool deathSceneEnd = false;  // apakah animasi kematian sudah selesai
    bool resourceLoaded = false; // apakah sumber daya sudah diload

    Player(sf::Vector2f startingPos, sf::Vector2f windowSize); // constructor

    void load(void); // fungsi untuk memuat sumber daya
    // mengupdate posisi dan status player,
    void update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets, Weapons &weapon); // fungsi update
    void setCharacterType(int type);

    int getCharacterType(void); // mengubah tipe karakter,
    int getHealth(void);        // mendapatkan tipe karakter dan health player,
    void resetStates(void);     // mereset status player.

    // mengatur animasi player saat idle, walk, dan death.
    void animateIdle(float dt, sf::Vector2f requiredScale);
    void animateWalk(float dt);
    void animateDeath(float dt);

    // untuk menggambar player ke dalam window.
    void draw(sf::RenderWindow &window, Weapons wp, int gameState);
};
