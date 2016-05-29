#include "Misc.h"


#include <sstream>
#include <cmath>

#include "Log.h"


std::string itos( int n )
{
	std::ostringstream oss;
	oss << n;
	return oss.str();
}

std::string ftos( float f, int precision )
{
	std::ostringstream oss;
	oss << f;
	return oss.str();
}

//! MATH


sf::Vector2f getAbsolutePosition( sf::FloatRect r, sf::FloatRect c, RelativePosition p )
{
	sf::Vector2f v( r.left, r.top );

	switch( p )
	{
		case POS_TOP:
			v.y = c.top;
			break;

		case POS_BOTTOM:
			v.y = c.height - r.height + c.top;
			break;

		case POS_MIDDLE:
			v.y = c.height / 2 - r.height / 2 + c.top;
			break;

		case POS_LEFT:
			v.x = c.left;
			break;

		case POS_RIGHT:
			v.x = c.width - r.width + c.left;
			break;

		case POS_CENTER:
			v.x = c.width / 2 - r.width / 2 + c.left;
			break;

		default:
			break;
	}

	return v;
}

bool inRectangle( sf::FloatRect r, const sf::Vector2i & p )
{
	return ( p.y > r.top && p.y < r.top + r.height ) && ( p.x > r.left && p.x < r.left + r.width );
}


sf::Vector2f normalize( sf::Vector2f v )
{
	float n( sqrt( v.x*v.x + v.y*v.y ) );

	if( n != 0 )
	{
		v.x = v.x / n;
		v.y = v.y / n;
	}
	return v;
}

sf::Vector2f direction( sf::Vector2f vFrom, sf::Vector2f vTo )
{
	sf::Vector2f dir;
	dir.x = vTo.x - vFrom.x;
	dir.y = vTo.y - vFrom.y;

	return dir;
}

float distanceEuclidienne( sf::Vector2f p1, sf::Vector2f p2 )
{
	return (float)sqrt( ( p1.x - p2.x )*( p1.x - p2.x ) + ( p1.y - p2.y )*( p1.y - p2.y ) );
}

float distanceEuclidienne( sf::Vector2i p1, sf::Vector2i p2 )
{
	return (float)sqrt( ( p1.x - p2.x )*( p1.x - p2.x ) + ( p1.y - p2.y )*( p1.y - p2.y ) );
}

unsigned int distanceManhattan( sf::Vector2i p1, sf::Vector2i p2 )
{
	return std::abs( p1.x - p2.x ) + std::abs( p1.y - p2.y );
}

float angle( sf::Vector2f v1, sf::Vector2f v2 )
{
	sf::Vector2f z;
	z.x = 0; z.y = 0;
	float A = distanceEuclidienne( v1, v2 );
	float B = distanceEuclidienne( v1, z );
	float C = distanceEuclidienne( v2, z );

	return static_cast<float>( acos( ( -( A*A - B*B - C*C ) ) / ( 2 * B*C ) ) / 3.1415f * 180.0f );
}


float lerp( float f1, float f2, float t )
{
	return f1 + ( f2 - f1 ) * t;
}

sf::Vector2f lerp( sf::Vector2f v1, sf::Vector2f v2, float t )
{
	sf::Vector2f vx = v2 - v1;
	vx.x *= t;
	vx.y *= t;
	return v1 + vx;
}

sf::Color lerp( sf::Color c1, sf::Color c2, float t )
{
	int r, g, b, a;
	r = static_cast<int>( c1.r + ( c2.r - c1.r ) * t );
	g = static_cast<int>( c1.g + ( c2.g - c1.g ) * t );
	b = static_cast<int>( c1.b + ( c2.b - c1.b ) * t );
	a = static_cast<int>( c1.a + ( c2.a - c1.a ) * t );
	return sf::Color(r, g, b, a);
}


