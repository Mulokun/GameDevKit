#include "StateManager.h"


#include "Log.h"
#include "State.h"
#include "GameTime.h"

// CONSTRUCTOR / DESTRUCTOR

StateManager::StateManager() : m_isClearWait( false ), m_isCloseWait( false ), m_isRunning( false )
{
	m_currentTransitionIn = NULL;
	m_currentTransitionOut = NULL;
}

StateManager::~StateManager()
{
	for( std::list<State *>::iterator it = m_states.begin(); it != m_states.end(); ++it )
	{
		delete ( *it );
	}

	for( std::list<State *>::iterator it = m_waitingStates.begin(); it != m_waitingStates.end(); ++it )
	{
		delete ( *it );
	}

	m_states.clear();
}

// ***

void StateManager::init(State * s)
{
    newState(s);
	m_isRunning = true;
}

void StateManager::update()
{
	GameTime::update();

	if( m_currentTransitionIn )
	{
		m_currentTransitionIn->update();
	}
	if( m_currentTransitionOut )
	{
		m_currentTransitionOut->update();
	}

	if( m_isCloseWait && (!m_currentTransitionOut || m_currentTransitionOut->isEnded() ) )
	{
		m_isCloseWait = false;
		m_currentTransitionOut = NULL;
		if( !m_states.empty() )
		{
			m_states.back()->close();
		}
		if( m_currentTransitionIn )
		{
			m_currentTransitionIn->start();
		}
	}

    if(!m_isCloseWait && !m_waitingStates.empty() && (!m_currentTransitionIn || m_currentTransitionIn->isEnded()) )
    {
        if( m_isClearWait )
        {
            for(std::list<State *>::iterator it = m_states.begin(); it != m_states.end(); ++it)
            {
                (*it)->close();
            }
			m_isClearWait = false;
        }

        m_states.push_back(m_waitingStates.front());
		m_waitingStates.pop_front();
		m_currentTransitionIn = NULL;
		if( !m_waitingStates.empty() )
		{
			m_currentTransitionIn = m_waitingStates.front()->getTransitionIn();
			if( m_currentTransitionIn )
			{
				m_currentTransitionIn->start();
			}
		}
    }

	// Remove all closed/ended states
	for (std::list<State *>::iterator it = m_states.begin(); it != m_states.end(); ++it)
	{
		if ((*it)->isEnded())
		{
			State * s = (*it);
			m_states.erase(it);
			s->clear();
			delete s;
			it = m_states.begin();
			if (it == m_states.end())
			{
				break;
			}
		}
	}


	// --- Always focus the last added state ---
	for( std::list<State *>::iterator it = m_states.begin(); it != m_states.end(); ++it )
	{
		( *it )->focus( false );
	}

	if( !m_states.empty() )
	{
		m_states.back()->focus( true );
	}
	// ---

    for(std::list<State *>::iterator it = m_states.begin(); it != m_states.end(); ++it)
    {
        if((*it)->isRunning())
        {
            (*it)->update();
        }
    }
}

void StateManager::handleEvent(sf::Event &e)
{
	if( !(m_currentTransitionIn && m_currentTransitionIn->isStarted() && !m_currentTransitionIn->isEnded() ) && 
		!(m_currentTransitionOut && m_currentTransitionOut->isStarted() && !m_currentTransitionOut->isEnded()) )
	{
		if( !m_states.empty() && m_states.back()->isRunning() )
		{
			m_states.back()->handleEvent( e );
		}
	}
}

void StateManager::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	if( m_currentTransitionOut && m_currentTransitionOut->isStarted() && !m_currentTransitionOut->isEnded() )
	{
		for( std::list<State *>::const_iterator it = m_states.begin(); it != m_states.end(); ++it )
		{
			if( ( *it )->isVisible() && (*it) != m_states.back())
			{
				target.draw( *( *it ) );
			}
		}

		m_currentTransitionOut->draw( m_states.back(), target, states );
	}
	else
	{
		for( std::list<State *>::const_iterator it = m_states.begin(); it != m_states.end(); ++it )
		{
			if( ( *it )->isVisible() )
			{
				target.draw( *( *it ) );
			}
		}
	}

	if( m_currentTransitionIn && m_currentTransitionIn->isStarted() && !m_currentTransitionIn->isEnded() )
	{
		m_currentTransitionIn->draw( m_waitingStates.front(), target, states );
	}
}

void StateManager::newState(State * s)
{
	for( std::list<State *>::iterator it = m_waitingStates.begin(); it != m_waitingStates.end(); ++it )
	{
		delete (*it);
	}
	m_waitingStates.clear();

    m_waitingStates.push_back(s);
	s->init();
	m_isClearWait = true;

	m_currentTransitionIn = m_waitingStates.front()->getTransitionIn();
	if( !m_states.empty() )
	{
		m_isCloseWait = true;
		m_currentTransitionOut = m_states.front()->getTransitionOut();
		if( m_currentTransitionOut )
		{
			m_currentTransitionOut->start();
		}
	}

	if( !m_currentTransitionOut && m_currentTransitionIn )
	{
		m_currentTransitionIn->start();
	}
}

void StateManager::pushState(State * s)
{
    m_waitingStates.push_back(s);
	s->init();
	if( m_waitingStates.size() <= 1 ) // Il y a que l'etat qu'on  vient d'ajouter
	{
		m_currentTransitionIn = s->getTransitionIn();
		if( m_currentTransitionIn )
		{
			m_currentTransitionIn->start();
		}
	}
}

void StateManager::popState( )
{
	if(!m_states.empty())
	{
		m_isCloseWait = true;
		m_currentTransitionOut = m_states.back()->getTransitionOut();
		if( m_currentTransitionOut )
		{
			m_currentTransitionOut->start();
		}
	}
}



