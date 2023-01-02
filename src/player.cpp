// file player.cpp
#include "player.h"

Player::Player(sf::Vector2f startingPos, sf::Vector2f windowSize)
{
    // set ukuran dan posisi awal dari player
    this->setSize(colRectSize);
    this->setOrigin(this->getSize().x / 2, this->getSize().y / 2);
    this->position = startingPos;
    this->setPosition(position);
    this->windowSize = windowSize;
}

void Player::load(void)
{
    // memuat tekstur untuk gerakan jalan dari semua tiga karakter
    for (int i = 0; i < 3; i++)
    {
        std::string walkTexureFileName = charTexureFileName + "Char_" + std::to_string(i + 1) + "/" + "walk.png";
        walkTexture[i].loadFromFile(walkTexureFileName);
    }
    // memuat tekstur untuk gerakan diam dari semua tiga karakter
    for (int i = 0; i < 3; i++)
    {
        std::string idleTexureFileName = charTexureFileName + "Char_" + std::to_string(i + 1) + "/" + "idle.png";
        idleTexture[i].loadFromFile(idleTexureFileName);
    }

    // memuat tekstur untuk gerakan mati dari semua tiga karakter
    for (int i = 0; i < 3; i++)
    {
        std::string deathTexureFileName = charTexureFileName + "Char_" + std::to_string(i + 1) + "/" + "death.png";
        deathTexture[i].loadFromFile(deathTexureFileName);
    }
    // mengatur karakter awal menjadi karakter ke-2
    setCharacterType(2);

    // memuat tekstur untuk bayangan
    shadowTex.loadFromFile("assets/Extras/shadow.png");
    shadow.setTexture(shadowTex);
    shadow.setScale(0.035, 0.035);

    // memuat suara
    deathSoundBuf.loadFromFile("assets/Sounds/Player_sounds/death.wav");
    deathSound.setBuffer(deathSoundBuf);
    hurtSoundBuf.loadFromFile("assets/Sounds/Player_sounds/umph.wav");
    hurtSound.setBuffer(hurtSoundBuf);

    // menandai bahwa sumber daya telah berhasil dimuat
    resourceLoaded = true;
}

