#include "Game.h"
#include "Menu.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



/*
texture.setRepeated(true);
sf::Sprite sprite;
sprite.setTexture(texture);
//sprite.setTextureRect(sf::IntRect(100, 100, 320, 320));       //affiche une certaine zone de la texture

sprite.setColor(sf::Color(255, 255, 255, 128));                 //couleur (actuellement transparence)
sprite.setScale(sf::Vector2f(0.5f, 0.5f));                      //taille de la texture
sprite.setPosition(sf::Vector2f(10.f, 50.f));                   //Position de la texture
sprite.setOrigin(sf::Vector2f(25.f, 25.f));                     //change le point d'origine de la texture
*/


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
                        RenderWindow Play(VideoMode(960, 960), "Pokemon");
                        window.close();
                       

                        while (Play.isOpen())
                        {
                            Playground pg;
                            pg.load();
                            Play.setFramerateLimit(60);

                            Battle btl;
                            btl.load();


                            Perso poke("texture/trainer.png", 6, 16);
                            Trainer trainer("texture/jotaro.png", 55, 15);
                            battleSprites btlSpr("texture/pikachu.png", 20, 5, "texture/evoli.png", 5, 18);
                            sf::Sprite perso_sprite = poke.sprite();
                            sf::Sprite trainer_sprite = trainer.sprite();
                            sf::Sprite pikachu = btlSpr.pikachu();
                            sf::Sprite evoli = btlSpr.evoli();

                            sf::Clock clock;

                            sf::View view(sf::FloatRect(300.f, 300.f, 352.f, 352.f));
                            sf::View view2(sf::FloatRect(0.f, 0.f, 960.f, 960.f));

                            while (Play.isOpen())
                            {



                                if (battle == false) {
                                    sf::Event event;
                                    while (Play.pollEvent(event))
                                    {

                                        switch (event.type)
                                        {
                                        case sf::Event::Closed:
                                            Play.close();
                                            break;

                                        case sf::Event::KeyPressed:
                                            clock.restart();

                                            poke.move();
                                            break;

                                        default:
                                            poke.pause(poke.last);
                                            break;

                                        }
                                    }



                                    if ((poke.GetX() > 1920 - 6 * SIZE_TILE))
                                        view.setCenter(1920 - 6 * SIZE_TILE + SIZE_TILE / 2, poke.GetY() + SIZE_TILE / 2);
                                    else if ((poke.GetX() < 0 + 6 * SIZE_TILE))
                                        view.setCenter(0 + 6 * SIZE_TILE - SIZE_TILE / 2, poke.GetY() + SIZE_TILE / 2);
                                    else if ((poke.GetY() > WINDOW_SIZE_Y - 6 * SIZE_TILE))
                                        view.setCenter(poke.GetX() + SIZE_TILE / 2, WINDOW_SIZE_Y - 6 * SIZE_TILE + SIZE_TILE / 2);
                                    else if ((poke.GetY() < 0 + 6 * SIZE_TILE))
                                        view.setCenter(poke.GetX() + SIZE_TILE / 2, 0 + 6 * SIZE_TILE - SIZE_TILE / 2);
                                    else
                                        view.setCenter(poke.GetX() + SIZE_TILE / 2, poke.GetY() + SIZE_TILE / 2);


                                    Play.setView(view);


                                    Play.clear();

                                    Play.draw(pg.GetSprite());
                                    if (Interaction(poke, trainer, 2))
                                    {
                                        battle = true;
                                        btl.reload();
                                        Play.setView(view2);
                                    }



                                    Play.draw(trainer_sprite);
                                    Play.draw(poke.sprite());

                                    Play.display();
                                }



                                else {
                                    sf::Event event;
                                    while (Play.pollEvent(event))
                                    {

                                        switch (event.type)
                                        {
                                        case sf::Event::Closed:
                                            Play.close();
                                            break;

                                        case sf::Event::KeyPressed:
                                            if (event.key.code == Keyboard::Up)
                                            {
                                                btl.MoveUp();
                                                break;
                                            }

                                            if (event.key.code == Keyboard::Down)
                                            {
                                                btl.MoveDown();
                                                break;
                                            }
                                            if (event.key.code == Keyboard::F)
                                            {
                                                battle = false;
                                            }
                                            if (event.key.code == Keyboard::Return)
                                            {
                                                int x = btl.AttackPressed();
                                                btl.evoliAttack(x);
                                                btl.pikachuAttack();
                                                if (btl.GetpikachuLife() < 1) {
                                                    std::cout << "You Win" << std::endl;
                                                    battle = false;
                                                }
                                                else if (btl.GetevoliLife() < 1) {
                                                    std::cout << "You Lose" << std::endl;
                                                    battle = false;
                                                }
                                            }
                                            break;

                                        default:
                                            break;

                                        }
                                    }
                                    Play.clear();
                                    Play.draw(btl.GetSprite());
                                    btl.draw(Play);
                                    Play.draw(pikachu);
                                    Play.draw(evoli);
                                    Play.display();
                                }

                            }


                        }
                    }

                    if (x == 1)
                    {
                        //RenderWindow Options(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Options");
                        //while (Options.isOpen())
                        //{
                        //    Event event;
                        //    while (Options.pollEvent(event))
                        //    {
                        //        Event event;
                        //        switch (event.type) {
                        //        case Event::Closed :                                    
                        //                Options.close();  
                        //                break;
                        //        case Event::KeyPressed :
                        //                if (event.key.code == Keyboard::Escape) {
                        //                    Options.close();
                        //                }
                        //        default :
                        //            break;
                        //        }
                        //        //Play.close();
                        //        Options.clear();
                        //        Options.display();
                        //    }
                        //}

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