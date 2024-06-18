#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem> //Dodane

namespace fs = std::filesystem; //Dodane
fs::path fontPath = "Fonts/OpenSans-Bold.ttf"; // �cie�ka do czcionki

class Gracz {
public:
    sf::CircleShape Krazek1; // Pierwszy kr�g
    sf::CircleShape Krazek2; // Drugi kr�g
    bool up1, down1, left1, right1, up2, down2, left2, right2;
    sf::Texture Krazek1Texture, Krazek2Texture;
    // Dodajemy obiekty reprezentuj�ce bramki
    sf::RectangleShape Bramka1;
    sf::RectangleShape Bramka2;

    // Dodajemy zmienne przechowuj�ce wyniki
    int score1 = 0;
    int score2 = 0;
    sf::Texture backgroundTexture; // Nowa zmienna przechowuj�ca tekstur� t�a

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
        float szybkosc = 0.5f; // warto�� pr�dko�ci

        // Aktualizacja ruchu dla pierwszego kr�gu
        if (up1 && Krazek1.getPosition().y > 0) // Sprawdzamy, czy kr�g nie wyjdzie poza g�rn� kraw�d�
            ruch1.y -= szybkosc;
        if (down1 && Krazek1.getPosition().y + Krazek1.getRadius() * 2 < maxY) // Sprawdzamy, czy kr�g nie wyjdzie poza doln� kraw�d�
            ruch1.y += szybkosc;
        if (left1 && Krazek1.getPosition().x > 0) // Sprawdzamy, czy kr�g znajduje si� po lewej stronie okna
            ruch1.x -= szybkosc;
        if (right1 && Krazek1.getPosition().x + Krazek1.getRadius() * 2 < maxX / 2) // Sprawdzamy, czy kr�g nie wyjdzie poza po�ow� szeroko�ci okna
            ruch1.x += szybkosc;

        // Aktualizacja ruchu dla drugiego kr�gu
        if (up2 && Krazek2.getPosition().y > 0) // Sprawdzamy, czy kr�g nie wyjdzie poza g�rn� kraw�d�
            ruch2.y -= szybkosc;
        if (down2 && Krazek2.getPosition().y + Krazek2.getRadius() * 2 < maxY) // Sprawdzamy, czy kr�g nie wyjdzie poza doln� kraw�d�
            ruch2.y += szybkosc;
        if (left2 && Krazek2.getPosition().x > maxX / 2) // Sprawdzamy, czy kr�g znajduje si� w prawej po�owie okna
            ruch2.x -= szybkosc;
        if (right2 && Krazek2.getPosition().x + Krazek2.getRadius() * 2 < maxX) // Sprawdzamy, czy kr�g nie wyjdzie poza praw� kraw�d� okna
            ruch2.x += szybkosc;

        Krazek1.move(ruch1);
        Krazek2.move(ruch2);
    }

    void Wyswietl(sf::RenderWindow& window, const std::string& nazwaGracza1, const std::string& nazwaGracza2) {
        // Rysowanie bramek
        window.draw(Bramka1);
        window.draw(Bramka2);

        // Rysowanie wynik�w
        sf::Font CzcionkaWynik;
        if (!CzcionkaWynik.loadFromFile(fontPath.string())) {
            // Obs�uga b��du wczytywania czcionki
            std::cerr << "Nie mo�na wczyta� czcionki OpenSans-Bold.ttf" << std::endl;
            return;
        }
        sf::Text scoreText;
        scoreText.setFont(CzcionkaWynik);
        scoreText.setCharacterSize(40);
        scoreText.setFillColor(sf::Color::Black);

        // Ustawienie pozycji tekstu dla wynik�w gracza 1
        scoreText.setPosition(255, 50);
        scoreText.setString(std::string(nazwaGracza1) + " " + std::to_string(score1) + " - " + std::to_string(score2) + " " + std::string(nazwaGracza2));
        window.draw(scoreText);

        // Rysowanie pi�ek
        window.draw(Krazek1);
        window.draw(Krazek2);
    }
};

class Pilka {
public:
    sf::CircleShape ball;
    sf::Vector2f predkosc;
    bool CzyGol; // Flaga informuj�ca, czy nast�pi�o zdobycie bramki
    sf::Texture ballTexture; // Tekstura dla pi�ki

    Pilka(float x, float y) {
        CzyGol = false;
        float radius = 40; // Promie� pi�ki

        ball.setRadius(radius);
        ball.setPosition(x, y);

        // Wczytaj tekstur� dla pi�ki z pliku
        ballTexture.loadFromFile("Photos/Dark.png");
        // Ustawienie tekstury dla pi�ki
        ball.setTexture(&ballTexture);

        // Pocz�tkowa pr�dko�� pi�ki
        predkosc.x = 0.4f;
        predkosc.y = 0.4f;
    }

    void kolizja(Gracz& player1, Gracz& player2) {//bierzemy player1 i player2 zeby skorzystac dla nich z funkcji klasy Gracz
        // Ruch pi�ki
        ball.move(predkosc);

        // Sprawdzenie kolizji z kraw�dziami okna
        if (ball.getPosition().x < 0 || ball.getPosition().x + ball.getRadius() * 2 > 800) {
            predkosc.x = -predkosc.x; // Odwr�cenie kierunku po odbiciu od lewej lub prawej kraw�dzi
        }
        if (ball.getPosition().y < 0 || ball.getPosition().y + ball.getRadius() * 2 > 600) {
            predkosc.y = -predkosc.y; // Odwr�cenie kierunku po odbiciu od g�rnej lub dolnej kraw�dzi
        }

        // Sprawdzenie kolizji z k�kami
        if (ball.getGlobalBounds().intersects(player1.Krazek1.getGlobalBounds()) ||//to lub to lub to lub to
            ball.getGlobalBounds().intersects(player1.Krazek2.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(player2.Krazek1.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(player2.Krazek2.getGlobalBounds())) {
            predkosc.x = -predkosc.x; // Odwr�cenie kierunku po odbiciu od k�ek
        }

        // Sprawdzenie kolizji z bramkami
        if (ball.getGlobalBounds().intersects(player1.Bramka1.getGlobalBounds())) {
            // Zwi�kszenie wyniku dla gracza 2 (przeciwnika)
            player2.score2++;
            ResetPilki(player1, player2);
        }
        else if (ball.getGlobalBounds().intersects(player2.Bramka2.getGlobalBounds())) {
            // Zwi�kszenie wyniku dla gracza 1 (przeciwnika)
            player1.score1++;
            ResetPilki(player1, player2);
        }
    }

    void ResetPilki(Gracz& player1, Gracz& player2) {
        // Resetowanie pozycji pi�ki do �rodka planszy
        ball.setPosition(400, 300);
        player1.Krazek1.setPosition(0, 300);
        player2.Krazek2.setPosition(750, 300);

        // Przywr�cenie pierwotnej pr�dko�ci pi�ki
        predkosc.x = 0.4f;
        predkosc.y = 0.4f;
    }

    void Wyswietl(sf::RenderWindow& window) {
        window.draw(ball);
    }
};