#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_


#include <SFML/Graphics.hpp>
#include <list>

#include "Entity.h"
#include "Transition.h"

class State;


class StateManager : public Entity
{
    public:
		StateManager();
		~StateManager();

        void init(State * s);
        void close() { m_isRunning = false; }
        bool isRunning() const { return m_isRunning && (!m_states.empty() || m_isClearWait ); }

        virtual void update();
        void handleEvent(sf::Event &e);

        void newState(State * s);
        void pushState(State * s);
        void popState();

    protected:
        //! Inherited from sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
		bool m_isRunning;

        std::list<State *> m_states;
		std::list<State *> m_waitingStates;
		bool m_isClearWait;
		bool m_isCloseWait;

		Transition * m_currentTransitionIn;
		Transition * m_currentTransitionOut;
};


#endif // _STATE_MANAGER_H_