// update() fungsi untuk mengupdate posisi dan rotasi player dan senjata sesuai dengan gerakan keyboard dan posisi mouse
void Player::update(float dt, bool keyPressed, sf::Vector2f mousePos, std::list<Bullet> &enemyBullets, Weapons &weapon)
{
    // gerakan keyboard
    sf::Vector2f oldPos = position;
    if (!isDead) // jika player belum mati
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // jika tombol A atau Left ditekan
        {
            position.x -= moveSpeed * dt; // gerak ke kiri
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // jika tombol D atau Right ditekan
        {
            position.x += moveSpeed * dt; // gerak ke kanan
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // jika tombol W atau Up ditekan
        {
            position.y -= moveSpeed * dt; // gerak ke atas
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            position.y += moveSpeed * dt; // gerak ke bawah
        }
    }
    // Menempatkan shadow di bawah karakter
    shadow.setPosition(position.x - 30, position.y - 5);

    // Menghitung jarak dan sudut antara posisi mouse dengan posisi senjata
    float dx = mousePos.x - weapon.gunSprite.getPosition().x;
    float dy = mousePos.y - weapon.gunSprite.getPosition().y;
    float angle = std::atan2(dy, dx);

    // Mengubah sudut dari radian ke derajat
    angle = angle * (180 / 3.1415);

    // Menetapkan rotasi senjata sesuai dengan sudut yang dihitung
    weapon.gunSprite.setRotation(angle);
    weapon.muzzleFlash.setRotation(angle);

    // Menentukan apakah senjata harus dibalik atau tidak berdasarkan posisi mouse
    flipped = (mousePos.x < position.x) ? true : false;

    // Menentukan skala yang harus diterapkan pada senjata
    if (flipped)
    {
        weapon.gunSprite.setScale(weapon.scaleSize.x, -weapon.scaleSize.y);
    }
    else
    {
        weapon.gunSprite.setScale(weapon.scaleSize);
    }

    // Memindahkan posisi senjata sesuai dengan posisi mouse dan posisi player
    if (mousePos.y < position.y)
        gunBehindPlayer = true;
    else
        gunBehindPlayer = false;

    // setelah posisi dari player diupdate, posisi dari senjata juga diupdate
    this->setPosition(position);

    // posisi senjata diatur agar selalu di depan player dengan menambahkan offset spritePosOffset ke posisi player
    weapon.gunSprite.setPosition(this->getPosition() + weapon.spritePosOffset);

    // jika senjata di flip (terbalik), maka posisinya diubah sebesar 20 pada sumbu x
    if (flipped)
        weapon.gunSprite.setPosition(weapon.gunSprite.getPosition().x - 20, weapon.gunSprite.getPosition().y);
    else
        weapon.gunSprite.setPosition(weapon.gunSprite.getPosition().x + 20, weapon.gunSprite.getPosition().y);

    // animations
    // jika player telah mati dan animasi kematian belum selesai, jalankan animasi kematian
    if (isDead && !deathAnimEnd)
    {
        animateDeath(dt);
        return;
    }

    // jika player belum mati,
    if (!isDead)
    {
        // jika posisi lama sama dengan posisi saat ini (tidak bergerak), jalankan animasi idle
        if (oldPos == position)
        {
            playerIdle = true;
            animateIdle(dt, scaleSize);
        }
        else
        {
            // jika tidak, jalankan animasi berjalan
            playerIdle = false;
            animateWalk(dt);
        }
    }

    // jika animasi kematian telah selesai, hitung waktu selama 3 detik sebelum menandai deathSceneEnd sebagai true
    if (deathAnimEnd)
    {
        deathSceneKeepTimer += dt;
        if (deathSceneKeepTimer > 3)
            deathSceneEnd = true;
    }

    // collision with enemy bullets
    auto i = enemyBullets.begin();
    while (i != enemyBullets.end())
    {
        // Mengurangi health player sebesar 10 jika terkena peluru musuh
        if (this->isColliding(*i))
        {
            this->health -= 10; // comment this line and you will be invincible

            // Memainkan suara hurt jika player masih hidup
            if (!deathAnimEnd)
                hurtSound.play();
            // Merubah warna sprite player menjadi merah jika terkena peluru musuh
            playerSprite.setColor(sf::Color::Red);

            // Mengeset isDead menjadi true jika health player sudah <= 0
            if (this->health <= 0)
            {
                isDead = true;
                // Memainkan suara death jika player sudah mati
                if (deathSound.getStatus() != sf::Sound::Playing)
                    deathSound.play();
                this->setFillColor(sf::Color::Red);
            }
            // Menghapus peluru musuh yang telah mengenai player dari list enemyBullets
            i = enemyBullets.erase(i);
        }
        else
            i++;
    }
}

// fungsi ini akan mengubah tipe karakter yang dimainkan oleh player (0-2)
// dan mengubah sprite yang digunakan sesuai dengan tipe karakter tersebut
void Player::setCharacterType(int type)
{
    // walkSprite, idleSprite, dan deathSprite akan di-set texture dan textureRectnya sesuai dengan tipe karakter yang dipilih
    // type varries between 0-2
    // walk sprites
    characterType = type;
    walkSprite.setTexture(walkTexture[characterType]);
    walkSprite.setTextureRect(sf::IntRect(currWalkTex * subTexRectSize, 0, subTexRectSize, subTexRectSize));
    walkSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
    walkSprite.setScale(scaleSize);

    // idle sprites
    idleSprite.setTexture(idleTexture[characterType]);
    idleSprite.setTextureRect(sf::IntRect(currIdleTex * subTexRectSize, 0, subTexRectSize, subTexRectSize));
    idleSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
    idleSprite.setScale(scaleSize);
    playerSprite = idleSprite; // initial sprite

    // death sprties
    deathSprite.setTexture(deathTexture[characterType]);
    deathSprite.setTextureRect(sf::IntRect(currDeathTex * subTexRectSize, 0, subTexRectSize, subTexRectSize));
    deathSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
    deathSprite.setScale(scaleSize);
}

// fungsi getCharacterType akan mengembalikan tipe karakter yang sedang dimainkan oleh player
int Player::getCharacterType(void)
{
    return this->characterType;
}

// fungsi getHealth akan mengembalikan nilai health dari player saat ini
int Player::getHealth(void)
{
    return this->health;
}

void Player::resetStates(void)
{
    this->health = 100;
    this->characterType = 0;
    deathSceneKeepTimer = 0;
    position = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
    currIdleTex = currWalkTex = currDeathTex = 0;
    playerIdle = true;
    flipped = false;
    gunBehindPlayer = false;
    hitAnimated = true;
    isDead = false;
    deathAnimEnd = false;
    deathSceneEnd = false;
}

// Proses animasi saat player tidak bergerak
void Player::animateIdle(float dt, sf::Vector2f requiredScale)
{
    // Menambahkan waktu pada timer animasi idle
    idleAnimTimer += dt;
    // Jika timer animasi idle sudah mencapai batas animasi idle yang diinginkan,
    // maka reset timer animasi idle dan ganti texture frame idle yang ditampilkan
    if (idleAnimTimer >= idleAnimTime)
    {
        idleAnimTimer = 0;

        // Ganti frame texture yang ditampilkan
        currIdleTex++;
        if (currIdleTex == maxIdleTex)
            currIdleTex = 0;
        idleSprite.setTextureRect(sf::IntRect(currIdleTex * subTexRectSize, 0, subTexRectSize, subTexRectSize + 150));
        idleSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
        idleSprite.setScale(sf::Vector2f(2.0f, 2.0f));

        // Flip sprite jika diperlukan
        if (flipped)
            idleSprite.setScale(-requiredScale.x, requiredScale.y);
        else
            idleSprite.setScale(requiredScale);
    }

    // Set posisi sprite idle sesuai dengan posisi player
    idleSprite.setPosition(position - spritePosOffset);
    playerSprite = idleSprite; // Set sprite yang akan ditampilkan pada player
}

// Proses animasi saat player berjalan
void Player::animateWalk(float dt)
{
    // Menambahkan waktu pada timer animasi walk
    walkAnimTimer += dt;
    // Jika timer animasi walk sudah mencapai batas animasi walk yang diinginkan,
    // maka reset timer animasi walk dan ganti texture frame walk yang ditampilkan
    if (walkAnimTimer >= walkAnimTime)
    {
        walkAnimTimer = 0;

        // Ganti frame texture yang ditampilkan
        currWalkTex++;
        if (currWalkTex == maxWalkTex)
            currWalkTex = 0;
        walkSprite.setTextureRect(sf::IntRect(currWalkTex * subTexRectSize, 0, subTexRectSize, subTexRectSize + 150));
        walkSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
        walkSprite.setScale(sf::Vector2f(2.0f, 2.0f));

        // Flip sprite jika diperlukan
        if (flipped)
            walkSprite.setScale(-scaleSize.x, scaleSize.y);
        else
            walkSprite.setScale(scaleSize);
    }
    // Set posisi sprite walk sesuai dengan posisi player
    walkSprite.setPosition(position - spritePosOffset);
    playerSprite = walkSprite; // Set sprite yang akan ditampilkan pada player
}

// Proses animasi saat player death
void Player::animateDeath(float dt)
{
    // Menambahkan waktu pada timer animasi death
    deathAnimTimer += dt;
    // Jika timer animasi death sudah mencapai batas animasi death yang diinginkan,
    // maka reset timer animasi death dan ganti texture frame death yang ditampilkan
    if (deathAnimTimer >= deathAnimTime)
    {
        deathAnimTimer = 0;

        // Ganti frame texture yang ditampilkan
        currDeathTex++;
        if (currDeathTex == maxDeathTex)
        {
            deathAnimEnd = true;
        }

        deathSprite.setTextureRect(sf::IntRect(currDeathTex * subTexRectSize, 0, subTexRectSize, subTexRectSize + 230));
        deathSprite.setOrigin(subTexRectSize / 2, subTexRectSize / 2);
        deathSprite.setScale(scaleSize);

        // Flip sprite jika diperlukan
        if (flipped)
            deathSprite.setScale(-scaleSize.x, scaleSize.y);
        else
            deathSprite.setScale(scaleSize);
    }
    // Set posisi sprite death sesuai dengan posisi player
    deathSprite.setPosition(position - spritePosOffset);
    playerSprite = deathSprite; // Set sprite yang akan ditampilkan pada player
}

// Fungsi ini akan menggambar sprite player dan sprite senjata di layar sesuai dengan gameState yang sedang aktif
void Player::draw(sf::RenderWindow &window, Weapons wp, int gameState)
{
    // Jika gunBehindPlayer bernilai true, maka sprite senjata akan ditaruh di belakang sprite player
    if (gunBehindPlayer)
    {
        if (!isDead && gameState == 4)
        {
            window.draw(wp.gunSprite);
            if (wp.renderFlash) // Jika wp.renderFlash bernilai true, maka sprite muzzleFlash akan ditampilkan di layar
                window.draw(wp.muzzleFlash);
        }
        window.draw(playerSprite);
    }
    // Jika tidak, maka sprite player akan ditaruh di belakang sprite senjata
    else
    {
        window.draw(playerSprite);
        if (!isDead && gameState == 4)
        {
            window.draw(wp.gunSprite);
            if (wp.renderFlash) // Jika wp.renderFlash bernilai true, maka sprite muzzleFlash akan ditampilkan di layar
                window.draw(wp.muzzleFlash);
        }
    }
    // Jika player sudah mati, maka sprite senjata tidak akan ditampilkan di layar
    // Jika gameState selain 4 (4 adalah state saat game sedang dimainkan), maka sprite senjata juga tidak akan ditampilkan di layar
}
