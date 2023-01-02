#include "enemyManager.h"

EnemyManager::EnemyManager(sf::Vector2f windowSize)
{
    this->windowSize = windowSize;
}

// fungsi untuk memuat asset - asset enemy
void EnemyManager::load(void)
{
    // loading textures
    std::string walkTexFileName = "assets/characters/Enemy_";
    for (int i = 0; i < 4; i++)
    {
        std::string currFileName = walkTexFileName + std::to_string(i + 1) + "/walk.png";
        walkTextures[i].loadFromFile(currFileName);

        enemyWalkSprites[i].setTexture(walkTextures[i]);
        enemyWalkSprites[i].setTextureRect(sf::IntRect(sf::IntRect(0 * subTexRectSize, 0, subTexRectSize, subTexRectSize)));
        enemyWalkSprites[i].setOrigin(subTexRectSize / 2, subTexRectSize / 2);
        enemyWalkSprites[i].setScale(2.0f, 2.0f);

        killScores.push_back(0); // pushing 4 times
    }
    enemySprite = enemyWalkSprites[0];

    // loading generic death texture
    genericDeathTex.loadFromFile("assets/Generic_death_animation/generic_death.png");
    genericDeathSprite.setTexture(genericDeathTex);
    genericDeathSprite.setTextureRect(sf::IntRect(0, 0, 2048, 2048));
    genericDeathSprite.setOrigin(genericDeathSprite.getGlobalBounds().width / 2, genericDeathSprite.getGlobalBounds().height / 2);
    genericDeathSprite.setScale(0.09, 0.09);

    shadowTex.loadFromFile("assets/Extras/shadow.png");
    shadow.setTexture(shadowTex);
    shadow.setScale(0.0175, 0.0175);

    // loading sounds
    hurtBuf.loadFromFile("assets/Sounds/Player_sounds/hit.wav");
    hurt.setBuffer(hurtBuf);

    resourceLoaded = true;
}

void EnemyManager::spawnEnemies(sf::Vector2f playerPos, Camera view)
{
    int direction = std::rand() % 4;
    int x = 0, y = 0;
    sf::Vector2f viewSize = view.playerView.getSize();

    // menentukan arah untuk menentukan posisi spawn enemy
    switch (direction)
    {
    case 0: // up
        x = std::rand() % static_cast<int>(viewSize.x);
        y = playerPos.y - viewSize.y / 2;
        break;
    case 1: // down
        x = std::rand() % static_cast<int>(viewSize.x);
        y = playerPos.y + viewSize.y / 2;
        break;
    case 2: // left
        x = playerPos.x - viewSize.x / 2;
        y = std::rand() % static_cast<int>(viewSize.y);
        break;
    case 3: // right
        x = playerPos.x + viewSize.x / 2;
        y = std::rand() % static_cast<int>(viewSize.y);
        break;
    default:
        return;
        break;
    }

    // menentukan tipe enemy
    int enemyType = std::rand() % 4;
    enemySprite = enemyWalkSprites[enemyType];

    // membuat objek enemy baru
    Enemy *e = new Enemy(sf::Vector2f(x, y), colRectSize, enemySprite, this->shadow, enemyType);
    enemies.push_back(*e);
    numberOfEnemy++;

    // mengatur max enemy yang boleh di spawn
    maxEnemySpawnd = (numberOfEnemy == maxNumberOfEnemy) ? true : false;
}

