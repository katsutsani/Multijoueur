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

    name.setFont(font);
    name.setFillColor(sf::Color::White);
    name.setString("Enter a name :");
    name.setCharacterSize(70);
    name.setPosition(WINDOW_SIZE / 4, GRID_SIZE / 3);

    nameEntered.setFont(font);
    nameEntered.setFillColor(sf::Color::White);
    nameEntered.setString("");
    nameEntered.setCharacterSize(70);
    nameEntered.setPosition(WINDOW_SIZE / 4, 2 * GRID_SIZE / 3);

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

void MenuWindow::Enter(sf::RenderWindow& window, std::string name, ClientSocket client) 
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
        name = "name" + name;
        client.SendInfo(name.c_str());
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
    if (isEnteringName == 0) 
    {
        for (int i = 0; i < Max_menu; ++i) {
            window.draw(menu[i]);
        }
    }
    else
    {
        window.draw(name);
        window.draw(nameEntered);
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

void MenuWindow::UpdateName(std::string name)
{
    nameEntered.setString(name);
}
