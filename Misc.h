#ifndef _MISC_H_
#define _MISC_H_


#include <string>
#include <SFML/Graphics.hpp>


std::string itos( int i );
std::string ftos( float f, int precision = -1 );


/// "MATH"

typedef enum RelativePosition {
    POS_TOP = 1,
    POS_BOTTOM = 2,
    POS_MIDDLE = 4,
    POS_LEFT = 8,
    POS_RIGHT = 16,
    POS_CENTER = 32,
    POS_NONE = 0
} RelativePosition;


enum Direction {
    DIR_UP = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 4,
    DIR_RIGHT = 8,
    DIR_NONE = 0
};


sf::Vector2f getAbsolutePosition( sf::FloatRect r, sf::FloatRect c, RelativePosition p );
bool inRectangle( sf::FloatRect r, const sf::Vector2i & p );

sf::Vector2f normalize( sf::Vector2f v );
sf::Vector2f direction( sf::Vector2f vFrom, sf::Vector2f vTo );
float distanceEuclidienne( sf::Vector2f p1, sf::Vector2f p2 );
float distanceEuclidienne( sf::Vector2i p1, sf::Vector2i p2 );
unsigned int distanceManhattan( sf::Vector2i p1, sf::Vector2i p2 );

float lerp( float f1, float f2, float t );
sf::Vector2f lerp( sf::Vector2f v1, sf::Vector2f v2, float t );
sf::Color lerp( sf::Color c1, sf::Color c2, float t );


#endif // _MISC_H_

