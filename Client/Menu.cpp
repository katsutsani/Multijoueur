#include "Menu.h"

Menu::Menu()
{
	if (!font.loadFromFile("WindlassExtended.ttf")) {
		std::cout << "error";
	}

	//Play
	menu[0].setFont(font);
	menu[0].setFillColor(Color::White);
	menu[0].setString("Play");
	menu[0].setCharacterSize(70);
	menu[0].setPosition(305, 500);
	//Options
	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Options");
	menu[1].setCharacterSize(70);
	menu[1].setPosition(305, 600);
	//Exit
	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(70);
	menu[2].setPosition(305, 700);

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
		menu[MenuSelected].setFillColor(Color::White);

		MenuSelected--;
		if (MenuSelected == -1) {
			MenuSelected = 2;
		}
		menu[MenuSelected].setFillColor(Color::Yellow);
	}
}

void Menu::MoveDown()
{
	if (MenuSelected + 1 >= 0) {
		menu[MenuSelected].setFillColor(Color::White);

		MenuSelected++;
		if (MenuSelected == 3) {
			MenuSelected = 0;
		}
		menu[MenuSelected].setFillColor(Color::Yellow);
	}
}

Menu::~Menu()
{

}
