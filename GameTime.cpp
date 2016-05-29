#include "GameTime.h"


#include "SFML/Graphics.hpp"


sf::Clock GameTime::m_elapsed;

void GameTime::wait( sf::Time timeWait )
{
    sf::sleep(timeWait);
}


sf::Time GameTime::m_lastTime = sf::Time::Zero;
sf::Time GameTime::frame = sf::Time::Zero;

unsigned int GameTime::framerate = 60;

void GameTime::update( void )
{
    GameTime::frame = GameTime::m_elapsed.getElapsedTime() - GameTime::m_lastTime;
    GameTime::m_lastTime = GameTime::m_elapsed.getElapsedTime();
}

