#pragma once

#include "Game.h"
#include "ClientSocket.h"

#define Max_menu 3

class MenuWindow {
public: 
	MenuWindow();
	void Enter(sf::RenderWindow& window, std::string name, ClientSocket client);
	void HandleInput(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int isPlaying = 0;
	int isEnteringName = 0;
	int isQuitting = 0;

private: 

	int MenuSelected = 0;
	sf::Font font;
	sf::Text menu[Max_menu];

};