// Memperbarui EnemyManager
void EnemyManager::update(float dt, Weapons &w, sf::Vector2f playerPos, Camera &view)
{
    // spawn enemies
    spawnnigTimer += dt;
    if (spawnnigTimer >= spawnTime && maxEnemySpawnd == false)
    {
        spawnnigTimer = 0;
        spawnEnemies(playerPos, view);
        spawnTime = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0 - 0.5)));
    }

    // update enemies
    auto i = enemies.begin();
    while (i != enemies.end())
    {
        i->update(dt, playerPos, w, view);

        moveEnemy(dt, playerPos, *i);
        animateWalk(dt, *i);
        i->sprite.setPosition(i->getPosition() - spritePosOffset);
        i->shadowSprite.setPosition(i->getPosition().x - 30, i->getPosition().y - 5);

        shoot(playerPos, *i, dt);

        if (i->getHealth() <= 0)
        { // enemy is down trigger death animation
            hurt.play();
            genericDeathSprite.setColor(i->deathShadowColor);
            genericDeathSprite.setPosition(i->sprite.getPosition());
            deathShadows.push_back(std::make_pair(genericDeathSprite, 0.f));

            // updating score
            killScores[i->enemyType]++;

            i = enemies.erase(i);
        }
        else
            i++;
    }
    numberOfEnemy = enemies.size();
    maxEnemySpawnd = (numberOfEnemy == maxNumberOfEnemy) ? true : false;

    // update enemy death shadows
    auto j = deathShadows.begin();
    while (j != deathShadows.end())
    {
        j->second += dt;
        // Update sprite ketika mati
        if (j->second > 0.1f)
            j->first.setTextureRect(sf::IntRect(2048, 0, 2048, 2048));
        if (j->second > 0.15f)
            j->first.setTextureRect(sf::IntRect((2048 * 2), 0, 2048, 2048));
        if (j->second > 1.4f)
            j->first.setColor(sf::Color(j->first.getColor().r, j->first.getColor().g, j->first.getColor().b, 255 / 2));

        if (j->second > 2.f)
            j = deathShadows.erase(j);
        else
            j++;
    }

    // update enemy bullets
    auto enBullet = enemyBullets.begin();
    while (enBullet != enemyBullets.end())
    {
        enBullet->update(dt);
        // Cek apakah pelurun musuh di luar pandangan
        if (ifOutsizeView(*enBullet, view)) // check if enemy bullet is outsize of view
            enBullet = enemyBullets.erase(enBullet);
        else
            enBullet++;
    }
}

// Fungsi ini bertujuan untuk memindahkan enemy
void EnemyManager::moveEnemy(float dt, sf::Vector2f playerPos, Enemy &e)
{
    float dx = playerPos.x - e.getPosition().x;                 // dx digunakan untuk menentukan perbedaan posisi antara player dan enemy
    float dy = playerPos.y - e.getPosition().y;                 // dy digunakan untuk menentukan perbedaan posisi antara player dan enemy
    float value = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2)); // value digunakan untuk menghitung jarak antara player dan enemy
    if (value <= minDistBtPlayerEnemy)                          // jika jarak antara player dan enemy kurang dari min dist
    {
        e.inNearestPoint = true; // inNearestPoint menjadi true
        return;
    }
    e.inNearestPoint = false;                                        // inNearestPoint menjadi false
    sf::Vector2f normDir = sf::Vector2f((dx / value), (dy / value)); // norm dir digunakan untuk menentukan arah normalisasi
    e.move(normDir * moveSpeed * dt);                                // enemy akan bergerak dengan arah normalisasi dengan kecepatan moveSpeed
}

// Fungsi ini bertujuan untuk mengatur animasi enemy
void EnemyManager::animateWalk(float dt, Enemy &e)
{
    if (e.inNearestPoint && e.enemyType != 2) // jika inNearestPoint true dan enemyType bukan 2
    {
        e.currWalkTex = 0;                                                                                       // currWalkTex menjadi 0
        e.sprite.setTextureRect(sf::IntRect(e.currWalkTex * subTexRectSize, 0, subTexRectSize, subTexRectSize)); // mengatur texture
        e.sprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);                                              // mengatur origin
        if (e.flipped)                                                                                           // jika enemy terbalik
            e.sprite.setScale(-scaleSize.x, scaleSize.y);                                                        // mengatur skala x menjadi negatif
        else
            e.sprite.setScale(scaleSize); // mengatur skala x menjadi positif
        return;
    }

    e.walkAnimTimer += dt;                 // walkAnimTimer digunakan untuk mengontrol timer animasi
    if (e.walkAnimTimer >= e.walkAnimTime) // jika walk anim timer lebih dari waktu animasi
    {
        e.walkAnimTimer = 0; // walk anim timer menjadi 0

        e.currWalkTex++;                                                                                              // currWalkTex bertambah 1
        if (e.currWalkTex == e.maxWalkTex - 1)                                                                        // jika currWalkTex sama dengan maxWalkTex - 1
            e.currWalkTex = 0;                                                                                        // currWalkTex menjadi 0
        e.sprite.setTextureRect(sf::IntRect(e.currWalkTex * subTexRectSize, 0, subTexRectSize, subTexRectSize + 50)); // mengatur texture
        e.sprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);                                                   // mengatur origin
        if (e.flipped)                                                                                                // jika enemy terbalik
            e.sprite.setScale(-scaleSize.x, scaleSize.y);                                                             // mengatur skala x menjadi negatif
        else
            e.sprite.setScale(scaleSize); // mengatur skala x menjadi positif
    }
}

