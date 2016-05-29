#ifndef _STATE_H_
#define _STATE_H_


#include "Entity.h"
#include "Transition.h"


class State : public Entity
{
    public:
		State() :	m_isVisible( true ),
					m_isRunning( true ),
					m_isEnded( false ),
					m_isFocused( false ),
					m_transitionIn(NULL),
					m_transitionOut(NULL)
					{}

        virtual ~State() 
		{
			if( m_transitionIn )
			{
				delete m_transitionIn;
			}
			if( m_transitionOut )
			{
				delete m_transitionOut;
			}
		}

        virtual void init() = 0;
        virtual void clear() = 0;
        virtual void update() = 0;
        virtual void handleEvent( sf::Event &e ) = 0;

        void close()			{ m_isEnded = true; }
        bool isEnded() const	{ return m_isEnded; }
        void pause()			{ m_isRunning = false; }
        void resume()			{ m_isRunning = true; }
        bool isRunning() const	{ return m_isRunning; }
        void hide()				{ m_isVisible = false; }
        void show()				{ m_isVisible = true; }
        bool isVisible() const	{ return m_isVisible; }
        void disable()			{ pause(); hide(); }
        void enable()			{ resume(); show(); }
		void focus( bool f )	{ m_isFocused = f; }
		
		Transition * getTransitionIn() { return m_transitionIn; }
		Transition * getTransitionOut() { return m_transitionOut; }
		void setTransitionIn( Transition * in )
		{
			if( m_transitionIn )
			{
				delete m_transitionIn;
			}
			m_transitionIn = in;
		}
		void setTransitionOut(Transition * out) 
		{
			if( m_transitionOut )
			{
				delete m_transitionOut;
			}
			m_transitionOut = out; 
		}

    protected:
        bool m_isVisible;
        bool m_isRunning;
        bool m_isEnded;
		bool m_isFocused;

		Transition * m_transitionIn;
		Transition * m_transitionOut;
    private:

};


#endif // _STATE_H_

