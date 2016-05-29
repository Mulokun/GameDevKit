#ifndef _GAMETIME_H_
#define _GAMETIME_H_


#include "SFML/Graphics.hpp"


class GameTime
{

    private :
        static sf::Time m_lastTime;

    public :
        static sf::Clock m_elapsed;
        static void wait( sf::Time timeWait );

        static sf::Time frame;
        static void update( void );

        static unsigned int framerate;

		static float deltaTime( void )
		{
			return static_cast<float>( frame.asMilliseconds() ) / ( 1000.0f / static_cast<float>( framerate ) );
		}

		static float getCurrentFPS( void )
		{
			return 1000.0f / static_cast<float>( frame.asMilliseconds() );
		}
};

#endif // _GAMETIME_H_
