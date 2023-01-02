#include "map.h"

Map::Map(sf::Vector2f windowSize)
{
    this->windowSize = windowSize;

    // loading rock textures
    mapObjects[0].loadFromFile("assets/Environment/rock1.png");
    mapObjects[1].loadFromFile("assets/Environment/rock2.png");
    mapObjects[2].loadFromFile("assets/Environment/rock3.png");
    mapObjects[3].loadFromFile("assets/Environment/cluster1.png");
    mapObjects[4].loadFromFile("assets/Environment/cluster2.png");
    mapObjects[5].loadFromFile("assets/Environment/cluster3.png");
}

// Fungsi initMap() digunakan untuk menginisialisasi peta pada saat game pertama kali dimulai.
// Fungsi ini mengeload 8 "quad" yang terletak di tengah, atas, bawah, kiri, dan kanan dari tengah.
// Setiap "quad" terdiri dari beberapa objek peta, yang dihasilkan oleh fungsi spwanObjectsInQuad().

void Map::initMap(Camera view)
{
    // Men-load 8 "quad" yang terletak di tengah, atas, bawah, kiri, dan kanan dari tengah.
    spwanObjectsInQuad(sf::Vector2i(0, 0), view);   // Tengah
    spwanObjectsInQuad(sf::Vector2i(-1, -1), view); // Atas kiri
    spwanObjectsInQuad(sf::Vector2i(0, -1), view);  // Atas
    spwanObjectsInQuad(sf::Vector2i(1, -1), view);  // Atas kanan
    spwanObjectsInQuad(sf::Vector2i(-1, 0), view);  // Kiri
    spwanObjectsInQuad(sf::Vector2i(1, 0), view);   // Kanan
    spwanObjectsInQuad(sf::Vector2i(-1, 1), view);  // Bawah kiri
    spwanObjectsInQuad(sf::Vector2i(0, 1), view);   // bawah
    spwanObjectsInQuad(sf::Vector2i(1, 1), view);   // bawah kanan
}

// Fungsi spwanObjectsInQuad akan membuat dan menambahkan sprite ke vector quads
void Map::spwanObjectsInQuad(sf::Vector2i quadIndex, Camera view)
{
    // Menentukan koordinat kiri dan atas dari quad yang akan dibuat
    int quadLeft = quadIndex.x * view.playerView.getSize().x - view.playerView.getSize().x / 2;
    int quadUp = quadIndex.y * view.playerView.getSize().y - view.playerView.getSize().y / 2;

    // Membuat objek quad sementara
    quad temp;
    temp.x = quadIndex.x;
    temp.y = quadIndex.y;

    // Pengulangan untuk membuat objek sprite sebanyak maxNumberOfMapObject
    for (int i = 0; i < maxNumberOfMapObject; i++)
    {
        // Menentukan posisi acak dari objek sprite
        int x = std::rand() % (static_cast<int>(view.playerView.getSize().x)) + quadLeft;
        int y = std::rand() % (static_cast<int>(view.playerView.getSize().y)) + quadUp;

        // Menentukan tipe objek sprite acak
        int objectType = std::rand() % 6;

        // Membuat sprite sementara
        sf::Sprite tempSprite;

        // Mengeset texture dari sprite sementara sesuai dengan tipe objek yang terpilih
        tempSprite.setTexture(mapObjects[objectType]);

        // Mengeset skala sprite sementara sesuai dengan tipe objek yang terpilih
        if (objectType <= 2)
        {
            float scale = 0.005 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.1 - 0.005)));
            tempSprite.setScale(scale, scale);
        }
        else
        {
            float scale = 0.05 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.15 - 0.05)));
            tempSprite.setScale(scale, scale);
        }

        // Mengeset warna sprite sementara sesuai dengan backgroundColor
        tempSprite.setColor(backgroundColor);

        // Mengeset posisi sprite sementara
        tempSprite.setPosition(x, y);

        // Menambahkan sprite sementara ke dalam vector objek pada objek quad sementara
        temp.objects.push_back(tempSprite);
    }

    // Menambahkan objek quad sementara ke dalam vector quads
    quads.push_back(temp);
}

