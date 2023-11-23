#include "Players.h"

Players::Players()
{
	if (!font.loadFromFile("OpenSans-SemiBold.ttf"))
	{
		// erreur...
	}

	player1.setString("Player 1");
	player1.setFont(font);
	player1.setCharacterSize(24);
	player1.setStyle(sf::Text::Bold);
	player1.setPosition(2, 2);

	player2.setString("Player 2");
	player2.setFont(font);
	player2.setCharacterSize(24);
	player2.setStyle(sf::Text::Bold);
	player2.setPosition(2, GRID_SIZE - 40);
}

void Players::SetPlayersString(std::string name, int index)
{
	std::string p1 = player1.getString();
	std::string p2 = player2.getString();
	if (index == 0)
	{
		player1.setString(name);
	}
	else if (index == 1)
	{
		player2.setString(name);
	}
}

void Players::Draw(sf::RenderWindow& window, Player currentPlayer)
{

	sf::VertexArray cross(sf::Lines, 4);
	cross[0].position = sf::Vector2f(40, 40);
	cross[1].position = sf::Vector2f(60, 60);
	cross[2].position = sf::Vector2f(40, 60);
	cross[3].position = sf::Vector2f(60, 40);

	for (int i = 0; i < 4; ++i) {
		cross[i].color = sf::Color::Red;
	}


	sf::CircleShape circle(GRID_SIZE / 32);
	circle.setPosition(40, GRID_SIZE - 60);
	circle.setFillColor(sf::Color::Blue);
	circle.setOutlineThickness(5);
	circle.setOutlineColor(sf::Color::Blue);


	if (currentPlayer == Player::Cross) {
		player1.setFillColor(sf::Color::Green);
		player2.setFillColor(sf::Color::White);
	}
	else {
		player1.setFillColor(sf::Color::White);
		player2.setFillColor(sf::Color::Green);
	}

	if (change == true)
	{
		player1.setFillColor(sf::Color::Red);
		player2.setFillColor(sf::Color::Red);
	}
		

	window.draw(player1);
	window.draw(cross);
	window.draw(player2);
	window.draw(circle);
}


void Players::RenderWinner(int ID)
{
	if (ID == 1)
	{
		change = true;
	}
	else if (ID == 2)
	{
		change = true;
	}
}
