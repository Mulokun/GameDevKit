#ifndef _TRANSITION_
#define _TRANSITION_


#include <SFML/Graphics.hpp>


class State;


typedef struct TransitionState
{
	sf::Time time = sf::Time::Zero;
	sf::Vector2f position = sf::Vector2f(0, 0);
	//sf::Vector2f scale = sf::Vector2f( 0, 0 );
	//sf::Vector2f rotation = sf::Vector2f( 0, 0 );
	sf::Color color = sf::Color::Transparent;
} TransitionState;


class Transition
{
public :
	Transition( const std::string &path );
	~Transition();

	void start() { m_isStarted = true; }
	bool isStarted() { return m_isStarted; }
	bool isEnded() { return m_isEnded; }

	virtual void draw( State * s, sf::RenderTarget& target, sf::RenderStates states ) const;
	virtual void update();

private:
	bool m_isStarted;
	bool m_isEnded;

	sf::Time m_timer;
	std::vector< TransitionState > m_states;
};

#endif // _TRANSITION_
