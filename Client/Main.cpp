#include "Game.h"

int WinMain() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, GRID_SIZE), "Tic Tac Toe");

    Game game;

    while (window.isOpen()) {
        game.Update(window);
        game.Render(window);
    }

    return 0;
}
