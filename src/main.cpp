// File main.cpp
#include "map.h"
#include <ctime>
#include <cstdlib>

int main()
{
    // Inisialisasi nilai acak dengan time saat ini
    srand(static_cast<unsigned>(std::time(0)));

    // Menentukan ukuran window
    sf::Vector2f windowSize = sf::Vector2f(1280, 720);
    // Membuat window dengan ukuran dan judul yang telah ditentukan
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PowerPuff_Shooter", sf::Style::Default);

    // Mengatur batas fps pada window
    window.setFramerateLimit(120);

    // Inisialisasi variabel-variabel yang akan digunakan pada loop
    sf::Time tm;
    sf::Clock clk;
    float dt = 0.f;
    sf::Vector2f mousePos;
    sf::Vector2i tempMousePos;
    bool keyPressed = false;
    bool mousePressed = false;

    // Inisialisasi objek Map, Bullet, Player, EnemyManager, Weapons, Camera, dan Ui
    Map *map = new Map(windowSize);
    Bullet *b = new Bullet();
    Player *player = new Player(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), windowSize);
    EnemyManager *enemyManager = new EnemyManager(windowSize);
    Weapons *weapon = new Weapons(windowSize);
    Camera *playerCam = new Camera(windowSize);
    Ui *gameUi = new Ui(windowSize);

    // Mengatur game state menjadi 0 (menu utama)
    gameUi->setGameState(0);

    // Memanggil fungsi initMap pada objek map dengan parameter objek playerCam
    map->initMap(*playerCam);

    // Loop utama program
    while (window.isOpen())
    {
        // Menyimpan waktu yang telah berlalu sejak frame terakhir
        tm = clk.restart();
        // Menyimpan waktu yang telah berlalu sejak frame terakhir
        dt = tm.asSeconds();

        // Memproses event yang terjadi
        sf::Event e;
        while (window.pollEvent(e))
        {
            // Cek jenis event yang terjadi
            switch (e.type)
            {
            // Jika event terjadi adalah penutupan window
            case sf::Event::Closed:
                // Menutup window
                window.close();
                break;

            // Jika event terjadi adalah penekanan mouse button
            case sf::Event::MouseButtonPressed:
                mousePressed = true; // Menandai bahwa mouse button telah ditekan
                if (!player->isDead) // Jika player belum mati, maka player akan menembak
                    weapon->fire(mousePos);
                break;
            // Jika event terjadi adalah pengeluaran mouse button
            case sf::Event::MouseButtonReleased:
                mousePressed = false; // Menandai bahwa mouse button telah dilepas
                break;
            // Jika event terjadi adalah penekanan tombol keyboard
            case sf::Event::KeyPressed:

                keyPressed = true; // Menandai bahwa tombol keyboard telah ditekan

                // Cek apakah game state saat ini adalah game over atau pause, dan apakah tombol escape telah ditekan
                if ((gameUi->getGameState() == 4 || gameUi->getGameState() == 6) &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    // Jika game state saat ini adalah game over, maka ubah game state menjadi pause
                    // Jika game state saat ini adalah pause, maka ubah game state menjadi game over
                    gameUi->setGameState((gameUi->getGameState() == 4) ? 6 : 4);
                }

                // Cek apakah tombol num1, num2, atau num3 telah ditekan
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                    weapon->changeWeapon(1, true); // Ganti senjata menjadi senjata pertama
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                    weapon->changeWeapon(2, true); // Ganti senjata menjadi senjata kedua
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                    weapon->changeWeapon(3, true); // Ganti senjata menjadi senjata ketiga
                break;
                // Jika event terjadi adalah pengeluaran tombol keyboard
            case sf::Event::KeyReleased:
                // Menandai bahwa tombol keyboard telah dilepas
                keyPressed = false;
                break;

            // Event lainnya diabaikan
            default:
                break;
            }
        }

        //////////////////////////////////////////////////////////////////////////
        // update actions
        // Update mouse position and hide/show cursor based on game state
        tempMousePos = sf::Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(tempMousePos);
        if (gameUi->getGameState() == 4)
            window.setMouseCursorVisible(false);
        else
            window.setMouseCursorVisible(true);

        // Update game state
        switch (gameUi->getGameState())
        {
        case 0: // if in main menu
            gameUi->updateMainMenu(mousePos, mousePressed);
            break;
        case 1: // if in character select state
            if (!player->resourceLoaded)
                player->load();

            gameUi->updateCharacterSelect(mousePos, mousePressed);
            if (gameUi->playerType != player->getCharacterType())
                player->setCharacterType(gameUi->playerType);
            player->animateIdle(dt, sf::Vector2f(1, 1));
            break;
        case 2: // how to
            gameUi->updateHowToState(mousePos, mousePressed);
            break;
        case 3: // if in countDown state
            if (!weapon->resourceLoaded && !enemyManager->resourceLoaded)
            {
                weapon->load();
                enemyManager->load();
            }
            gameUi->updateCountDown(dt);
            break;
        case 4: // if play state
            player->update(dt, keyPressed, mousePos, enemyManager->enemyBullets, *weapon);
            weapon->update(mousePressed, mousePos, player->getPosition(), *player, dt, *playerCam, player->isDead);
            enemyManager->update(dt, *weapon, player->getPosition(), *playerCam);
            playerCam->update(player->getPosition(), window, dt);
            map->update(*playerCam, keyPressed, player->getPosition());
            gameUi->updatePlayState(playerCam->playerView.getSize(), playerCam->playerView.getCenter(), player->getHealth(), weapon->remainingGunTime);

            if (player->isDead && player->deathSceneEnd)
                gameUi->setGameState(5);
            break;
        case 5: // score state
            if (!gameUi->scoresLoaded)
                gameUi->loadScoreState(playerCam->playerView.getSize(), playerCam->playerView.getCenter(), enemyManager->killScores);
            if (gameUi->updateScoreState(playerCam->playerView.getSize(), playerCam->playerView.getCenter(), mousePos, mousePressed))
            {
                player->resetStates();
                enemyManager->resetStates();
                weapon->resetStates();
                sf::Vector2i temp = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);
                playerCam->playerView.setCenter(temp.x, temp.y);
                window.setView(playerCam->playerView);
                gameUi->resetStates();
                gameUi->setGameState(0);
            }
            break;
        case 6:
            break;
        case 7:
            window.close();
        default:
            break;
        }

        //////////////////////////////////////////////////////////////////////////
        // render functions
        // render game objects
        // Bersihkan window dengan warna latar belakang dari map
        window.clear(map->backgroundColor);

        // Berdasarkan state yang sedang aktif, rendam UI yang sesuai
        switch (gameUi->getGameState())
        {
        case 0: // main menu state
            gameUi->renderMainMenu(window);
            break;
        case 1: // character select state
            // Jika resource player belum diload, tampilkan menu utama
            if (!player->resourceLoaded)
            {
                gameUi->renderMainMenu(window);
                break;
            }
            gameUi->renderCharacterSelect(window);
            player->draw(window, *weapon, gameUi->getGameState());
            break;
        case 2: // how to
            gameUi->renderHowToState(window);
            break;
        case 3: // countDown
            gameUi->renderCountDown(window);
            break;
        case 4: // if play state
            map->draw(window);
            window.draw(player->shadow);
            // Jika player belum mati, tampilkan senjata yang dipakai
            if (!player->isDead)
                weapon->draw(window);
            player->draw(window, *weapon, gameUi->getGameState());
            enemyManager->drawEnemies(window);
            gameUi->renderPlayState(window, weapon->gunEquipped, weapon->spawndWeaponType);
            window.draw(weapon->crosshair);
            break;
        case 5: // score
            gameUi->renderScoreState(window);
            break;
        case 6: // paused
            gameUi->renderPauseState(window);
            break;
        case 7:
            window.close();
        default:
            break;
        }

        // Tampilkan window
        window.display();
    }
}