// Fungsi removeQuad akan menghapus objek quad yang memiliki indeks sesuai dengan input quadIndex dari vector quads
void Map::removeQuad(sf::Vector2i quadIndex)
{
    // Menentukan iterator pertama pada vector quads
    auto i = quads.begin();
    // Pengulangan sampai iterator mencapai akhir vector quads
    while (i != quads.end())
    {
        // Jika objek quad memiliki indeks sesuai dengan input quadIndex, objek quad tersebut dihapus dari vector quads
        if (i->x == quadIndex.x && i->y == quadIndex.y)
            i = quads.erase(i);
        // Jika tidak, iterator diincrement
        else
            i++;
    }
}

// Fungsi update akan memperbarui quads yang terlihat oleh player dan menghapus quads yang tidak terlihat
void Map::update(Camera view, bool keyPressed, sf::Vector2f playerPos)
{
    // Menentukan indeks quad yang sedang dilihat oleh player saat ini
    sf::Vector2i currViewIndex = sf::Vector2i(playerPos.x / windowSize.x, playerPos.y / windowSize.y);
    // Jika indeks quad tidak berubah, tidak perlu memperbarui quads
    if (oldViewIndex == currViewIndex)
        return;

    // Player berpindah ke quad yang berbeda. Memerlukan pembaruan quads
    if (currViewIndex.x != oldViewIndex.x)
    {
        // Player berpindah ke quad di sebelah kiri
        if (oldViewIndex.x > currViewIndex.x)
        {
            // Memuat quad di kiri atas
            spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y - 1), view);
            // Menghapus quad di kanan atas
            removeQuad(sf::Vector2i(currViewIndex.x + 2, currViewIndex.y - 1));

            // Memuat quad di sebelah kiri
            spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y), view);
            // Menghapus quad di sebelah kanan
            removeQuad(sf::Vector2i(currViewIndex.x + 2, currViewIndex.y));

            // Memuat quad di kiri bawah
            spwanObjectsInQuad(sf::Vector2i(currViewIndex.x - 1, currViewIndex.y + 1), view);
            // Menghapus quad di kanan bawah
            removeQuad(sf::Vector2i(currViewIndex.x + 2, currViewIndex.y + 1));
        }
        else
        { // Player berpindah ke quad di sebelah kanan
            // Memuat quad di kanan atas
            spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y - 1), view);
            // Menghapus quad di kiri atas
            removeQuad(sf::Vector2i(currViewIndex.x - 2, currViewIndex.y - 1));
            // Memuat quad di sebelah kanan
            spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y), view);
            // Menghapus quad di sebelah kiri
            removeQuad(sf::Vector2i(currViewIndex.x - 2, currViewIndex.y));
            // Memuat quad di kanan bawah
            spwanObjectsInQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y + 1), view);
            // Menghapus quad di sebelah kanan
            removeQuad(sf::Vector2i(currViewIndex.x + 1, currViewIndex.y - 2));
        }
    }
    // mengupdate nilai oldViewIndex dengan nilai currViewIndex.
    oldViewIndex = currViewIndex;
}

// Fungsi outsideView akan mengembalikan true jika posisi object di luar view yang ditunjuk oleh Camera
bool Map::outsideView(sf::Sprite object, Camera view)
{
    // Menentukan posisi batas kiri, kanan, atas, dan bawah dari view yang ditunjuk oleh Camera
    int viewLeft = view.playerView.getCenter().x - view.playerView.getSize().x / 2;
    int viewRight = view.playerView.getCenter().x + view.playerView.getSize().x / 2;
    int viewUp = view.playerView.getCenter().y - view.playerView.getSize().y / 2;
    int viewDown = view.playerView.getCenter().y + view.playerView.getSize().y / 2;

    // Jika posisi object di luar batas view yang ditunjuk oleh Camera, mengembalikan true
    if (object.getPosition().x < viewLeft || object.getPosition().x > viewRight ||
        object.getPosition().y < viewUp || object.getPosition().y > viewDown)
        return true;
    else
        return false;
}

// Fungsi draw akan menampilkan semua objek yang terdapat pada quads
void Map::draw(sf::RenderWindow &window)
{
    // Pengulangan sampai iterator mencapai akhir vector quads
    for (auto i = quads.begin(); i != quads.end(); i++)
    {
        // Pengulangan sampai iterator mencapai akhir vector objects pada objek quad
        for (auto j = i->objects.begin(); j != i->objects.end(); j++)
            window.draw(*j);
    }
}