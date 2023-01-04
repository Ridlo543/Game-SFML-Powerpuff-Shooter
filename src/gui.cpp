#include "gui.h"

Ui::Ui(sf::Vector2f windowSize)
// Ui::Ui(sf::Vector2f windowSize)
// Membuat instance dari class Ui
// parameter yang diterima adalah windowSize
{
    this->windowSize = windowSize;

    sf::Vector2f charSelectTextPosition;
    float charSelectTextCharSize;

    charSelectTextPosition = sf::Vector2f(200, 180);
    charSelectTextCharSize = 75;

    // mendefinisikan posisi dan ukuran dari text
    playButtonScale = sf::Vector2f(0.6, 0.6);
    exitButtonScale = sf::Vector2f(0.4, 0.4);

    startButtonScale = sf::Vector2f(0.8, 0.8);
    nextButtonScale = sf::Vector2f(0.8, 0.8);
    healthStuffScale = sf::Vector2f(0.6, 0.4);
    gotoMenuButtonScale = sf::Vector2f(0.7, 0.7);
    gunTimerBarScale = sf::Vector2f(0.6, 0.6);

    // loading textures and sprites
    // memuat texture dari file dan mengatur posisi dari sprite

    menuBackgroundTex.loadFromFile("assets/Ui/main_menu_1.png");
    menuBackground.setTexture(menuBackgroundTex);
    menuBackground.setPosition(0, 0);

    playButtonTex.loadFromFile("assets/Ui/play_button.png");
    playButton.setTexture(playButtonTex);
    playButton.setScale(playButtonScale);
    playButtonPos = sf::Vector2f(windowSize.x / 2 - playButton.getGlobalBounds().width / 2,
                                 windowSize.y - 480);
    playButton.setPosition(playButtonPos);

    exitButtonTex.loadFromFile("assets/Ui/exit_button.png");
    exitButton.setTexture(exitButtonTex);
    exitButton.setScale(exitButtonScale);
    exitButtonPos = sf::Vector2f(windowSize.x / 2 - exitButton.getGlobalBounds().width / 2,
                                 windowSize.y - 360);
    exitButton.setPosition(exitButtonPos);

    blankBackgroundTex.loadFromFile("assets/Ui/blank_background.png");
    blankBackground.setTexture(blankBackgroundTex);
    blankBackground.setPosition(0, -20);

    arrowTex.loadFromFile("assets/Ui/arrows.png");
    arrow.setTexture(arrowTex);
    arrow.setScale(0.5, 0.5);
    arrowPos = sf::Vector2f(windowSize.x / 2 - 220, windowSize.y / 2);
    arrow.setPosition(arrowPos);

    nextButtonTex.loadFromFile("assets/Ui/next_button.png");
    nextButton.setTexture(nextButtonTex);
    nextButton.setScale(nextButtonScale);
    nextButtonPos = sf::Vector2f(windowSize.x / 2 - nextButton.getGlobalBounds().width / 2,
                                 windowSize.y - nextButton.getGlobalBounds().height * 2);
    nextButton.setPosition(nextButtonPos);

    howToTex.loadFromFile("assets/Ui/how_TO.png");
    howToInfo.setTexture(howToTex);
    howToInfo.setPosition(0, -20);

    startButtonTex.loadFromFile("assets/Ui/start_button.png");
    startButton.setTexture(startButtonTex);
    startButton.setScale(startButtonScale);
    startButtonPos = sf::Vector2f(windowSize.x / 2 + 200,
                                  windowSize.y - 170);
    startButton.setPosition(startButtonPos);

    scoreUiTex.loadFromFile("assets/Ui/kills.png");
    scoreUi.setTexture(scoreUiTex);
    scoreUi.setPosition(windowSize.x / 2 - scoreUi.getGlobalBounds().width / 2, windowSize.y / 2 - scoreUi.getGlobalBounds().height / 2);

    gotoMenuButtonTex.loadFromFile("assets/Ui/goto_main_menu.png");
    gotoMenuButton.setTexture(gotoMenuButtonTex);
    gotoMenuButton.setScale(gotoMenuButtonScale);
    gotoMenuButton.setPosition(gotoMenuButtonPos);

    rifelTimeBarTex.loadFromFile("assets/Ui/rifel_outline.png");
    rifelTimeBar.setTexture(rifelTimeBarTex);
    rifelTimeBar.setScale(gunTimerBarScale);
    shotgunTimeBarTex.loadFromFile("assets/Ui/shotgun_outline.png");
    shotgunTimeBar.setTexture(shotgunTimeBarTex);
    shotgunTimeBar.setScale(gunTimerBarScale);
    timeBarInlineTex.loadFromFile("assets/Ui/gunTimer_inline.png");
    timeBarInline.setTexture(timeBarInlineTex);
    timeBarInline.setScale(gunTimerBarScale);
    timeBarTex.loadFromFile("assets/Ui/gunTimer_bar.png");
    timeBar.setTexture(timeBarTex);
    timeBar.setScale(gunTimerBarScale);

    newHighScoreTex.loadFromFile("assets/Ui/newHighScore.png");
    newHighScore.setTexture(newHighScoreTex);
    newHighScore.setScale(0.6, 0.6);

    ///////////
    // health bar stuffs
    healthOutTex.loadFromFile("assets/Ui/healthBarOutline.png");
    healthBarOutline.setTexture(healthOutTex);
    healthBarOutline.setScale(healthStuffScale);

    healthInTex.loadFromFile("assets/Ui/healthBarInline.png");
    healthBarInline.setTexture(healthInTex);
    healthBarInline.setScale(healthStuffScale);

    healthTex.loadFromFile("assets/Ui/healthBar.png");
    healthBar.setTexture(healthTex);
    healthBar.setScale(healthStuffScale);

    heartTex.loadFromFile("assets/Ui/heart.png");
    heart.setTexture(heartTex);
    heart.setScale(healthStuffScale.x - 0.08, healthStuffScale.y);

    // loading fonts
    gravePartyFont.loadFromFile("assets/Fonts/GraveParty.ttf");
    colorCandyFont.loadFromFile("assets/Fonts/ColorfulCandyDecorated-6Yrl6.otf");

    characterSelectText.setFont(colorCandyFont);
    characterSelectText.setCharacterSize(charSelectTextCharSize);
    characterSelectText.setFillColor(sf::Color(234, 42, 123, 255));
    characterSelectText.setString("SELECT  YOUR  PLAYER");
    characterSelectText.setPosition(charSelectTextPosition);
    characterSelectText.setRotation(-31.5 * (180 / 3.1415));

    countdownText.setFont(gravePartyFont);
    countdownText.setCharacterSize(200);
    countdownText.setFillColor(sf::Color(234, 42, 123, 255));
    countdownText.setString("GET  READY");
    countdownText.setPosition(windowSize.x / 2 - countdownText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);

    for (int i = 0; i < 6; i++)
    {
        scoreTexts[i].setFont(gravePartyFont);
        scoreTexts[i].setFillColor(sf::Color(234, 42, 123, 255));
        scoreTexts[i].setCharacterSize(50);
    }

    pauseText.setFont(colorCandyFont);
    pauseText.setCharacterSize(200);
    pauseText.setFillColor(sf::Color(72, 37, 55, 255));
    pauseText.setString("PAUSED");
    pauseText.setPosition(windowSize.x / 2 - pauseText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);

    // loading sounds
    buttonActiveBuffer.loadFromFile("assets/Sounds/Ui/menu_active.wav");
    buttonActive.setBuffer(buttonActiveBuffer);

    buttonSelectBuffer.loadFromFile("assets/Sounds/Ui/menu_select.wav");
    buttonSelect.setBuffer(buttonSelectBuffer);

    std::string bgMusicFilename = "assets/Sounds/Background_music/bg_music_";
    for (int i = 0; i < 5; i++)
    {
        bgMusicBuf[i].loadFromFile(bgMusicFilename + std::to_string(i + 1) + ".wav");
        bgMusic[i].setBuffer(bgMusicBuf[i]);
        if (i > 0)
            bgMusic[i].setVolume(bgMusicVolume - 20);
        else
            bgMusic[i].setVolume(bgMusicVolume);
    }
}

