#include "Menu.h"

Menu::Menu()
{
	if (!font.loadFromFile("WindlassExtended.ttf")) {
		std::cout << "error";
	}

	//Play
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Play");
	menu[0].setCharacterSize(70);
	menu[0].setPosition(WINDOW_SIZE / 2, 3 * (GRID_SIZE / 7));
	//Options
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setCharacterSize(70);
	menu[1].setPosition(WINDOW_SIZE / 2, 4 * (GRID_SIZE / 7));
	//Exit
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(70);
	menu[2].setPosition(WINDOW_SIZE / 2, 5 * (GRID_SIZE / 7));

	MenuSelected = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_menu; ++i) {
		window.draw(menu[i]);
	}

}

void Menu::MoveUp()
{
	if (MenuSelected - 1 >= -1) {
		menu[MenuSelected].setFillColor(sf::Color::White);

		MenuSelected--;
		if (MenuSelected == -1) {
			MenuSelected = 2;
		}
		menu[MenuSelected].setFillColor(sf::Color::Yellow);
	}
}

void Menu::MoveDown()
{
	if (MenuSelected + 1 >= 0) {
		menu[MenuSelected].setFillColor(sf::Color::White);

		MenuSelected++;
		if (MenuSelected == 3) {
			MenuSelected = 0;
		}
		menu[MenuSelected].setFillColor(sf::Color::Yellow);
	}
}

Menu::~Menu()
{

}