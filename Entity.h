#ifndef _ENTITY_H_
#define _ENTITY_H_


#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable
{
	public:
		virtual void update() = 0;

	protected:
		//! Inherited from sf::Drawable
		virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const = 0;

	private:
};


#endif // _ENTITY_H_
