#ifndef VECTORUTILITIES_H
#define VECTORUTILITIES_H

#include "SFML/Graphics.hpp"


float Dot( sf::Vector2f & vec1, sf::Vector2f & vec2 )
	{
	return vec1.x * vec2.x + vec1.y * vec2.y;
	}

sf::Vector2f & Normalize( sf::Vector2f & vec )
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

#endif // VECTORUTILITIES_H
