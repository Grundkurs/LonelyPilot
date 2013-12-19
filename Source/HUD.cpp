#include "HUD.h"
#include "Game.h"

HUD::HUD(Game* mpGame)
{
	mHealthBarSprite.setTexture(mpGame->mHealthBarTexture);
	mHealthBarRect = static_cast<sf::IntRect>(mHealthBarSprite.getGlobalBounds()); 
	sf::Vector2f pos(mpGame->ScreenWidth - mHealthBarSprite.getGlobalBounds().width, 
					mpGame->ScreenHeight - mHealthBarSprite.getGlobalBounds().height);
	mHealthBarSprite.setPosition(pos); 
	mHealthBarRect.width = 40; 
	mHealthBarSprite.setTextureRect(mHealthBarRect);
}


HUD::~HUD()
{
}


void HUD::Update(const sf::Time& deltaFrame){}
void HUD::Draw(sf::RenderWindow& renderWindow)
	{
	renderWindow.draw(mHealthBarSprite); 
	}