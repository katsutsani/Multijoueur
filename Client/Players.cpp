#include "Players.h"

Players::Players()
{
	if (!font.loadFromFile("OpenSans-SemiBold.ttf"))
	{
		// erreur...
	}
}

void Players::Draw(sf::RenderWindow& window, Player currentPlayer)
{
	player1.setFont(font);
	player1.setString("Player 1");
	player1.setCharacterSize(24);
	player1.setStyle(sf::Text::Bold);
	player1.setPosition(2, 2);

	sf::VertexArray cross(sf::Lines, 4);
	cross[0].position = sf::Vector2f(40, 40);
	cross[1].position = sf::Vector2f(60, 60);
	cross[2].position = sf::Vector2f(40, 60);
	cross[3].position = sf::Vector2f(60, 40);

	for (int i = 0; i < 4; ++i) {
		cross[i].color = sf::Color::Red;
	}

	player2.setFont(font);
	player2.setString("Player 2");
	player2.setCharacterSize(24);
	player2.setStyle(sf::Text::Bold);
	player2.setPosition(2, WINDOW_SIZE - 40);


	if (currentPlayer == Player::Cross) {
		player1.setFillColor(sf::Color::Green);
		player2.setFillColor(sf::Color::White);
	}
	else {
		player1.setFillColor(sf::Color::White);
		player2.setFillColor(sf::Color::Green);
	}
		

	window.draw(player1);
	window.draw(cross);
	window.draw(player2);
}
