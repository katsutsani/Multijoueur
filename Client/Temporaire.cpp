#include "Game.h"
#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




int main()
{
   RenderWindow window(sf::VideoMode(960, 960), "Main Menu", Style::Default);
   Menu mainMenu;


    while (window.isOpen())
    {
        window.clear();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }

                if (event.key.code == Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }

                if (event.key.code == Keyboard::Return)
                {



                    int x = mainMenu.MenuPressed();
                    if (x == 0)
                    {
                        sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, GRID_SIZE), "Tic Tac Toe");

                        Game game;

                        while (window.isOpen()) {
                            game.Update(window);
                            game.Render(window);
                        }
                    }

                    if (x == 1)
                    {
                        
                    }
                    if (x == 2)
                    {
                        window.close();
                        break;
                    }

                }
            }
        }

        mainMenu.draw(window);
        window.display();
    }

    return 0;
}
