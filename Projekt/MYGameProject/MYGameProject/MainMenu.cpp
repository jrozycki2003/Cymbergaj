#include "MainMenu.h"

MainMenu::MainMenu(float szer, float wys) {
	font.loadFromFile("Fonts/Aleo-Bold.ttf");
	//graj
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("Graj");
	mainMenu[0].setCharacterSize(80);
	mainMenu[0].setPosition(150, 100);
	// opcje
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Opcje");
	mainMenu[1].setCharacterSize(80);
	mainMenu[1].setPosition(150, 200);
	//Pomoc gry
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Pomoc");
	mainMenu[2].setCharacterSize(80);
	mainMenu[2].setPosition(150, 300);
	//wyjscie
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color::White);
	mainMenu[3].setString("Wyjscie");
	mainMenu[3].setCharacterSize(80);
	mainMenu[3].setPosition(150, 400);

	WyborMenu = -1;
}
MainMenu::~MainMenu() {}//??

//Draw MainMenu
void MainMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; ++i) {
		window.draw(mainMenu[i]);
	}
}

//MoveUp
void MainMenu::MoveUp() {
	if (WyborMenu - 1 >= 0) {
		mainMenu[WyborMenu].setFillColor(sf::Color::White);

		WyborMenu--;
		if (WyborMenu == -1) {
			WyborMenu = 2;
		}
		mainMenu[WyborMenu].setFillColor(sf::Color::Cyan);
	}
}

//MoveDown
void MainMenu::MoveDown() {
	if (WyborMenu + 1 <= Max_main_menu) {
		mainMenu[WyborMenu].setFillColor(sf::Color::White);
		WyborMenu++;
		if (WyborMenu == 4) {
			WyborMenu = 0;
		}
		mainMenu[WyborMenu].setFillColor(sf::Color::Cyan);
	}
}