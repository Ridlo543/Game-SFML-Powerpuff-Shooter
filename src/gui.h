#pragma once
#include "bullet.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

// Ui merupakan kelas yang menangani semua tampilan di game.
// Game dibagi menjadi beberapa bagian seperti main menu, character select, how to play, countdown, play, score, dan pause.
// Ui memiliki beberapa variabel yang digunakan untuk menampilkan tampilan-tampilan tersebut.
class Ui
{
private:
    // Ukuran window game.
    sf::Vector2f windowSize;
    // State game.
    int gameState = 0;
    // 0 -> main menu
    // 1 -> character select
    // 2 -> how to
    // 3 -> count down
    // 4 -> play
    // 5 -> score
    // 6 -> pause

    // Textures untuk menampilkan sprite-sprite yang dibutuhkan.
    sf::Texture menuBackgroundTex, blankBackgroundTex, playButtonTex, arrowTex, startButtonTex, exitButtonTex;
    sf::Texture healthOutTex, healthInTex, healthTex, heartTex;
    sf::Texture howToTex, nextButtonTex, scoreUiTex, gotoMenuButtonTex;
    sf::Texture rifelTimeBarTex, shotgunTimeBarTex, timeBarInlineTex, timeBarTex;
    sf::Texture newHighScoreTex;

    // Sprites untuk menampilkan texture di layar.
    sf::Sprite menuBackground, blankBackground, playButton, arrow, startButton, exitButton;
    sf::Sprite healthBarOutline, healthBarInline, healthBar, heart;
    sf::Sprite howToInfo, nextButton, scoreUi, gotoMenuButton;
    sf::Sprite rifelTimeBar, shotgunTimeBar, timeBarInline, timeBar;
    sf::Sprite newHighScore;

    // Fonts untuk menampilkan text di layar.
    sf::Font gravePartyFont, colorCandyFont;
    // Texts untuk menampilkan string di layar.
    sf::Text characterSelectText, countdownText, scoreTexts[6], pauseText;

    // Sounds untuk menambahkan audio di game.
    sf::SoundBuffer buttonActiveBuffer, buttonSelectBuffer;
    sf::SoundBuffer bgMusicBuf[5];
    sf::Sound buttonActive, buttonSelect;
    sf::Sound bgMusic[5];

    // Posisi button-button di layar.
    sf::Vector2f playButtonPos, exitButtonPos, startButtonPos, arrowPos, nextButtonPos, gotoMenuButtonPos;
    // Skala sprite-sprite.
    sf::Vector2f playButtonScale, exitButtonScale, startButtonScale, healthStuffScale, nextButtonScale, gotoMenuButtonScale;
    sf::Vector2f gunTimerBarScale;
    // Timer untuk countdown.
    float countDownInterval = 1.2f, countDownTimer = 0.f;
    int countNum = 3;

    // Variabel untuk mengontrol button-button.
    bool playButtonActive = true;
    bool soundException1 = true, soundException2 = true;
    bool bgMusicPlaying = false;
    bool newHighScoreAchieved = false;
    int musicType = 1;
    int bgMusicVolume = 60;

public:
    int playerType = 0;
    bool scoresLoaded = false;

    // Konstruktor dari kelas Ui yang menginisialisasi windowSize dan posisi-posisi yang dibutuhkan oleh sprite-sprite.
    Ui(sf::Vector2f windowSize);
    // setGameState digunakan untuk mengatur game state saat ini.
    void setGameState(int state);
    int getGameState(void);

    // method method
    void updateMainMenu(sf::Vector2f mousePos, bool mousePressed);         // updateMainMenu digunakan untuk mengupdate posisi button-button di layar jika kursor mouse berada di dekatnya.
    void updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed); // updateCharacterSelect digunakan untuk mengupdate playerType ketika pemain memilih karakter yang akan dimainkan.
    void updateHowToState(sf::Vector2f mousePos, bool mousePressed);       // updateHowToState digunakan untuk mengupdate posisi button-button di layar jika kursor mouse berada di dekatnya.
    void updateCountDown(float dt);                                        // updateCountDown digunakan untuk mengatur countdown yang ditampilkan pada layar sebelum permainan dimulai.

    void updatePlayState(sf::Vector2f viewSize, sf::Vector2f viewCenter, int playerHealth, float remainingGunTime);  // updatePlayState digunakan untuk mengupdate tampilan pada saat permainan sedang berlangsung.
    void loadScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, std::vector<int> scores);                    // loadScoreState digunakan untuk memuat skor yang tersimpan pada file eksternal ke dalam scoreTexts.
    bool updateScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, sf::Vector2f mousePos, bool mousePressed); // updateScoreState digunakan untuk mengupdate posisi button-button di layar jika kursor mouse berada di dekatnya.
    bool ifMouseIntersects(sf::Vector2f mousePos, sf::Vector2f buttonPos, sf::Vector2f buttonSize, int number);      // ifMouseIntersects digunakan untuk memeriksa apakah mouse berada di dalam area yang ditentukan.

    void resetStates(void);                                                            // resetStates digunakan untuk mereset semua variabel yang digunakan dalam game.
    void renderMainMenu(sf::RenderWindow &window);                                     // renderMainMenu digunakan untuk menampilkan tampilan main menu di layar.
    void renderCharacterSelect(sf::RenderWindow &window);                              // renderCharacterSelect digunakan untuk menampilkan tampilan character select di layar.
    void renderHowToState(sf::RenderWindow &window);                                   // renderHowToState digunakan untuk menampilkan tampilan how to play di layar.
    void renderCountDown(sf::RenderWindow &window);                                    // renderCountDown digunakan untuk menampilkan contdown di layar.
    void renderPlayState(sf::RenderWindow &window, bool showTimeBar, int timebarType); // renderPlayState digunakan untuk menampilkan tampilan permainan di layar.
    void renderScoreState(sf::RenderWindow &window);                                   // renderScoreState digunakan untuk menampilkan tampilan score di layar.
    void renderPauseState(sf::RenderWindow &window);                                   // renderPauseState digunakan untuk menampilkan tampilan pause di layar.
};