#pragma once
#include "framework.h"
#include <cstdlib>
#include <ctime>

#include "Players.h"
#include "ClientSocket.h"

const int _SIZE = 3;

class Game
{
public:
	Game();
	void HandleInput(sf::RenderWindow& window);
	void HandleMouseClick(sf::RenderWindow& window);
	void AIMove();
	void AICheckWin();
	void Update(sf::RenderWindow& window, ClientSocket client);
	void Render(sf::RenderWindow& window, Players* players);
	void DrawPlayer1(sf::RenderWindow& window, int row, int col);
	void DrawPlayer2(sf::RenderWindow& window, int row, int col);
	void SwitchPlayer();
	bool CheckWinner();
	void DisplayWinner();
	void CheckPosBoard();
	void BoardModif(std::string pos, std::string token);
	ClientSocket m_client;

	Player currentPlayer;
	Player board[_SIZE][_SIZE];
	std::string changeToken;

private:
	bool end = false;

};