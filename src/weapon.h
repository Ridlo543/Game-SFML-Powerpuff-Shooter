#pragma once
#include "camera.h"

// Kelas ini merepresentasikan senjata yang digunakan oleh player dalam game
class Weapons
{
private:
    sf::Vector2f windowSize;                                                   // Variabel untuk menyimpan ukuran window
    sf::Texture pistolTex, rifelTex, shotgunTex, muzzleFlashTex, crosshairTex; // Variabel untuk menyimpan texture dari pistol, rifel, dan shotgun
    sf::Sprite pistol, rifel, shotgun;                                         // Variabel untuk menyimpan sprite dari pistol, rifel, dan shotgun
    sf::SoundBuffer pistolSoundBuf, rifelSoundBuf, shotgunSoundBuf;            // Variabel untuk menyimpan sound buffer dari suara pistol, rifel, dan shotgun
    sf::SoundBuffer pistolPickupBuf, rifelPickupBuf, shotgunPickupBuf;         // Variabel untuk menyimpan sound buffer dari suara pickup pistol, rifel, dan shotgun
    sf::Sound pistolSound, rifelSound, shotgunSound;                           // Variabel untuk menyimpan suara pistol, rifel, dan shotgun
    sf::Sound pistolPickup, rifelPickup, shotgunPickup;                        // Variabel untuk menyimpan suara pickup pistol, rifel, dan shotgun

    // Tipe senjata saat ini (pistol = 1, rifel = 2, shotgun = 3)
    int gunType = 1;
    float muzzleFlashTime = 0.1f;                                                    // Waktu munculnya muzzle flash
    float flashTimer = 0.f;                                                          // Timer untuk muzzle flash
    float pistolReloadTime = 0.2f, rifelReloadTime = 0.1f, shotGunReloadTime = 0.3f; // Waktu reload untuk masing-masing senjata
    float reloadTimer = 0.f;                                                         // Timer untuk reload senjata
    float gunSpawnTimeDelay = 5.f, gunEquippedTime = 10;                             // Waktu delay dan waktu bisa menggunakan senjata yang muncul di arena
    float gunSpawnTimer = 0.f, gunEquippedTimer = 0.f;
    bool gunSpawnned = false;

public:
    std::list<Bullet> bullets;                                               // Daftar peluru yang sedang terbang
    sf::Sprite gunSprite, muzzleFlash, pickupGun[2], spawnnedGun, crosshair; // Sprite senjata, cahaya tembakan, senjata yang bisa diambil, senjata yang telah di-spawn, dan tanda sasaran
    sf::Vector2f spritePosOffset = sf::Vector2f(0, 25);                      // Offset posisi sprite senjata
    sf::Vector2f scaleSize = sf::Vector2f(0.1, 0.1);                         // Skala ukuran sprite senjata
    bool renderFlash = false;                                                // Status render cahaya tembakan
    int remainingGunTime = 0;                                                // Sisa waktu gunakan senjata yang telah di-equip
    int spawndWeaponType = 0;                                                // Tipe senjata yang di-spawn
    bool gunEquipped = false;                                                // Status apakah senjata telah di-equip
    bool resourceLoaded = false;                                             // Status apakah sumber daya senjata telah diload

    // Konstruktor kelas Weapons
    Weapons(sf::Vector2f windowSize);

    void load(void);                  // Fungsi untuk memuat resource yang dibutuhkan oleh kelas Weapons
    void fire(sf::Vector2f mousePos); // Fungsi untuk mengeluarkan peluru

    void update(bool mousePressed, sf::Vector2f mousePos, sf::Vector2f playerPos, Entity player, float dt, Camera view, bool playerStatus); // Fungsi untuk memperbarui keadaan senjata (mengupdate posisi peluru dan sprite senjata, serta mengecek kolision dengan player)

    int spawnWeapon(sf::Vector2f playerPos, float dt, Camera view); // Fungsi untuk men-spawn senjata baru pada map
    void changeWeapon(int type, bool playSound);                    // Fungsi untuk mengganti senjata yang sedang dipakai
    bool ifOutsideView(Bullet b, Camera view);
    void resetStates(void);              // fungsi mereset status player
    void draw(sf::RenderWindow &window); // Fungsi untuk merender semua proses
};