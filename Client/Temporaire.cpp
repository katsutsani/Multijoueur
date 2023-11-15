#include "Game.h"
#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




int main()
{
   RenderWindow window(sf::VideoMode(960, 960), "Main Menu", Style::Default);
   Menu mainMenu;

    bool start = false;
    bool battle = false;

    RectangleShape background;
    background.setSize(Vector2f(960, 960));
    Texture Maintexture;
    Maintexture.loadFromFile("texture/Background1.png");
    background.setTexture(&Maintexture);

    RectangleShape Titre;
    Titre.setSize(Vector2f(960 * 2 / 3, 200));
    Titre.setPosition(960 / 6, 150.f);
    Texture TextureTitre;
    TextureTitre.loadFromFile("texture/Titre.png");
    Titre.setTexture(&TextureTitre);


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

        window.draw(background);
        window.draw(Titre);
        mainMenu.draw(window);
        window.display();
    }

    return 0;
}
