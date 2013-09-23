#ifndef IENTITY_H
#define IENTITY_H
#include "SFML/Graphics.hpp"

class Game;
class IEntity
{
protected:
	//TODO: move into derived classes. Interface should not own data-members.
public:
	virtual ~IEntity();
	virtual void Update(const sf::Time& deltaFrame) = 0;
	virtual void SetTexture(const sf::Texture& tex) = 0;
	virtual const sf::Sprite& GetSprite() const = 0;


};

#endif //IENTITY_H

