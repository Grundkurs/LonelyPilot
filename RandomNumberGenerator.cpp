#include "RandomNumberGenerator.h"


RandomNumberGenerator::RandomNumberGenerator()
	{
	 //initialize seed
    auto currTime = std::chrono::high_resolution_clock::now();
    int currTimeInt = std::chrono::duration_cast<std::chrono::milliseconds>( currTime.time_since_epoch() ).count();
    srand( currTimeInt );
	}


RandomNumberGenerator::~RandomNumberGenerator()
	{
	}

int	RandomNumberGenerator::getRandomInt(int to)
	{
    int randomNumber = rand() % to;
    return randomNumber;
	}


sf::Vector2f RandomNumberGenerator::getRandomVec2f( int to )
	{
    float x = rand() % to;
    float y = rand()%to;
    return sf::Vector2f( x,y );
	}