void Ui::setGameState(int state)
{
    gameState = state;
}

int Ui::getGameState(void)
{
    return gameState;
}

void Ui::updateMainMenu(sf::Vector2f mousePos, bool mousePressed)
{
    if (bgMusic[0].getStatus() != sf::Sound::Playing)
    {
        bgMusic[musicType].stop();
        bgMusic[0].play();
    }

    if (ifMouseIntersects(mousePos, playButton.getPosition(),
                          sf::Vector2f(playButton.getGlobalBounds().width, playButton.getGlobalBounds().height), 0))
    {

        playButton.setScale(playButtonScale.x + 0.2, playButtonScale.y + 0.2);
        playButton.setPosition(playButtonPos.x - 20, playButtonPos.y - 12);

        if (mousePressed)
        {
            buttonSelect.play();
            gameState = 1; // change to char select
        }
    }
    else
    {
        playButton.setPosition(playButtonPos);
        playButton.setScale(playButtonScale);
    }

    if (ifMouseIntersects(mousePos, exitButton.getPosition(),
                          sf::Vector2f(exitButton.getGlobalBounds().width, exitButton.getGlobalBounds().height), 0))
    {

        exitButton.setScale(exitButtonScale.x + 0.2, exitButtonScale.y + 0.2);
        exitButton.setPosition(exitButtonPos.x - 20, exitButtonPos.y - 12);

        if (mousePressed)
        {
            buttonSelect.play();
            gameState = 7; // change to char select
        }
    }
    else
    {
        exitButton.setPosition(exitButtonPos);
        exitButton.setScale(exitButtonScale);
    }
}

