#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem> //Dodane

namespace fs = std::filesystem; //Dodane
fs::path fontPath = "Fonts/OpenSans-Bold.ttf"; // Œcie¿ka do czcionki

class Gracz {
public:
    sf::CircleShape Krazek1; // Pierwszy kr¹g
    sf::CircleShape Krazek2; // Drugi kr¹g
    bool up1, down1, left1, right1, up2, down2, left2, right2;
    sf::Texture Krazek1Texture, Krazek2Texture;
    // Dodajemy obiekty reprezentuj¹ce bramki
    sf::RectangleShape Bramka1;
    sf::RectangleShape Bramka2;

    // Dodajemy zmienne przechowuj¹ce wyniki
    int score1 = 0;
    int score2 = 0;
    sf::Texture backgroundTexture; // Nowa zmienna przechowuj¹ca teksturê t³a

    Gracz(float x, float y)
    {
        // Inicjalizacja gracza 1
        Krazek1.setRadius(50);
        Krazek1.setPosition(0, 300);
        up1 = down1 = left1 = right1 = false;

        // Inicjalizacja gracza 2
        Krazek2.setRadius(50);
        Krazek2.setPosition(750, 300);
        up2 = down2 = left2 = right2 = false;

        // Wczytaj tekstury dla Krazek1 i Krazek2
        Krazek1Texture.loadFromFile("Photos/Puck1_texture.png");
        Krazek2Texture.loadFromFile("Photos/Puck2_texture.png");

        // Ustawienie tekstur dla Krazek1 i Krazek2
        Krazek1.setTexture(&Krazek1Texture);
        Krazek2.setTexture(&Krazek2Texture);

        // Inicjalizacja bramek
        Bramka1.setSize(sf::Vector2f(10, 200)); // Wymiary bramki
        Bramka1.setPosition(0, 200); // Pozycja bramki gracza 1
        Bramka1.setFillColor(sf::Color::Transparent);
        Bramka1.setOutlineColor(sf::Color::White);

        Bramka2.setSize(sf::Vector2f(10, 200)); // Wymiary bramki
        Bramka2.setPosition(790, 200); // Pozycja bramki gracza 2
        Bramka2.setFillColor(sf::Color::Transparent);
        Bramka2.setOutlineColor(sf::Color::White);
    }
    void SterowanieKrazek1(sf::Keyboard::Key klawisz, bool wcisniete)
    {
        if (wcisniete == true)
        {
            if (klawisz == sf::Keyboard::W)
                up1 = true;
            if (klawisz == sf::Keyboard::S)
                down1 = true;
            if (klawisz == sf::Keyboard::A)
                left1 = true;
            if (klawisz == sf::Keyboard::D)
                right1 = true;
        }
        if (wcisniete == false)
        {
            up1 = false;
            down1 = false;
            left1 = false;
            right1 = false;
        }
    }

    void SterowanieKrazek2(sf::Keyboard::Key klawisz, bool wcisniete)
    {
        if (wcisniete == true)
        {
            if (klawisz == sf::Keyboard::Up)
                up2 = true;
            if (klawisz == sf::Keyboard::Down)
                down2 = true;
            if (klawisz == sf::Keyboard::Left)
                left2 = true;
            if (klawisz == sf::Keyboard::Right)
                right2 = true;
        }
        if (wcisniete == false)
        {
            up2 = false;
            down2 = false;
            left2 = false;
            right2 = false;
        }
    }

    void RuchKrazka(float maxX, float maxY)
    {
        sf::Vector2f ruch1;
        sf::Vector2f ruch2;
        float szybkosc = 0.5f; // wartoœæ prêdkoœci

        // Aktualizacja ruchu dla pierwszego krêgu
        if (up1 && Krazek1.getPosition().y > 0) // Sprawdzamy, czy kr¹g nie wyjdzie poza górn¹ krawêdŸ
            ruch1.y -= szybkosc;
        if (down1 && Krazek1.getPosition().y + Krazek1.getRadius() * 2 < maxY) // Sprawdzamy, czy kr¹g nie wyjdzie poza doln¹ krawêdŸ
            ruch1.y += szybkosc;
        if (left1 && Krazek1.getPosition().x > 0) // Sprawdzamy, czy kr¹g znajduje siê po lewej stronie okna
            ruch1.x -= szybkosc;
        if (right1 && Krazek1.getPosition().x + Krazek1.getRadius() * 2 < maxX / 2) // Sprawdzamy, czy kr¹g nie wyjdzie poza po³owê szerokoœci okna
            ruch1.x += szybkosc;

        // Aktualizacja ruchu dla drugiego krêgu
        if (up2 && Krazek2.getPosition().y > 0) // Sprawdzamy, czy kr¹g nie wyjdzie poza górn¹ krawêdŸ
            ruch2.y -= szybkosc;
        if (down2 && Krazek2.getPosition().y + Krazek2.getRadius() * 2 < maxY) // Sprawdzamy, czy kr¹g nie wyjdzie poza doln¹ krawêdŸ
            ruch2.y += szybkosc;
        if (left2 && Krazek2.getPosition().x > maxX / 2) // Sprawdzamy, czy kr¹g znajduje siê w prawej po³owie okna
            ruch2.x -= szybkosc;
        if (right2 && Krazek2.getPosition().x + Krazek2.getRadius() * 2 < maxX) // Sprawdzamy, czy kr¹g nie wyjdzie poza praw¹ krawêdŸ okna
            ruch2.x += szybkosc;

        Krazek1.move(ruch1);
        Krazek2.move(ruch2);
    }

