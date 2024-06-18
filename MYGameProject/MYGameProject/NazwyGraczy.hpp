#include <SFML/Graphics.hpp>
#include <regex> //Dodane
#include <algorithm> // Dodanie biblioteki dla funkcji sortowania
#include <ranges>

class NazwijGraczy {
public:

    std::string nazwaGracza1;
    std::string nazwaGracza2;

    // Dodane: Funkcja sprawdzaj¹ca poprawnoœæ nazwy gracza za pomoc¹ wyra¿eñ regularnych
bool sprawdzNazwe(const std::string & nazwa) {
    // Nazwa gracza mo¿e zawieraæ tylko litery i spacje
    std::regex wzor("^[a-zA-Z]+$");
    return std::regex_match(nazwa, wzor);
}

void wczytajNazwyGraczy() {
    std::ifstream plik("nazwy_graczy.txt");
    if (plik.is_open()) {
        std::getline(plik, nazwaGracza1);
        std::getline(plik, nazwaGracza2);
        plik.close();
    }
}

void zapiszNazwyGraczy() {
    std::ofstream plik("nazwy_graczy.txt");
    if (plik.is_open()) {
        plik << nazwaGracza1 << std::endl;
        plik << nazwaGracza2 << std::endl;
        plik.close();
    }
}

void wprowadzNazwyGraczy() {
    const int maxDlugosc = 8; // Maksymalna d³ugoœæ nicku gracza
    sf::Font czcionka;
    if (!czcionka.loadFromFile(fontPath.string())) {
        std::cerr << "Nie mo¿na wczytaæ czcionki" << std::endl;// Obs³uga b³êdu wczytywania czcionki
        return;
    }

    sf::Text text;
    text.setFont(czcionka);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);
    text.setString("Wprowadz nazwe gracza 1:");

    sf::Text textGracz1;
    textGracz1.setFont(czcionka);
    textGracz1.setCharacterSize(24);
    textGracz1.setFillColor(sf::Color::White);
    textGracz1.setPosition(20, 60);

    sf::Text textGracz2;
    textGracz2.setFont(czcionka);
    textGracz2.setCharacterSize(24);
    textGracz2.setFillColor(sf::Color::White);
    textGracz2.setPosition(20, 100);

    bool wprowadzGracza1 = true;
    bool wprowadzGracza2 = false;

    // Wczytaj nazwy graczy z pliku
    wczytajNazwyGraczy();

    // Przypisz wczytane nazwy do zmiennych
    textGracz1.setString(nazwaGracza1);
    textGracz2.setString(nazwaGracza2);

    sf::RenderWindow window(sf::VideoMode(400, 200), "Wprowadz nazwy graczy");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (wprowadzGracza1) {
                    if (event.text.unicode == 8 && !nazwaGracza1.empty()) { // Backspace
                        nazwaGracza1.pop_back();
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13 &&
                        nazwaGracza1.size() < maxDlugosc) { // Sprawdzenie d³ugoœci nicku
                        // Dodane: Sprawdzenie poprawnoœci nazwy gracza i d³ugoœci
                        if (sprawdzNazwe(nazwaGracza1 + static_cast<char>(event.text.unicode))) {
                            nazwaGracza1 += event.text.unicode;
                        }
                    }
                    textGracz1.setString(nazwaGracza1);
                }
                else if (wprowadzGracza2) {
                    if (event.text.unicode == 8 && !nazwaGracza2.empty()) { // Backspace
                        nazwaGracza2.pop_back();
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13 &&
                        nazwaGracza2.size() < maxDlugosc) { // Sprawdzenie d³ugoœci nicku
                        // Dodane: Sprawdzenie poprawnoœci nazwy gracza i d³ugoœci
                        if (sprawdzNazwe(nazwaGracza2 + static_cast<char>(event.text.unicode))) {
                            nazwaGracza2 += event.text.unicode;
                        }
                    }
                    textGracz2.setString(nazwaGracza2);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (wprowadzGracza1) {
                    wprowadzGracza1 = false;
                    wprowadzGracza2 = true;
                    text.setString("Wprowadz nazwe gracza 2:");
                }
                else if (wprowadzGracza2) {
                    wprowadzGracza2 = false;
                    zapiszNazwyGraczy(); // Zapisz nazwy graczy po zakoñczeniu wprowadzania
                    window.close();
                }
            }
        }
        window.clear();
        window.draw(text);
        window.draw(textGracz1);
        window.draw(textGracz2);
        window.display();
    }
} 
};

// Klasa do obs³ugi tabeli wyników
class TabelaWynikow {
public:
    std::vector<std::pair<std::string, int>> wyniki;

    void wczytajTabeleWynikow(const std::string& nazwaPliku) {
        wyniki.clear();
        std::ifstream plik(nazwaPliku);
        if (plik.is_open()) {
            std::string nick;
            int liczbaZwyciestw;
            while (plik >> nick >> liczbaZwyciestw) {
                wyniki.push_back({ nick, liczbaZwyciestw });
            }
            plik.close();
        }
    }

    void zapiszTabeleWynikow(const std::string& nazwaPliku) {
        std::ofstream plik(nazwaPliku);
        if (plik.is_open()) {
            for (const auto& para : wyniki) {
                plik << para.first << " " << para.second << std::endl;
            }
            plik.close();
        }
    }

    void wyswietlTabeleWynikow(sf::RenderWindow& window, sf::Font& font) {
        std::ranges::sort(wyniki, [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(50, 50);

        std::string wynikiText;
        for (const auto& para : wyniki) {
            wynikiText += para.first + ": " + std::to_string(para.second) + " pkt.\n";
        }
        text.setString(wynikiText);

        sf::Text tabelaText;
        tabelaText.setFont(font);
        tabelaText.setCharacterSize(20);
        tabelaText.setFillColor(sf::Color::White);
        tabelaText.setPosition(50, 20);
        tabelaText.setString("KLASYFIKACJA:");

        sf::Text infoText;
        infoText.setFont(font);
        infoText.setCharacterSize(16);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(205, 200);
        infoText.setString("Enter - Nowa Gra\nEsc - Menu Glowne");

        window.clear();
        window.draw(text);
        window.draw(tabelaText);
        window.draw(infoText);
        window.display();
    }
};