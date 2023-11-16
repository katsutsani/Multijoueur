#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

#define Max_menu 3

class Menu
{
public:
	Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MenuPressed() {
		return MenuSelected;
	}
	~Menu();

private:

	int MenuSelected;
	Font font;
	Text menu[Max_menu];

};