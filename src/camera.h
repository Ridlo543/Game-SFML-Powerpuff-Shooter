#pragma once
#include "gui.h"

class Camera
{
private:
    int maxPlayerOffset = 300;                // menentukan berapa jauh offset maksimal dalam game
    float moveSpeed = 400.f;                  // menentukan kecepatan kamera
    float shakeTime = 0.2f, shakeTimer = 0.f; // menentukan durasi shake

public:
    sf::View playerView;       // membuat view pada kamera
    bool triggerShake = false; // menentukan apakah camera dalam mode shake

    Camera(sf::Vector2f windowSize);                                         // konstruktor
    void update(sf::Vector2f playerPos, sf::RenderWindow &window, float dt); // fungsi untuk memperbarui kamera
    void cameraShake(float dt);                                              // membuat kamera bergetar
};