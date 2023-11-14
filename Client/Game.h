#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int _SIZE = 3;
const int WINDOW_SIZE = 300;

enum class Player { None, Cross, Circle };

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

private:
	Player currentPlayer;
	Player board[_SIZE][_SIZE];
	bool end = false;

};