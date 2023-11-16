#include "Game.h"

int WinMain() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, GRID_SIZE), "Tic Tac Toe");

    Game game;

    std::ifstream j("test.json");
    json data = json::parse(j);

    

    json jsonfile;
    int victory = data["emile"]["victory"];
    victory++;
    jsonfile["emile"]["victory"] = victory;

    std::ofstream f("test.json");
    f << jsonfile;

    while (window.isOpen()) {
        game.Update(window);
        game.Render(window);
    }

    return 0;
}
