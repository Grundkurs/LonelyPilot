#ifndef LASER_H
#define LASER_H
#include "IEntity.h"



class Laser : public IEntity
{
public:
    Laser();
        void                        Update(const sf::Time& deltaFrame);
        void                        SetTexture(const sf::Texture& tex);
  const sf::Sprite&                 GetSprite() const;



private:

        sf::Sprite                  mSprite;


};

#endif // LASER_H
