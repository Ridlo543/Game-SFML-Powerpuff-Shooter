#pragma once
#include "player.h"
#include <array>

// membuat struct dengan nama quad yang memiliki tiga variabel
// x dan y sebagai koordinat lokasi quad
// objects sebagai list dari sprite objek yang ada di quad tersebut
typedef struct quad
{
    int x;
    int y;
    std::list<sf::Sprite> objects;
} quad;

class Map
{
private:
    int maxNumberOfMapObject = 6; // menyimpan maksimal jumlah objek yang dapat ditampilkan di map
    sf::Vector2f windowSize;

    sf::Texture mapObjects[6];                      // menyimpan tekstur dari objek-objek yang ada di map
    sf::Vector2i oldViewIndex = sf::Vector2i(0, 0); // menyimpan koordinat quad lama yang sedang ditampilkan di layar

    std::list<quad> quads; // list dari struct quad yang telah dibuat sebelumnya

public:
    // menyimpan warna latar belakang map
    sf::Color backgroundColor = sf::Color(255, 188, 232);

    Map(sf::Vector2f windowSize);                                      // konstruktor kelas Map
    void initMap(Camera view);                                         // menginisialisasi map dengan membuat objek-objek di map sesuai dengan pandangan camera
    void spwanObjectsInQuad(sf::Vector2i quadIndex, Camera view);      // men-spawn objek di quad yang sesuai dengan indeks quad yang diberikan dan pandangan camera saat ini
    void removeQuad(sf::Vector2i quadIndex);                           // menghapus quad yang sesuai dengan indeks quad yang diberikan
    void update(Camera view, bool keyPressed, sf::Vector2f playerPos); // mengupdate map dengan memastikan objek-objek yang ditampilkan sesuai dengan pandangan camera
    bool outsideView(sf::Sprite object, Camera view);                  // mengecek apakah suatu objek berada di luar pandangan camera atau tidak
    void draw(sf::RenderWindow &window);                               // menampilkan map ke layar
};