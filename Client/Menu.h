#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Players.h"

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
	sf::Font font;
	sf::Text menu[Max_menu];

};