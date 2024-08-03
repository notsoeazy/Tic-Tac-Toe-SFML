#include "Game.hpp"

Game::Game()
{
    m_texture.loadFromFile("res/Tic-Tac-Toe assets.png");

//INITIALIZE THE BOARD
    m_board.setSize({441.f, 784.f});
    m_board.setTexture(&m_texture);
    m_board.setTextureRect({125, 3, 64, 115});

    //191, 81, 27, 6
    m_playerTurnSignX.setSize({203, 49});
    m_playerTurnSignX.setPosition({15.f, 176.f});
    m_playerTurnSignX.setTexture(&m_texture);
    m_playerTurnSignX.setTextureRect({191, 81, 28, 7});
    m_playerTurnSignX.setFillColor(sf::Color(255, 255, 255, 255));

    //191, 88, 27, 6
    m_playerTurnSignO.setSize({203, 49});
    m_playerTurnSignO.setPosition({220.f, 176.f});
    m_playerTurnSignO.setTexture(&m_texture);
    m_playerTurnSignO.setTextureRect({191, 88, 28, 7});
    m_playerTurnSignO.setFillColor(sf::Color(255, 255, 255, 64));

    m_emptybox.setTexture(&m_texture);
    m_emptybox.setTextureRect({229, 96, 17, 17}); //blank space next to O
    m_emptybox.setSize({119.f, 119.f});

    //this one initializes the boxes vector in the board 
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //130
            m_emptybox.setPosition({30.f + (j * 130), 240.f + (i * 130)});
            m_boxes.push_back(m_emptybox);
        }
    }

    m_playerXHealth = 3;
    m_playerOHealth = 3;

    m_totalTime = 0.f;
    m_isXturn = true;
    m_mouseHold = false;
};

void Game::Update(sf::RenderWindow& window, float& deltaTime)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_UpdateMousePosition(window);
        if (m_mouseHold == false && m_CheckBoxAvailability())
        {
            m_mouseHold = true;
            
            //check individual boxes for click
            for (int i = 0; i < m_boxes.size(); i++)
            {
                if (m_boxes[i].getGlobalBounds().contains(m_mousePosView))
                {
                    m_isXturn ? m_boxes[i].setTextureRect({191, 96, 17, 17}) : m_boxes[i].setTextureRect({210, 96, 17, 17});
                }
            }

            //Turn display
            if (m_isXturn)
            {
                m_isXturn = false;
                m_playerTurnSignO.setFillColor(sf::Color(255, 255, 255, 255));
                m_playerTurnSignX.setFillColor(sf::Color(255, 255, 255, 64));
            }
            else
            {
                m_isXturn = true;
                m_playerTurnSignX.setFillColor(sf::Color(255, 255, 255, 255));
                m_playerTurnSignO.setFillColor(sf::Color(255, 255, 255, 64));
            }

            switch (m_CheckWinner())
            {
            case ' ':
                break;
            case 'X':
                std::cout << "Player X wins this round!" << std::endl;
                m_playerOHealth--;
                m_ResetBoard();
                break;
            case 'O':
                std::cout << "Player O wins this round!" << std::endl;
                m_playerXHealth--;
                m_ResetBoard();
                break;
            }

            m_CheckTie();
        }
    }
    else
        m_mouseHold = false;
    

};

void Game::Draw(sf::RenderTarget& window)
{
    window.draw(m_board);
    window.draw(m_playerTurnSignX);
    window.draw(m_playerTurnSignO);

    for (int i = 0; i < 9; i++)
    {
        window.draw(m_boxes[i]);
    }    
};

bool Game::m_CheckBoxAvailability()
{
    for (int i = 0; i < m_boxes.size(); i++)
    {
        if (m_boxes[i].getGlobalBounds().contains(m_mousePosView) && m_boxes[i].getTextureRect() == m_emptybox.getTextureRect())
        {
            return true;
        }
    }
    return false;
}

char Game::m_CheckWinner()
{
    //Horizontal
    if (m_boxes[0].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[0].getTextureRect() == m_boxes[1].getTextureRect() && m_boxes[1].getTextureRect() == m_boxes[2].getTextureRect())
    {
        if (m_boxes[0].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }
    if (m_boxes[3].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[3].getTextureRect() == m_boxes[4].getTextureRect() && m_boxes[4].getTextureRect() == m_boxes[5].getTextureRect())
    {
        if (m_boxes[3].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }
    if (m_boxes[6].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[6].getTextureRect() == m_boxes[7].getTextureRect() && m_boxes[7].getTextureRect() == m_boxes[8].getTextureRect())
    {
        if (m_boxes[6].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }

    //Vertical
    if (m_boxes[0].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[0].getTextureRect() == m_boxes[3].getTextureRect() && m_boxes[3].getTextureRect() == m_boxes[6].getTextureRect())
    {
        if (m_boxes[0].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }
    if (m_boxes[1].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[1].getTextureRect() == m_boxes[4].getTextureRect() && m_boxes[4].getTextureRect() == m_boxes[7].getTextureRect())
    {
        if (m_boxes[1].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }
    if (m_boxes[2].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[2].getTextureRect() == m_boxes[5].getTextureRect() && m_boxes[5].getTextureRect() == m_boxes[8].getTextureRect())
    {
        if (m_boxes[2].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }

    //Diagonal
    if (m_boxes[0].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[0].getTextureRect() == m_boxes[4].getTextureRect() && m_boxes[4].getTextureRect() == m_boxes[8].getTextureRect())
    {
        if (m_boxes[0].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }
    if (m_boxes[2].getTextureRect() != m_emptybox.getTextureRect() && m_boxes[2].getTextureRect() == m_boxes[4].getTextureRect() && m_boxes[4].getTextureRect() == m_boxes[6].getTextureRect())
    {
        if (m_boxes[2].getTextureRect() == sf::IntRect{191, 96, 17, 17})
            return 'X';
        else
            return 'O';
    }

    return ' ';
}

bool Game::m_CheckTie()
{
    for (int i = 0; i < m_boxes.size(); i++)
    {
        if (m_boxes[i].getTextureRect() == m_emptybox.getTextureRect())
            return false;
    }
    m_ResetBoard();
    std::cout << m_isXturn;
    return true;
}

void Game::m_ResetBoard()
{
    m_isXturn = true;
    
    for (int i = 0; i < m_boxes.size(); i++)
    {
        m_boxes[i].setTextureRect({229, 96, 17, 17});
    }
}