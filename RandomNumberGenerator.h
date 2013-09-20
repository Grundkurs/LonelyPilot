#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H
#include <SFML/Graphics.hpp>


#include <chrono>
class RandomNumberGenerator
{
public:
    RandomNumberGenerator();
    ~RandomNumberGenerator();
    int getRandomInt(int to);
    sf::Vector2f getRandomVec2f(int to);
};

#endif // RANDOMNUMBERGENERATOR_H
