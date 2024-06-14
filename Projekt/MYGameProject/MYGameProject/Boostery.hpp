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
    bool CzyAktywny; // Flaga okreœlaj¹ca, czy obiekt jest aktywny
    sf::Texture obiektTexture; // Tekstura dla obiektu przyspieszenia

    ZmianaPredkosci(float szybkX, float szybkY, const std::string& texturePath) : predkosc(szybkX, szybkY), CzyAktywny(true) {
        obiekt.setRadius(15); // Ustawienie promienia obiektu
        obiektTexture.loadFromFile(texturePath); // Wczytaj teksturê
        obiekt.setTexture(&obiektTexture); // Ustawienie tekstury
        obiekt.setPosition(pozycja); // Ustawienie pozycji
    }

    virtual void SpeedKolizja(Pilka& ball) = 0;
    virtual void Wyswietl(sf::RenderWindow& window) {
        if (CzyAktywny) // Rysujemy obiekt tylko jeœli jest aktywny
            window.draw(obiekt);
    }
};

class SpeedUp : public ZmianaPredkosci {
public:
    SpeedUp(float maxX, float maxY) : ZmianaPredkosci(maxX, maxY, "Photos/Boost.png") // Przekazanie wspó³rzêdnych i œcie¿ki tekstury do konstruktora klasy bazowej
    {
        // Wylosuj wspó³rzêdne x i y w zakresie od 0 do maxX oraz od 0 do maxY
        float x = random(0, maxX);
        float y = random(0, maxY);

        // Ustaw wspó³rzêdne obiektu na wylosowane wartoœci
        obiekt.setPosition(x, y);
    }

    void SpeedKolizja(Pilka& ball) override {
        if (CzyAktywny && obiekt.getGlobalBounds().intersects(ball.ball.getGlobalBounds())) {
            ball.predkosc *= 6.0f; // Przyœpieszenie pi³ki o 20%
            CzyAktywny = false; // Dezaktywacja obiektu
        }
    }

    void Wyswietl(sf::RenderWindow& window) override {
        ZmianaPredkosci::Wyswietl(window); // Wywo³anie metody z klasy bazowej
    }
};

class SpeedDown : public ZmianaPredkosci {
public:
    SpeedDown(float maxX, float maxY) : ZmianaPredkosci(maxX, maxY, "Photos/Slow.png") // Przekazanie wspó³rzêdnych i œcie¿ki tekstury do konstruktora klasy bazowej
    {
        // Wylosuj wspó³rzêdne x i y w zakresie od 0 do maxX oraz od 0 do maxY
        float x = random(0, maxX);
        float y = random(0, maxY);

        // Ustaw wspó³rzêdne obiektu na wylosowane wartoœci
        obiekt.setPosition(x, y);
    }

    void SpeedKolizja(Pilka& ball) override {
        if (CzyAktywny && obiekt.getGlobalBounds().intersects(ball.ball.getGlobalBounds())) {
            ball.predkosc *= 0.5f; // Spowolnienie pi³ki
            CzyAktywny = false; // Dezaktywacja obiektu
        }
    }

    void Wyswietl(sf::RenderWindow& window) override {
        ZmianaPredkosci::Wyswietl(window); // Wywo³anie metody z klasy bazowej
    }
};