    void Wyswietl(sf::RenderWindow& window, const std::string& nazwaGracza1, const std::string& nazwaGracza2) {
        // Rysowanie bramek
        window.draw(Bramka1);
        window.draw(Bramka2);

        // Rysowanie wyników
        sf::Font CzcionkaWynik;
        if (!CzcionkaWynik.loadFromFile(fontPath.string())) {
            // Obs³uga b³êdu wczytywania czcionki
            std::cerr << "Nie mo¿na wczytaæ czcionki OpenSans-Bold.ttf" << std::endl;
            return;
        }
        sf::Text scoreText;
        scoreText.setFont(CzcionkaWynik);
        scoreText.setCharacterSize(40);
        scoreText.setFillColor(sf::Color::Black);

        // Ustawienie pozycji tekstu dla wyników gracza 1
        scoreText.setPosition(255, 50);
        scoreText.setString(std::string(nazwaGracza1) + " " + std::to_string(score1) + " - " + std::to_string(score2) + " " + std::string(nazwaGracza2));
        window.draw(scoreText);

        // Rysowanie pi³ek
        window.draw(Krazek1);
        window.draw(Krazek2);
    }
};

class Pilka {
public:
    sf::CircleShape ball;
    sf::Vector2f predkosc;
    bool CzyGol; // Flaga informuj¹ca, czy nast¹pi³o zdobycie bramki
    sf::Texture ballTexture; // Tekstura dla pi³ki

    Pilka(float x, float y) {
        CzyGol = false;
        float radius = 40; // Promieñ pi³ki

        ball.setRadius(radius);
        ball.setPosition(x, y);

        // Wczytaj teksturê dla pi³ki z pliku
        ballTexture.loadFromFile("Photos/Dark.png");
        // Ustawienie tekstury dla pi³ki
        ball.setTexture(&ballTexture);

        // Pocz¹tkowa prêdkoœæ pi³ki
        predkosc.x = 0.4f;
        predkosc.y = 0.4f;
    }

    void kolizja(Gracz& player1, Gracz& player2) {//bierzemy player1 i player2 zeby skorzystac dla nich z funkcji klasy Gracz
        // Ruch pi³ki
        ball.move(predkosc);

        // Sprawdzenie kolizji z krawêdziami okna
        if (ball.getPosition().x < 0 || ball.getPosition().x + ball.getRadius() * 2 > 800) {
            predkosc.x = -predkosc.x; // Odwrócenie kierunku po odbiciu od lewej lub prawej krawêdzi
        }
        if (ball.getPosition().y < 0 || ball.getPosition().y + ball.getRadius() * 2 > 600) {
            predkosc.y = -predkosc.y; // Odwrócenie kierunku po odbiciu od górnej lub dolnej krawêdzi
        }

        // Sprawdzenie kolizji z kó³kami
        if (ball.getGlobalBounds().intersects(player1.Krazek1.getGlobalBounds()) ||//to lub to lub to lub to
            ball.getGlobalBounds().intersects(player1.Krazek2.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(player2.Krazek1.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(player2.Krazek2.getGlobalBounds())) {
            predkosc.x = -predkosc.x; // Odwrócenie kierunku po odbiciu od kó³ek
        }

        // Sprawdzenie kolizji z bramkami
        if (ball.getGlobalBounds().intersects(player1.Bramka1.getGlobalBounds())) {
            // Zwiêkszenie wyniku dla gracza 2 (przeciwnika)
            player2.score2++;
            ResetPilki(player1, player2);
        }
        else if (ball.getGlobalBounds().intersects(player2.Bramka2.getGlobalBounds())) {
            // Zwiêkszenie wyniku dla gracza 1 (przeciwnika)
            player1.score1++;
            ResetPilki(player1, player2);
        }
    }

    void ResetPilki(Gracz& player1, Gracz& player2) {
        // Resetowanie pozycji pi³ki do œrodka planszy
        ball.setPosition(400, 300);
        player1.Krazek1.setPosition(0, 300);
        player2.Krazek2.setPosition(750, 300);

        // Przywrócenie pierwotnej prêdkoœci pi³ki
        predkosc.x = 0.4f;
        predkosc.y = 0.4f;
    }

    void Wyswietl(sf::RenderWindow& window) {
        window.draw(ball);
    }
};