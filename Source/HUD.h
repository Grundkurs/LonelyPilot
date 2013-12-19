#ifndef HUD_H
#define HUD_H
#include <SFML\Graphics.hpp>
class Game; 

class HUD
{
	sf::Sprite			mHealthBarSprite; 
	sf::Sprite			mPlayerLifeIconsSprite; 
	sf::IntRect			mHealthBarRect; 
public:
	HUD(Game* mpGame);
	~HUD();

	Game*				mpGame; 
	void				Update(const sf::Time& deltaFrame );
	void				Draw(sf::RenderWindow& renderWindow);
};

#endif //HUD_H