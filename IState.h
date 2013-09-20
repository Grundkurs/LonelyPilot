#ifndef ISTATE_H
#define ISTATE_H
#include "SFML\Graphics.hpp"

class Game; 
class IState
{
protected:
	
	
public:
	
	virtual ~IState();

	virtual IState* ProcessStateInput(const sf::Event& event) = 0; 
	virtual void Update(const sf::Time& deltaFrame) = 0; 
	virtual void Render() = 0; 
};

#endif //ISTATE_H

