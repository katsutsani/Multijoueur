#pragma once

#include "Game.h"

#define Max_menu 3

class MenuWindow {
public: 
	MenuWindow();
	void Enter();
	void HandleInput(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

private: 

	int MenuSelected = 0;
	sf::Font font;
	sf::Text menu[Max_menu];

};