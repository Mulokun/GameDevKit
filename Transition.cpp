#include "Transition.h"

#include <fstream>

#include "Log.h"
#include "Misc.h"
#include "State.h"
#include "GameManager.h"
#include "GameTime.h"

Transition::Transition( const std::string &path ) : m_isStarted(false), m_isEnded(false)
{
	std::ifstream file;
	file.open( path.c_str() );

	if( !file.is_open() )
	{
		log(LOG_ERROR) << "TRANSITION - Can't open file : " << path << std::endl;
	}

	std::string buffer = "";

	while( !file.eof() )
	{
		if( buffer == "[KEY]" )
		{
			TransitionState state;
			unsigned int time;
			file >> time;
			state.time = sf::milliseconds( time );
			unsigned int r, g, b, a;

			file >> state.position.x >> state.position.y >> r >> g >> b >> a;
			state.position.x *= GameManager::getSingleton()->getScreenInitSize().x;
			state.position.y *= GameManager::getSingleton()->getScreenInitSize().y;
			state.color.r = r;
			state.color.g = g;
			state.color.b = b;
			state.color.a = a;

			//log( LOG_DEBUG ) << int(state.color.r) << " : " << int( state.color.g) << " : " << int( state.color.b) << " : " << int( state.color.a) << std::endl;

			m_states.push_back( state );
		}

		file >> buffer;
	}

	file.close();
}

Transition::~Transition()
{

}

void Transition::draw( State * s, sf::RenderTarget& target, sf::RenderStates states ) const
{
	std::vector< TransitionState >::const_iterator it;
	TransitionState pred;
	for( it = m_states.begin(); it != m_states.end(); ++it )
	{
		if( m_timer < it->time )
		{
			float prct = 0;
			if( ( ( *it ).time - pred.time ) != sf::Time::Zero)
			{
				prct = ( m_timer - pred.time ) / ( ( *it ).time - pred.time );
			}

			states.transform.translate( lerp( pred.position, ( *it ).position, prct ) );
			target.draw( *s, states );

			sf::RectangleShape rect( sf::Vector2f( GameManager::getSingleton()->getScreenSize() ) );
			rect.setFillColor( lerp( pred.color, ( *it ).color, prct ) );
			target.draw( rect, states );

			break;
		}
		pred = *it;
	}
}

void Transition::update()
{
	if( m_isStarted && !m_isEnded)
	{
		m_timer += GameTime::frame;

		if( m_states.back().time < m_timer )
		{
			m_isEnded = true;
		}
	}
}