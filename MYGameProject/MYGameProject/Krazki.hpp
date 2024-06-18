#include <SFML/Graphics.hpp>
#include <filesystem> //Dodane

namespace fs = std::filesystem; //Dodane
fs::path fontPath = "Fonts/OpenSans-Bold.ttf"; // Œcie¿ka do czcionki

class Gracz {
public:
    sf::Sprite Krazek; // Zmiana na sf::Sprite
    bool up, down, left, right;
    sf::Texture KrazekTexture;
    sf::Texture backgroundTexture;

    Gracz(const std::string& texturePath, const sf::Vector2f& position) : up(false), down(false), left(false), right(false)
    {
        KrazekTexture.loadFromFile(texturePath); // £adowanie tekstury
        Krazek.setTexture(KrazekTexture); // Ustawienie tekstury dla sprite'a
        Krazek.setPosition(position);
    }

    virtual void Sterowanie(sf::Keyboard::Key klawisz, bool wcisniete) = 0;
    virtual void Ruch(float maxX, float maxY) = 0;
    virtual void Wyswietl(sf::RenderWindow& window, const std::string& nazwaGracza) = 0;
};

class Gracz1 : public Gracz {
public:
    int score1 = 0;
    sf::RectangleShape Bramka1;

    Gracz1() : Gracz("Photos/Puck1_texture.png", sf::Vector2f(0, 300))
    {

        // Inicjalizacja bramek
        Bramka1.setSize(sf::Vector2f(10, 200)); // Wymiary bramki
        Bramka1.setPosition(0, 200); // Pozycja bramki gracza 1
        Bramka1.setFillColor(sf::Color::Transparent);
        Bramka1.setOutlineColor(sf::Color::White);
    }

    void Sterowanie(sf::Keyboard::Key klawisz, bool wcisniete) override {
        if (wcisniete == true) {
            if (klawisz == sf::Keyboard::W)
                up = true;
            if (klawisz == sf::Keyboard::S)
                down = true;
            if (klawisz == sf::Keyboard::A)
                left = true;
            if (klawisz == sf::Keyboard::D)
                right = true;
        }
        else {
            up = false;
            down = false;
            left = false;
            right = false;
        }
    }

    void Ruch(float maxX, float maxY) override {
        sf::Vector2f ruch;
        float szybkosc = 1.2f;

        if (up && Krazek.getPosition().y > 0)
            ruch.y -= szybkosc;
        if (down && Krazek.getPosition().y + Krazek.getGlobalBounds().height < maxY)
            ruch.y += szybkosc;
        if (left && Krazek.getPosition().x > 0)
            ruch.x -= szybkosc;
        if (right && Krazek.getPosition().x + Krazek.getGlobalBounds().width < maxX/2)
            ruch.x += szybkosc;

        Krazek.move(ruch);
    }

    void Wyswietl(sf::RenderWindow& window, const std::string& nazwaGracza) override {
        window.draw(Bramka1);

        // Rysowanie wyników
        sf::Font CzcionkaWynik;
        if (!CzcionkaWynik.loadFromFile(fontPath.string())) {
            // Obs³uga b³êdu wczytywania czcionki
            std::cerr << "Nie mo¿na wczytaæ czcionki" << std::endl;
            return;
        }
        sf::Text scoreText;
        scoreText.setFont(CzcionkaWynik);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(250, 40);
        scoreText.setString(nazwaGracza + " " + std::to_string(score1));
        window.draw(scoreText);

        window.draw(Krazek);
    }
};

class Gracz2 : public Gracz {
public:
    int score2 = 0;
    sf::RectangleShape Bramka2;

    Gracz2() : Gracz("Photos/Puck2_texture.png", sf::Vector2f(750, 300))
    {
        Bramka2.setSize(sf::Vector2f(10, 200)); // Wymiary bramki
        Bramka2.setPosition(790, 200); // Pozycja bramki gracza 2
        Bramka2.setFillColor(sf::Color::Transparent);
        Bramka2.setOutlineColor(sf::Color::White);
    }

    void Sterowanie(sf::Keyboard::Key klawisz, bool wcisniete) override {
        if (wcisniete == true) {
            if (klawisz == sf::Keyboard::Up)
                up = true;
            if (klawisz == sf::Keyboard::Down)
                down = true;
            if (klawisz == sf::Keyboard::Left)
                left = true;
            if (klawisz == sf::Keyboard::Right)
                right = true;
        }
        else {
            up = false;
            down = false;
            left = false;
            right = false;
        }
    }

    void Ruch(float maxX, float maxY) override {
        sf::Vector2f ruch;
        float szybkosc = 1.2f;

        if (up && Krazek.getPosition().y > 0)
            ruch.y -= szybkosc;
        if (down && Krazek.getPosition().y + Krazek.getGlobalBounds().height < maxY)
            ruch.y += szybkosc;
        if (left && Krazek.getPosition().x > maxX/2)
            ruch.x -= szybkosc;
        if (right && Krazek.getPosition().x + Krazek.getGlobalBounds().width < maxX)
            ruch.x += szybkosc;

        Krazek.move(ruch);
    }

