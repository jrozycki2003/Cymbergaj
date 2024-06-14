#include <SFML/Graphics.hpp>
#include <iostream>
#include "Krazki.hpp"
#include "MainMenu.h"
#include "ObslugaGry.hpp"

int main() {
	//glowne okno
	RenderWindow window(VideoMode(800, 600), "Cymbergaj The Game", Style::Default);
	window.setFramerateLimit(60);

	MainMenu mainMenu(window.getSize().x, window.getSize().y);

	ObslugaGry obslugaGry;

	// grafika w tle
	RectangleShape background;
	background.setSize(Vector2f(800, 600));
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Photos/background.jpg");
	background.setTexture(&backgroundTexture);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Up)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down) {
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return) {
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
						cout << "Koniec Gry";
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