#include "Game.h"

Game::Game()
    : currentPlayer(Player::Cross)
{
    for (int i = 0; i < _SIZE; ++i) {
        for (int j = 0; j < _SIZE; ++j) {
            board[i][j] = Player::None;
        }
    }
}

void Game::HandleInput(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (currentPlayer == Player::Cross) {
                    HandleMouseClick(window);
                }
            }
        }
    }
}

void Game::HandleMouseClick(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int col = (mousePos.x - INFO_SIZE) / (GRID_SIZE / _SIZE);
    int row = mousePos.y / (GRID_SIZE / _SIZE);

    if (col >= 0 && col < _SIZE && row >= 0 && row < _SIZE && board[row][col] == Player::None && mousePos.x > INFO_SIZE) {
        board[row][col] = currentPlayer;
        CheckWinner();
        if (end == false)
        {
            SwitchPlayer();
        }
        if (currentPlayer == Player::Circle) {
            AIMove();
        }
    }
}

void Game::AIMove()
{
    std::vector<std::pair<int, int>> availableMoves;

    for (int i = 0; i < _SIZE; ++i) {
        for (int j = 0; j < _SIZE; ++j) {
            if (board[i][j] == Player::None) {
                availableMoves.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!availableMoves.empty()) {
        std::srand(std::time(0));
        int randomIndex = std::rand() % availableMoves.size();
        std::pair<int, int> move = availableMoves[randomIndex];
        board[move.first][move.second] = currentPlayer;
        CheckWinner();
        SwitchPlayer();
    }
}

void Game::AICheckWin()
{
    /*for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == Player::None) {

                board[i][j] = Player::Cross;



                board[i][j] = Player::None;
            }
        }
    }*/
}

void Game::Update(sf::RenderWindow& window)
{
    HandleInput(window);
}

void Game::Render(sf::RenderWindow& window)
{
    window.clear();

    for (int i = 1; i < _SIZE; ++i) {
        sf::Vertex line[] = {
            sf::Vector2f(i * GRID_SIZE / _SIZE + INFO_SIZE, 0),
            sf::Vector2f(i * GRID_SIZE / _SIZE + INFO_SIZE, GRID_SIZE)
        };
        window.draw(line, 2, sf::Lines);

        sf::Vertex line2[] = {
            sf::Vector2f(INFO_SIZE, i * GRID_SIZE / _SIZE),
            sf::Vector2f(WINDOW_SIZE, i * GRID_SIZE / _SIZE)
        };
        window.draw(line2, 2, sf::Lines);
    }

    for (int i = 0; i < _SIZE; ++i) {
        for (int j = 0; j < _SIZE; ++j) {
            if (board[i][j] == Player::Cross) {
                DrawPlayer1(window, i, j);
            }
            else if (board[i][j] == Player::Circle) {
                DrawPlayer2(window, i, j);
            }
        }
    }

    players.Draw(window, currentPlayer);

    window.display();
}

void Game::DrawPlayer1(sf::RenderWindow& window, int row, int col)
{
    sf::VertexArray cross(sf::Lines, 4);
    cross[0].position = sf::Vector2f(col * GRID_SIZE / _SIZE + INFO_SIZE, row * GRID_SIZE / _SIZE);
    cross[1].position = sf::Vector2f((col + 1) * GRID_SIZE / _SIZE + INFO_SIZE, (row + 1) * GRID_SIZE / _SIZE);
    cross[2].position = sf::Vector2f((col + 1) * GRID_SIZE / _SIZE + INFO_SIZE, row * GRID_SIZE / _SIZE);
    cross[3].position = sf::Vector2f(col * GRID_SIZE / _SIZE + INFO_SIZE, (row + 1) * GRID_SIZE / _SIZE);

    for (int i = 0; i < 4; ++i) {
        cross[i].color = sf::Color::Red;
    }

    window.draw(cross);
}

void Game::DrawPlayer2(sf::RenderWindow& window, int row, int col)
{
    sf::CircleShape circle(GRID_SIZE / _SIZE / 2 - 5);
    circle.setPosition(col * GRID_SIZE / _SIZE + INFO_SIZE, row * GRID_SIZE / _SIZE);
    circle.setFillColor(sf::Color::Blue);
    circle.setOutlineThickness(5);
    circle.setOutlineColor(sf::Color::Blue);

    window.draw(circle);
}

void Game::SwitchPlayer()
{
    currentPlayer = (currentPlayer == Player::Cross) ? Player::Circle : Player::Cross;
}

void Game::CheckWinner()
{
    // lignes et colonnes
    for (int i = 0; i < _SIZE; ++i) {
        if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            DisplayWinner();
            return;
        }
        if (board[0][i] != Player::None && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            DisplayWinner();
            return;
        }
    }

    // diagonales
    if (board[0][0] != Player::None && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        DisplayWinner();
        return;
    }
    if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        DisplayWinner();
        return;
    }
}

void Game::DisplayWinner()
{
    //std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
    end = true;
}
