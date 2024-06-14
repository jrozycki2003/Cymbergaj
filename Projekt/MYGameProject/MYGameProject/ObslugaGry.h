#include <SFML/Graphics.hpp>
#include <fstream>
#include "NazwyGraczy.hpp"
#include "Boostery.hpp"
#include "Krazki.hpp"

class ObslugaGry {
public:
    sf::RenderWindow Graj;
    Gracz1 player1;
    Gracz2 player2;
    Pilka ball{ 400,300 };
    NazwijGraczy nazwijgraczy;

    // Dla obiektu SpeedUp
    float maxX = 800; // Maksymalna wspó³rzêdna x (szerokoœæ okna)
    float maxY = 600; // Maksymalna wspó³rzêdna y (wysokoœæ okna)
    SpeedUp Item_Up{ maxX,maxY };// Utworzenie obiektu SpeedUp
    SpeedDown Item_Down{ maxX,maxY };// Utworzenie obiektu SpeedDown

    sf::Texture BackgroundTla[3];
    bool enableSpeedUp, enableSpeedDown = true;
    int liczbaBramek = 5;
    int WybraneTlo = 0;

    void graj();
    void Pomoc();
    void opcje();

    void RestartGry();
};
