#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

const int INFO_SIZE = 200;
const int GRID_SIZE = 600;
const int WINDOW_SIZE = GRID_SIZE + INFO_SIZE;

enum class Player { None, Cross, Circle };

class Players
{
public :
	Players();
	void Draw(sf::RenderWindow& window, Player currentPlayer);

private :
	sf::Font font;
	sf::Text player1;
	sf::Text player2;

};