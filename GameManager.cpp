#include "GameManager.h"


GameManager * GameManager::s_singleton = nullptr;


GameManager::GameManager()
{
	p_screen = nullptr;
	p_resourcesManager = nullptr;
	p_stateManager = nullptr;

	init();
}

GameManager::~GameManager()
{
	clear();
}

GameManager * GameManager::getSingleton()
{
	if( !s_singleton )
	{
		s_singleton = new GameManager();
	}

	return s_singleton;
}

void GameManager::killSingleton()
{
	if( s_singleton )
	{
		delete s_singleton;
	}

	s_singleton = nullptr;
}


void GameManager::clear()
{
	if( p_screen )
	{
		delete p_screen;
	}
	p_screen = nullptr;

	if( p_resourcesManager )
	{
		delete p_resourcesManager;
	}
	p_resourcesManager = nullptr;

	if( p_stateManager )
	{
		delete p_stateManager;
	}
	p_stateManager = nullptr;
}

void GameManager::init()
{
	clear();

	setScreenSize( 800, 600 );
	setScreenRatio( sf::Vector2u( 0, 0 ) );
	setScreenTitle( "No Title" );

	m_isUpdated = true;
	m_isScissored = false;

	p_resourcesManager = new ResourcesManager();
	p_stateManager = new StateManager();

	update();
}

void GameManager::run()
{
	while( p_stateManager->isRunning() && p_screen->isOpen() )
	{
		sf::Event event;
		while( p_screen->pollEvent( event ) )
		{
			handleEvent( event );
			p_stateManager->handleEvent( event );
		}

		update();
		p_stateManager->update();

		p_screen->clear( sf::Color::Black );
		p_screen->draw( *p_stateManager );
		p_screen->display();
	}
}

void GameManager::update( void )
{
	if( m_isUpdated )
	{
		if( !p_screen )
		{
			p_screen = new sf::RenderWindow( sf::VideoMode( m_screenSize.x, m_screenSize.y ), m_screenTitle );
			m_screenInitSize = m_screenSize;
		}
		p_screen->setTitle( m_screenTitle );
		p_screen->setSize( m_screenSize );

		m_isUpdated = false;
	}
}

void GameManager::handleEvent( sf::Event &e )
{
	if( e.type == sf::Event::Closed )
	{
		p_screen->close();
	}
	else if( e.type == sf::Event::Resized )
	{
		if( m_screenRatio.x > 0 && m_screenRatio.y > 0 )
		{
			int isWidthBigger = std::abs( static_cast<int>( m_screenSize.x - p_screen->getSize().x ) ) > std::abs( static_cast<int>( m_screenSize.y - p_screen->getSize().y ) );
			if( isWidthBigger )
			{
				setScreenSize( p_screen->getSize().x, p_screen->getSize().x * m_screenRatio.y / m_screenRatio.x );
			}
			else
			{
				setScreenSize( p_screen->getSize().y * m_screenRatio.x / m_screenRatio.y, p_screen->getSize().y );
			}
		}
		else
		{
			setScreenSize( p_screen->getSize() );
		}
	}
}


void GameManager::setViewport( sf::FloatRect zone, sf::RenderStates states )
{
	sf::View v;
	zone = states.transform.transformRect( zone );
	v.reset( zone );
	sf::FloatRect r( zone.left / m_screenInitSize.x, zone.top / m_screenInitSize.y, zone.width / m_screenInitSize.x, zone.height / m_screenInitSize.y );
	v.setViewport( r );
	p_screen->setView( v );
	m_isScissored = true;
}

void GameManager::setDefaultViewport()
{
	p_screen->setView( p_screen->getDefaultView() );
	m_isScissored = false;
}

sf::FloatRect GameManager::getCurrentViewport()
{
	sf::View v = p_screen->getView();
	sf::FloatRect r = v.getViewport();
	return sf::FloatRect( r.left * m_screenInitSize.x, r.top * m_screenInitSize.y, r.width * m_screenInitSize.x, r.height * m_screenInitSize.y );
}



sf::Vector2f GameManager::getMouseCoord()
{
	return getScreen()->mapPixelToCoords( sf::Mouse::getPosition( *getScreen() ) );
}

sf::Vector2f GameManager::getCoord( float x, float y )
{
	return getCoord( sf::Vector2i( (int)x, (int)y ) );
}

sf::Vector2f GameManager::getCoord( int x, int y )
{
	return getCoord( sf::Vector2i( x, y ) );
}

sf::Vector2f GameManager::getCoord( sf::Vector2f p )
{
	return getCoord( sf::Vector2i( p ) );
}

sf::Vector2f GameManager::getCoord( sf::Vector2i p )
{
	return getScreen()->mapPixelToCoords( p );
}