void Ui::updateCharacterSelect(sf::Vector2f mousePos, bool &mousePressed)
{
    if (ifMouseIntersects(mousePos, nextButton.getPosition(),
                          sf::Vector2f(nextButton.getGlobalBounds().width, nextButton.getGlobalBounds().height), 1))
    {

        nextButton.setScale(nextButtonScale.x + 0.2, nextButtonScale.x + 0.2);
        nextButton.setPosition(nextButtonPos.x - 20, nextButtonPos.y - 12);
        if (soundException1)
        {
            soundException1 = false;
            buttonActive.play();
        }

        if (mousePressed)
        {
            buttonSelect.play();
            gameState = 2; // change to howto state
        }
    }
    else
    {
        nextButton.setPosition(nextButtonPos);
        nextButton.setScale(nextButtonScale);
        soundException1 = true;
    }

    if (ifMouseIntersects(mousePos, arrow.getPosition(),
                          sf::Vector2f(arrow.getGlobalBounds().width, arrow.getGlobalBounds().height), 2))
    {

        arrow.setScale(0.6, 0.6);
        arrow.setPosition(arrowPos.x - 10, arrowPos.y - 6);
        if (soundException2)
        {
            soundException2 = false;
            buttonActive.play();
        }

        if (mousePressed)
        {
            mousePressed = false;
            buttonSelect.play();
            playerType += 1;
            if (playerType > 2)
                playerType = 0;
        }
    }
    else
    {
        arrow.setPosition(arrowPos);
        arrow.setScale(0.5, 0.5);
        soundException2 = true;
    }
}

void Ui::updateHowToState(sf::Vector2f mousePos, bool mousePressed)
{
    if (ifMouseIntersects(mousePos, startButton.getPosition(),
                          sf::Vector2f(startButton.getGlobalBounds().width, startButton.getGlobalBounds().height), 3))
    {

        startButton.setScale(startButtonScale.x + 0.1, startButtonScale.y + 0.1);
        startButton.setPosition(startButtonPos.x - 16, startButtonPos.y - 8);

        if (mousePressed)
        {
            buttonSelect.play();
            gameState = 3;
        }
    }
    else
    {
        startButton.setScale(startButtonScale);
        startButton.setPosition(startButtonPos);
    }
}

