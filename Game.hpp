#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

class Game
{
public:
    void Draw(sf::RenderTarget& window);
    void Update(sf::RenderWindow& window, float& deltaTime);

private:
    void m_UpdateMousePosition(sf::RenderWindow& window) 
    {
        m_mousePos = sf::Mouse::getPosition(window);
        m_mousePosView = window.mapPixelToCoords(m_mousePos);
    };

    bool m_CheckBoxAvailability();
    char m_CheckWinner();

private:
    sf::RenderWindow* m_window;
    sf::Texture m_texture;
    
    sf::RectangleShape m_board;
    sf::RectangleShape m_playerTurnSignX;
    sf::RectangleShape m_playerTurnSignO;

    float m_totalTime;

    std::vector<sf::RectangleShape> m_boxes;
    sf::RectangleShape m_emptybox;

    bool m_isXturn;

    sf::Vector2i m_mousePos;
    sf::Vector2f m_mousePosView;
    bool m_mouseHold;

public:
    Game();
    ~Game(){};
};
