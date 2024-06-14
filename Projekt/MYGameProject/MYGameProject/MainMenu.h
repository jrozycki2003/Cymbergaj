#include <SFML/Graphics.hpp>
#define Max_main_menu 4

class MainMenu
{
public:
	MainMenu(float szer, float wys);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return WyborMenu;
	}
	~MainMenu();
private:
	int WyborMenu;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
};