// Fungsi ini bertujuan untuk menentukan jika bullet berada di luar view
bool EnemyManager::ifOutsizeView(Bullet b, Camera view)
{
    int viewLeft = view.playerView.getCenter().x - view.playerView.getSize().x / 2;  // viewLeft digunakan untuk menentukan posisi view kiri
    int viewRight = view.playerView.getCenter().x + view.playerView.getSize().x / 2; // viewRight digunakan untuk menentukan posisi view kanan
    int viewUp = view.playerView.getCenter().y - view.playerView.getSize().y / 2;    // viewUp digunakan untuk menentukan posisi view atas
    int viewDown = view.playerView.getCenter().y + view.playerView.getSize().y / 2;  // viewDown digunakan untuk menentukan posisi view bawah

    if (b.getPosition().x < viewLeft || b.getPosition().x > viewRight || // jika posisi bullet kiri dari viewLeft atau kanan dari viewRight atau
        b.getPosition().y < viewUp || b.getPosition().y > viewDown)      // atas dari viewUp atau bawah dari viewDown
        return true;                                                     // maka return true
    else
        return false; // selain itu return false
}

// Fungsi ini bertujuan untuk mereset semua state
void EnemyManager::resetStates(void)
{
    spawnnigTimer = 0.f;    // spawning timer menjadi 0
    reloadingTimer = 0.f;   // reloading timer menjadi 0
    spawnTime = 1.f;        // spawnTime menjadi 1
    maxEnemySpawnd = false; // maxEnemySpawnd menjadi false

    deathShadows.clear(); // hapus semua elemen deathShadows
    killScores.clear();   // hapus semua elemen killScores
    for (int i = 0; i < 4; i++)
        killScores.push_back(0); // set semua nilai killScores menjadi 0
    enemies.clear();             // hapus semua elemen enemies
    enemyBullets.clear();        // hapus semua elemen enemyBullets
}
// Fungsi untuk menembak peluru untuk musuh tertentu
void EnemyManager::shoot(sf::Vector2f playerPos, Enemy enemy, float dt)
{
    reloadingTimer += dt;
    if (reloadingTimer >= enemyReloadTime)
    {
        reloadingTimer = 0;
        enemyReloadTime = 1.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.5 - 1.5)));
        // bullet fire for particular enemy
        Bullet *b = new Bullet(enemy.getPosition(), 2);
        float dx = playerPos.x - enemy.getPosition().x;
        float dy = playerPos.y - enemy.getPosition().y;
        float angle = std::atan2(dy, dx);
        b->setFireAngle(angle);
        enemyBullets.push_back(*b);
    }
}

// Fungsi untuk menggambar musuh
void EnemyManager::drawEnemies(sf::RenderWindow &window)
{
    // Draw shadow musuh
    for (auto i = enemies.begin(); i != enemies.end(); i++)
    {
        window.draw(i->shadowSprite);
    }

    // Draw sprite musuh
    for (auto i = enemies.begin(); i != enemies.end(); i++)
    {
        window.draw(i->sprite);
    }

    // Draw sprite kematian musuh
    for (auto i = deathShadows.begin(); i != deathShadows.end(); i++)
    {
        window.draw(i->first);
    }

    // Draw peluru musuh
    for (auto i = enemyBullets.begin(); i != enemyBullets.end(); i++)
    {
        window.draw(i->sprite);
    }
}