void Ui::updateCountDown(float dt)
{
    if (bgMusic[0].getStatus() == sf::Sound::Playing)
    {
        if (bgMusic[0].getVolume() > 0)
            bgMusic[0].setVolume(bgMusic[0].getVolume() - 0.18);
        if (static_cast<int>(bgMusic[0].getVolume()) <= 0)
        {
            bgMusic[0].stop();
            bgMusic[0].setVolume(bgMusicVolume);
        }
    }
    else if (!bgMusicPlaying)
    {
        musicType = std::rand() % 4 + 1;
        bgMusic[musicType].play();
        bgMusicPlaying = true;
    }

    countDownTimer += dt;

    if (countDownTimer > countDownInterval)
    {
        countDownTimer = 0;

        if (countNum == -1)
        {
            gameState = 4; // change to play state
            return;
        }
        buttonActive.play();
        countdownText.setString(std::to_string(countNum));
        if (countNum == 0)
        {
            buttonSelect.play();
            countdownText.setString("GO");
        }
        countdownText.setPosition(windowSize.x / 2 - countdownText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);
        countNum -= 1;
    }
}

void Ui::updatePlayState(sf::Vector2f viewSize, sf::Vector2f viewCenter, int playerHealth, float remainingGunTime)
{
    if (bgMusic[musicType].getStatus() == sf::Sound::Status::Stopped)
    {
        musicType = std::rand() % 4 + 1;
        bgMusic[musicType].play();
        bgMusicPlaying = true;
    }

    if (playerHealth >= 0)
    {
        float healthBarFactor = healthStuffScale.x / 5;
        float reduceScale = healthBarFactor * ((100 - playerHealth) / 20);
        healthBar.setScale(healthStuffScale.x - reduceScale, healthStuffScale.y);
    }
    if (remainingGunTime >= 0)
    {
        float timerbarFactor = gunTimerBarScale.x / 10;
        float reduceScale = timerbarFactor * ((10 - remainingGunTime));
        timeBar.setScale(gunTimerBarScale.x - reduceScale, gunTimerBarScale.y);
    }

    float x = viewCenter.x - viewSize.x / 2 + healthBarOutline.getGlobalBounds().width / 4;
    float y = viewCenter.y - viewSize.y / 2 + healthBarOutline.getGlobalBounds().height / 2;
    healthBarOutline.setPosition(x, y);
    healthBarInline.setPosition(x + 12, y + 8);
    healthBar.setPosition(x + 12, y + 8);
    if (this->windowSize.x <= 1366 && this->windowSize.y <= 768)
    {
        heart.setPosition(x - 30, y - 6);
        timeBarInline.setPosition(x + 600 + 100, y + 10);
        timeBar.setPosition(x + 600 + 100, y + 10);
    }
    else
    {
        heart.setPosition(x - 38, y - 10);
        timeBarInline.setPosition(x + 600 + 120, y + 10);
        timeBar.setPosition(x + 600 + 120, y + 10);
    }

    rifelTimeBar.setPosition(x + 600, y);
    shotgunTimeBar.setPosition(x + 600, y);

    // pause text position
    pauseText.setPosition(sf::Vector2f(viewCenter.x - pauseText.getGlobalBounds().width / 2,
                                       viewCenter.y - pauseText.getGlobalBounds().height));
}

void Ui::loadScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, std::vector<int> scores)
{
    float x = viewCenter.x - scoreUi.getGlobalBounds().width / 2;
    float y = viewCenter.y - scoreUi.getGlobalBounds().height / 2;
    scoreUi.setPosition(x, y);

    int totalScore = 0;
    for (int i = 0; i < 4; i++)
    {
        totalScore += scores[i];
        std::string tempScore = std::to_string(scores[i]);
        scoreTexts[i].setString(tempScore);
        scoreTexts[i].setPosition((x + 100 + i * 130), y + 250);
    }
    std::string tempScore = std::to_string(totalScore);
    scoreTexts[4].setString(tempScore);
    scoreTexts[4].setPosition(x + scoreUi.getGlobalBounds().width / 2, y + 315);

    std::ifstream highScoreFile("assets/User_flies/score.txt");
    std::string scoreInFile;
    highScoreFile >> scoreInFile;
    highScoreFile.close();
    int highestScore = std::atoi(scoreInFile.c_str());
    if (totalScore > highestScore)
    {
        newHighScoreAchieved = true;
        newHighScore.setPosition(x + 10, y + 10);
        highestScore = totalScore;
        std::ofstream highScoreFile("assets/User_flies/score.txt");
        highScoreFile << std::to_string(highestScore);
    }

    scoreTexts[5].setString(std::to_string(highestScore));
    scoreTexts[5].setPosition(x + scoreUi.getGlobalBounds().width / 2, y + 360);

    gotoMenuButtonPos = sf::Vector2f(x + 250, y + 420);
    gotoMenuButton.setPosition(gotoMenuButtonPos);

    scoresLoaded = true;
}

