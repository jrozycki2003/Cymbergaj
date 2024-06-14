#include <SFML/Graphics.hpp>
#include <random>

int random(const int& min, const int& max)
{
    std::default_random_engine silnik;
    silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rozklad(min, max);

    return rozklad(silnik);
}

class ZmianaPredkosci {
public:
    sf::CircleShape obiekt;
    sf::Vector2f pozycja;
    sf::Vector2f predkosc;
    bool CzyAktywny; // Flaga okre�laj�ca, czy obiekt jest aktywny
    sf::Texture obiektTexture; // Tekstura dla obiektu przyspieszenia

    ZmianaPredkosci(float szybkX, float szybkY, const std::string& texturePath) : predkosc(szybkX, szybkY), CzyAktywny(true) {
        obiekt.setRadius(15); // Ustawienie promienia obiektu
        obiektTexture.loadFromFile(texturePath); // Wczytaj tekstur�
        obiekt.setTexture(&obiektTexture); // Ustawienie tekstury
        obiekt.setPosition(pozycja); // Ustawienie pozycji
    }

    virtual void SpeedKolizja(Pilka& ball) = 0;
    virtual void Wyswietl(sf::RenderWindow& window) {
        if (CzyAktywny) // Rysujemy obiekt tylko je�li jest aktywny
            window.draw(obiekt);
    }
};

class SpeedUp : public ZmianaPredkosci {
public:
    SpeedUp(float maxX, float maxY) : ZmianaPredkosci(maxX, maxY, "Photos/Boost.png") // Przekazanie wsp�rz�dnych i �cie�ki tekstury do konstruktora klasy bazowej
    {
        // Wylosuj wsp�rz�dne x i y w zakresie od 0 do maxX oraz od 0 do maxY
        float x = random(0, maxX);
        float y = random(0, maxY);

        // Ustaw wsp�rz�dne obiektu na wylosowane warto�ci
        obiekt.setPosition(x, y);
    }

    void SpeedKolizja(Pilka& ball) override {
        if (CzyAktywny && obiekt.getGlobalBounds().intersects(ball.ball.getGlobalBounds())) {
            ball.predkosc *= 6.0f; // Przy�pieszenie pi�ki o 20%
            CzyAktywny = false; // Dezaktywacja obiektu
        }
    }

    void Wyswietl(sf::RenderWindow& window) override {
        ZmianaPredkosci::Wyswietl(window); // Wywo�anie metody z klasy bazowej
    }
};

class SpeedDown : public ZmianaPredkosci {
public:
    SpeedDown(float maxX, float maxY) : ZmianaPredkosci(maxX, maxY, "Photos/Slow.png") // Przekazanie wsp�rz�dnych i �cie�ki tekstury do konstruktora klasy bazowej
    {
        // Wylosuj wsp�rz�dne x i y w zakresie od 0 do maxX oraz od 0 do maxY
        float x = random(0, maxX);
        float y = random(0, maxY);

        // Ustaw wsp�rz�dne obiektu na wylosowane warto�ci
        obiekt.setPosition(x, y);
    }

    void SpeedKolizja(Pilka& ball) override {
        if (CzyAktywny && obiekt.getGlobalBounds().intersects(ball.ball.getGlobalBounds())) {
            ball.predkosc *= 0.5f; // Spowolnienie pi�ki
            CzyAktywny = false; // Dezaktywacja obiektu
        }
    }

    void Wyswietl(sf::RenderWindow& window) override {
        ZmianaPredkosci::Wyswietl(window); // Wywo�anie metody z klasy bazowej
    }
};