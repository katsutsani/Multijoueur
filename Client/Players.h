#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

const int WINDOW_SIZE = 300;

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