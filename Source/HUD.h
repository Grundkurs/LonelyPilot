#ifndef HUD_H
#define HUD_H
#include <SFML\Graphics.hpp>
class Game; 

class HUD
{
	sf::Sprite			mHealthBar; 
	sf::Sprite			mPlayerLifeIcons; 
	sf::IntRect			mLifeIconBar; 
public:
	HUD();
	~HUD();

	Game*				mpGame; 
	void				Update( const sf::Time& deltaFrame );
	void				Draw(const sf::RenderWindow& renderWindow);
};

#endif //HUD_H