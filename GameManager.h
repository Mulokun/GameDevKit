#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_


#include <SFML/Graphics.hpp>


class GameManager
{
public :
	static GameManager * getSingleton();
	static void killSingleton();

	void clear();
	void init();
	void run();
	void update( void );
	void handleEvent( sf::Event &e );
	
	sf::RenderWindow * getScreen( void ) const { return p_screen; }
	void setScreenSize( unsigned int w, unsigned int h ) { setScreenSize( sf::Vector2u(w, h) ); }
	void setScreenSize( sf::Vector2u size ) { m_screenSize = size; m_isUpdated = true; }
	void setScreenRatio( sf::Vector2u ratio ) { m_screenRatio = ratio; m_isUpdated = true; }
	sf::Vector2u getScreenSize() { return m_screenSize; }
	sf::Vector2u getScreenIniSize() { return m_screenInitSize; }
	sf::Vector2u getScreenRatio() { return m_screenRatio; }
	sf::Vector2f getScreenCurrentRatio() { return sf::Vector2f( float(m_screenSize.x / m_screenInitSize.x), float(m_screenSize.y / m_screenInitSize.y) ); }
	void setScreenTitle( std::string title ) { m_screenTitle = title; m_isUpdated = true; }
	std::string getScreenTitle() { return m_screenTitle; }

	void setViewport( sf::FloatRect zone, sf::RenderStates states );
	void setDefaultViewport();
	sf::FloatRect getCurrentViewport();
	bool isScissored() { return m_isScissored; }


	sf::Vector2f getMouseCoord();
	sf::Vector2f getCoord( float x, float y );
	sf::Vector2f getCoord( int x, int y );
	sf::Vector2f getCoord( sf::Vector2f p );
	sf::Vector2f getCoord( sf::Vector2i p );

private :
	GameManager();
	~GameManager();

	static GameManager * s_singleton;

	bool m_isRunning;

	sf::RenderWindow * p_screen;
	sf::Vector2u m_screenSize;
	sf::Vector2u m_screenRatio;
	sf::Vector2u m_screenInitSize;
	std::string m_screenTitle;
	bool m_isUpdated;
	bool m_isScissored;

};

#endif