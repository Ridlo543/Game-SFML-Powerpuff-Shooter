#pragma once
#include "enemy.h"

class EnemyManager
{
private:
    sf::Vector2f windowSize;
    float enemyReloadTime = 1.f; // Waktu untuk mengisi kembali ulang senjata musuh
    float spawnTime = 1.f;       // Waktu untuk menghasilkan musuh
    float spawnnigTimer = 0.f;   // Timer untuk menghasilkan musuh
    float reloadingTimer = 0.f;  // Timer untuk mengisi ulang senjata musuh
    float moveSpeed = 300.f;     // Kecepatan bergerak musuh
    int maxNumberOfEnemy = 5;    // Jumlah maksimum musuh
    int numberOfEnemy = 0;       // Jumlah saat ini musuh
    bool maxEnemySpawnd = false; // Apakah jumlah maksimum musuh telah muncul?

    // sprite dan tekstur
    sf::Texture walkTextures[4], genericDeathTex, shadowTex;                                                               // Tekstur untuk berjalan, mati umum, dan bayangan
    sf::Sprite enemyWalkSprites[4], shadow;                                                                                // Sprite untuk berjalan, mati umum, dan bayangan
    sf::Sprite genericDeathSprite;                                                                                         // Sprite untuk mati umum
    sf::Vector2f scaleSize = sf::Vector2f(1, 1), spritePosOffset = sf::Vector2f(0, 0), colRectSize = sf::Vector2f(40, 80); // Skala, offset sprite, dan ukuran kolom
    sf::SoundBuffer hurtBuf;                                                                                               // Buffer untuk suara cedera
    sf::Sound hurt;                                                                                                        // Suara cedera

    int subTexRectSize = 75;        // Ukuran sub-rect teks
    int minDistBtPlayerEnemy = 450; // Jarak minimal antara pemain dan musuh

    std::list<std::pair<sf::Sprite, float>> deathShadows; // Daftar bayangan kematian

public:
    std::vector<int> killScores;    // Skor pembunuhan
    std::list<Enemy> enemies;       // Daftar musuh
    std::list<Bullet> enemyBullets; // Daftar peluru musuh
    sf::Sprite enemySprite;         // Sprite musuh
    bool resourceLoaded = false;    // Apakah sumber daya telah dimuat?

    EnemyManager(sf::Vector2f windowSize);
    void load(void);                                                         // Memuat sumber daya
    void shoot(sf::Vector2f playerPos, Enemy enemy, float dt);               // Menembak musuh
    void spawnEnemies(sf::Vector2f playerPos, Camera view);                  // Menghasilkan musuh
    void update(float dt, Weapons &w, sf::Vector2f playerPos, Camera &view); // Memperbarui musuh
    void moveEnemy(float dt, sf::Vector2f playerPos, Enemy &e);              // Memindahkan musuh
    void animateWalk(float dt, Enemy &e);                                    // Animasi berjalan musuh
    bool ifOutsizeView(Bullet b, Camera view);                               // Apakah peluru berada di luar pandangan?
    void resetStates(void);                                                  // Mereset status
    void drawEnemies(sf::RenderWindow &window);                              // Menggambar musuh
};