    void Wyswietl(sf::RenderWindow& window, const std::string& nazwaGracza) override {
        window.draw(Bramka2);

        sf::Font CzcionkaWynik;
        if (!CzcionkaWynik.loadFromFile(fontPath.string())) {
            // Obs³uga b³êdu wczytywania czcionki
            std::cerr << "Nie mo¿na wczytaæ czcionki" << std::endl;
            return;
        }
        sf::Text scoreText;
        scoreText.setFont(CzcionkaWynik);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(450, 40);
        scoreText.setString(std::to_string(score2) + " " + nazwaGracza);
        window.draw(scoreText);

        window.draw(Krazek);
    }
};

class Pilka {
public:
    sf::Sprite ball;
    sf::Vector2f predkosc;
    bool CzyGol;
    sf::Texture ballTexture;
    bool wRuchu;

    Pilka(float x, float y) {
        CzyGol = false;
        wRuchu = false; // Pi³ka na pocz¹tku nie jest w ruchu
        float radius = 55;

        ball.setPosition(x, y);
        ballTexture.loadFromFile("Photos/Dark.png");
        ball.setTexture(ballTexture); // Ustawienie tekstury dla sprite'a
        ball.setScale(radius * 2 / ballTexture.getSize().x, radius * 2 / ballTexture.getSize().y); // Dopasowanie skali

        predkosc.x = 1.0f;
        predkosc.y = 1.0f;
    }

    void kolizja(Gracz1& player1, Gracz2& player2) {
        if (wRuchu) {
            ball.move(predkosc);
        }

        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::FloatRect player1Bounds = player1.Krazek.getGlobalBounds();
        sf::FloatRect player2Bounds = player2.Krazek.getGlobalBounds();
        sf::FloatRect goal1Bounds = player1.Bramka1.getGlobalBounds();
        sf::FloatRect goal2Bounds = player2.Bramka2.getGlobalBounds();

        // Kolizja z krawêdziami ekranu
        if (ballBounds.left <= 0 || ballBounds.left + ballBounds.width >= 800) {
            predkosc.x = -predkosc.x;
            // Zapobieganie utkniêciu w krawêdzi
            if (ballBounds.left <= 0)
                ball.setPosition(0, ballBounds.top);
            if (ballBounds.left + ballBounds.width >= 800)
                ball.setPosition(800 - ballBounds.width, ballBounds.top);
        }
        if (ballBounds.top <= 0 || ballBounds.top + ballBounds.height >= 600) {
            predkosc.y = -predkosc.y;
            // Zapobiega utkniêciu w krawêdzi
            if (ballBounds.top <= 0)
                ball.setPosition(ballBounds.left, 0);
            if (ballBounds.top + ballBounds.height >= 600)
                ball.setPosition(ballBounds.left, 600 - ballBounds.height);
        }

        // Kolizja z graczami
        if (ballBounds.intersects(player1Bounds)) {
            sf::Vector2f ballCenter = sf::Vector2f(ballBounds.left + ballBounds.width / 2, ballBounds.top + ballBounds.height / 2);
            sf::Vector2f playerCenter = sf::Vector2f(player1Bounds.left + player1Bounds.width / 2, player1Bounds.top + player1Bounds.height / 2);
            sf::Vector2f direction = ballCenter - playerCenter;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;
            predkosc = direction * std::sqrt(predkosc.x * predkosc.x + predkosc.y * predkosc.y);
            wRuchu = true; // Pi³ka zaczyna siê poruszaæ po dotkniêciu przez gracza
        }
        else if (ballBounds.intersects(player2Bounds)) {
            sf::Vector2f ballCenter = sf::Vector2f(ballBounds.left + ballBounds.width / 2, ballBounds.top + ballBounds.height / 2);
            sf::Vector2f playerCenter = sf::Vector2f(player2Bounds.left + player2Bounds.width / 2, player2Bounds.top + player2Bounds.height / 2);
            sf::Vector2f direction = ballCenter - playerCenter;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;
            predkosc = direction * std::sqrt(predkosc.x * predkosc.x + predkosc.y * predkosc.y);
            wRuchu = true; // Pi³ka zaczyna siê poruszaæ po dotkniêciu przez gracza
        }

        // Kolizja z bramkami
        if (ballBounds.intersects(goal1Bounds)) {
            player2.score2++;
            ResetPilki(player1, player2);
        }
        else if (ballBounds.intersects(goal2Bounds)) {
            player1.score1++;
            ResetPilki(player1, player2);
        }
    }

    void ResetPilki(Gracz& player1, Gracz& player2) {
        ball.setPosition(400, 300);
        player1.Krazek.setPosition(0, 300);
        player2.Krazek.setPosition(750, 300);

        predkosc.x = 1.0f;
        predkosc.y = 1.0f;
        wRuchu = false; // Pi³ka przestaje siê poruszaæ
    }

    void Wyswietl(sf::RenderWindow& window) {
        window.draw(ball);
    }
};
