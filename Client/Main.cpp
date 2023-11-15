#include "Game.h"
#include "ClientSocket.h"

int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, char* szCmdLine, int iCmdShow) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Tic Tac Toe");

    Game game;

    ClientSocket client;
    while (window.isOpen()) {
        game.Update(window);
        game.Render(window);
    }

    return 0;
}
