#pragma once

#include "Game.h"

#define Max_menu 3

class MenuWindow {
public: 
	MenuWindow();
	void Enter(sf::RenderWindow& window);
	void HandleInput(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void UpdateName(std::string name);

	int isPlaying = 0;
	int isEnteringName = 0;
	int isQuitting = 0;

private: 

	int MenuSelected = 0;
	sf::Font font;
	sf::Text menu[Max_menu];
	sf::Text name;
	sf::Text nameEntered;

};