#include <SFML/Graphics.hpp>
#include <iostream>
#include "Krazki.hpp"
#include "MainMenu.h"
#include "ObslugaGry.hpp"

int main() {
	//glowne okno
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cymbergaj The Game", sf::Style::Default);
	window.setFramerateLimit(60);

	MainMenu mainMenu(window.getSize().x, window.getSize().y);

	ObslugaGry obslugaGry;

	// grafika w tle
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(800, 600));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Photos/background.jpg");
	background.setTexture(&backgroundTexture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == sf::Keyboard::Down) {
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == sf::Keyboard::Return) {
					int x = mainMenu.MainMenuPressed();
					if (x == 0) {
						obslugaGry.graj();
					}

					if (x == 1) {
						obslugaGry.opcje();
					}

					if (x == 2) {
						obslugaGry.Pomoc();
					}
					if (x == 3) {
						window.close();
						std::cout << "Koniec Gry";
						break;
					}
				}
			}
			window.clear();
			window.draw(background);
			mainMenu.draw(window);
			window.display();
		}
	}
}