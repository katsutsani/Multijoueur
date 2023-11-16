#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Players.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

const int SIZE = 3;

class Game
{
public:
	Game();
	void HandleInput(sf::RenderWindow& window);
	void HandleMouseClick(sf::RenderWindow& window);
	void AIMove();
	void AICheckWin();
	void Update(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);
	void DrawPlayer1(sf::RenderWindow& window, int row, int col);
	void DrawPlayer2(sf::RenderWindow& window, int row, int col);
	void SwitchPlayer();
	void CheckWinner();
	void DisplayWinner();

	Player currentPlayer;

private:
	Player board[SIZE][SIZE];
	bool end = false;
	Players players;

};