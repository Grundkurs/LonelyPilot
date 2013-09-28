#ifndef VECTORUTILITIES_H
#define VECTORUTILITIES_H

#include "SFML/Graphics.hpp"


inline float Dot( sf::Vector2f & vec1, sf::Vector2f & vec2 )
	{
	return vec1.x * vec2.x + vec1.y * vec2.y;
	}

inline sf::Vector2f & Normalize( sf::Vector2f & vec )
	{
	float length = sqrt(Dot(vec,vec) );
	if ( length == 0.0f )
		{
		vec.x = 0.0f;
		vec.y = 0.0f;
		return vec;
		}
	vec /= length;
	return vec;
	}

inline sf::Vector2f Inertia( const sf::Vector2f & velocity, const float slowRate, const float frameDelta )
	{
	// NOTE: you could make seperate slow down rates for x and y
	sf::Vector2f oppositeDir( -velocity );
	Normalize(oppositeDir);

	oppositeDir *= (slowRate * frameDelta);

	if ( abs( velocity.x ) <= abs(oppositeDir.x ) )
		{
		oppositeDir.x = velocity.x;
		}
	if ( abs( velocity.y ) <= abs(oppositeDir.y ) )
		{
		oppositeDir.y = velocity.y;
		}
	return oppositeDir;
	}

#endif // VECTORUTILITIES_H
