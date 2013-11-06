#ifndef LASER_H
#define LASER_H
#include "IEntity.h"
#include "SFML/Graphics.hpp"


class Player;
enum class Weapon;
class Laser : public IEntity
{



public:
									Laser(Player* pPlayer, bool leftSide, Weapon weapon);
                                    ~Laser();
        void                        Update(const sf::Time& deltaFrame);
        void                        SetTexture(const sf::Texture& tex);
  const sf::Sprite&                 GetSprite() const;



private:
        Player*                     mPlayer;
        sf::Sprite                  mSprite;
        int                         mSpriteWidth;
        int                         mSpriteHeight;


};

#endif // LASER_H
