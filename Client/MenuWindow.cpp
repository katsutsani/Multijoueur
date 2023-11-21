#include "MenuWindow.h"

MenuWindow::MenuWindow() {
    if (!font.loadFromFile("WindlassExtended.ttf")) {
        std::cout << "error";
    }

    //Play
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Play");
    menu[0].setCharacterSize(70);
    menu[0].setPosition(WINDOW_SIZE / 2, 3 * (GRID_SIZE / 7));
    //Options
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setCharacterSize(70);
    menu[1].setPosition(WINDOW_SIZE / 2, 4 * (GRID_SIZE / 7));
    //Exit
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(70);
    menu[2].setPosition(WINDOW_SIZE / 2, 5 * (GRID_SIZE / 7));
}

void MenuWindow::HandleInput(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void MenuWindow::Enter(sf::RenderWindow& window) 
{
    if (isEnteringName == 0) 
    {
        int x = MenuSelected;
        if (x == 0)
        {
            isEnteringName = 1;
        }

        if (x == 1)
        {

        }

        if (x == 2)
        {
            isQuitting = 1;
        }
    }
    else
    {
        isEnteringName = 0;
        isPlaying = 1;
    }
}

void MenuWindow::Update(sf::RenderWindow& window)
{
    HandleInput(window);
}

void MenuWindow::Render(sf::RenderWindow& window)
{
    window.clear();
        
    for (int i = 0; i < Max_menu; ++i) {
        window.draw(menu[i]);
    }
    window.display();
}

void MenuWindow::MoveUp()
{
    if (MenuSelected - 1 >= -1) {
        menu[MenuSelected].setFillColor(sf::Color::White);

        MenuSelected--;
        if (MenuSelected == -1) {
            MenuSelected = 2;
        }
        menu[MenuSelected].setFillColor(sf::Color::Yellow);
    }
}

void MenuWindow::MoveDown()
{
    if (MenuSelected + 1 >= 0) {
        menu[MenuSelected].setFillColor(sf::Color::White);

        MenuSelected++;
        if (MenuSelected == 3) {
            MenuSelected = 0;
        }
        menu[MenuSelected].setFillColor(sf::Color::Yellow);
    }
}
