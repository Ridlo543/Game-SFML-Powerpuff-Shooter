#include "camera.h"

Camera::Camera(sf::Vector2f windowSize)
{
    playerView.setSize(windowSize);
    playerView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

void Camera::update(sf::Vector2f playerPos, sf::RenderWindow &window, float dt)
{
    // Mengikuti posisi player
    playerView.setCenter(playerPos);

    // Mengeset view camera ke window
    window.setView(playerView);

    // Apabila triggerShake bernilai true, jalankan fungsi cameraShake
    if (triggerShake)
    {
        cameraShake(dt);
    }
}

void Camera::cameraShake(float dt)
{
    // Menambah timer shake
    shakeTimer += dt;

    // Apabila timer shake melebihi nilai shakeTime, reset timer shake dan matikan trigger shake
    if (shakeTimer >= shakeTime)
    {
        shakeTimer = 0;
        triggerShake = false;
        return;
    }

    // Tentukan nilai offset secara acak
    float offset = 5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10 - 5)));

    // Tentukan arah offset secara acak
    float direction = rand() % 2;

    // Tentukan posisi baru x dan y dengan offset
    float newCenterX = playerView.getCenter().x + ((direction == 0) ? offset : -offset);
    float newCenterY = playerView.getCenter().y + ((direction == 0) ? offset : -offset);

    // Set posisi baru
    playerView.setCenter(newCenterX, newCenterY);
}