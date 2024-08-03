#include "SFML/Graphics.hpp"
#include "Game.hpp"
int main()
{
    sf::RenderWindow window (sf::VideoMode(441.f, 784.f), "Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Clock clock;
    float deltaTime;

    Game game;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed :
                window.close();
                break;
            case sf::Event::KeyPressed :
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            default:
                break;
            }
        }
        game.Update(window, deltaTime);
        window.clear();


        game.Draw(window);
        window.display();
    }
}