bool Ui::updateScoreState(sf::Vector2f viewSize, sf::Vector2f viewCenter, sf::Vector2f mousePos, bool mousePressed)
{
    if (bgMusic[musicType].getStatus() == sf::Sound::Playing)
    {
        if (bgMusic[musicType].getVolume() > 0)
            bgMusic[musicType].setVolume(bgMusic[musicType].getVolume() - 0.2);
        if (static_cast<int>(bgMusic[musicType].getVolume()) <= 0)
        {
            bgMusic[musicType].stop();
            bgMusicPlaying = false;
            bgMusic[musicType].setVolume(bgMusicVolume);
        }
    }

    if (ifMouseIntersects(mousePos, gotoMenuButton.getPosition(),
                          sf::Vector2f(gotoMenuButton.getGlobalBounds().width, gotoMenuButton.getGlobalBounds().height), 4))
    {

        gotoMenuButton.setScale(gotoMenuButtonScale.x + 0.2, gotoMenuButtonScale.y + 0.2);
        gotoMenuButton.setPosition(gotoMenuButtonPos.x - 16, gotoMenuButtonPos.y - 8);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            buttonSelect.play();
            return true;
        }
    }
    else
    {
        gotoMenuButton.setScale(gotoMenuButtonScale);
        gotoMenuButton.setPosition(gotoMenuButtonPos);
        return false;
    }
}

bool Ui::ifMouseIntersects(sf::Vector2f mousePos, sf::Vector2f buttonPos, sf::Vector2f buttonSize, int number)
{
    if (mousePos.x > buttonPos.x && mousePos.x < buttonPos.x + buttonSize.x &&
        mousePos.y > buttonPos.y && mousePos.y < buttonPos.y + buttonSize.y)
    {
        if (playButtonActive && (number != 1 && number != 2))
        {
            buttonActive.play();
        }
        playButtonActive = false;
        return true;
    }
    else
    {
        playButtonActive = true;
        return false;
    }
}

void Ui::resetStates(void)
{
    playerType = 0;
    scoresLoaded = false;
    countNum = 3;
    bgMusicPlaying = false;
    newHighScoreAchieved = false;
    countdownText.setString("GET  READY");
    countdownText.setPosition(windowSize.x / 2 - countdownText.getGlobalBounds().width / 2, windowSize.y / 2 - 220);
}

void Ui::renderMainMenu(sf::RenderWindow &window)
{
    window.draw(menuBackground);
    window.draw(playButton);
    window.draw(exitButton);
}

void Ui::renderCharacterSelect(sf::RenderWindow &window)
{
    window.draw(blankBackground);
    window.draw(characterSelectText);
    window.draw(nextButton);
    window.draw(arrow);
}

void Ui::renderHowToState(sf::RenderWindow &window)
{
    window.draw(howToInfo);
    window.draw(startButton);
}

void Ui::renderCountDown(sf::RenderWindow &window)
{
    window.draw(countdownText);
}

void Ui::renderPlayState(sf::RenderWindow &window, bool showTimeBar, int timebarType)
{
    window.draw(healthBarInline);
    window.draw(healthBar);
    window.draw(healthBarOutline);
    window.draw(heart);

    if (showTimeBar)
    {
        window.draw(timeBarInline);
        window.draw(timeBar);
        if (timebarType == 0)
            window.draw(rifelTimeBar);
        else
            window.draw(shotgunTimeBar);
    }
}

void Ui::renderScoreState(sf::RenderWindow &window)
{
    window.draw(scoreUi);
    if (newHighScoreAchieved)
        window.draw(newHighScore);
    for (int i = 0; i < 6; i++)
        window.draw(scoreTexts[i]);
    window.draw(gotoMenuButton);
}

void Ui::renderPauseState(sf::RenderWindow &window)
{
    window.draw(pauseText);
}
