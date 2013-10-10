#include "Laser.h"
#include "Player.h"
#include <iostream>
Laser::Laser(Player* pPlayer, bool leftSide, int damageBoost)
    :
      mPlayer(pPlayer)
    {
    sf::Vector2f defaultPos = pPlayer->GetSprite().getPosition();
    defaultPos.x += 5; //adjust laser-position a bit
    sf::IntRect rect(0, 0, 7, 48);

    if(!leftSide) //make second shot appear on right side
    {
        defaultPos.x += (pPlayer->GetSprite().getLocalBounds().width - 15);
    }
    //adjust exact position where lasershot has to appear!
    mSprite.setPosition(defaultPos);
    mSprite.setTextureRect(rect);
    }

Laser::~Laser()
    {
    std::cout << "destroying Laser!\n" ;
    }

void Laser::Update(const sf::Time& deltaFrame)
    {
    sf::Vector2f currPos = mSprite.getPosition();
    currPos.y -= 1200.f * deltaFrame.asSeconds();
    mSprite.setPosition(currPos);
    }
void Laser::SetTexture(const sf::Texture& tex)
    {
    mSprite.setTexture(tex);
    }
const sf::Sprite& Laser::GetSprite() const
    {
    return mSprite;
    }
