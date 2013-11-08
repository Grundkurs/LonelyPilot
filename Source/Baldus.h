#ifndef BALDUS_H
#define BALDUS_H
#include "Enemy.h"
#include "VectorUtilities.h"
class Game;
class Player;



class Baldus : public Enemy
{
 public:
                                    Baldus(Game * pGame, Player * pPlayer);
                                    ~Baldus();
		bool						isAlive();
		bool						shutDown();
		void						Update(const sf::Time& deltaFrame);
		void						SetTexture(const sf::Texture& tex);
		void						Animation(const sf::Time& deltaFrame);
		void						Movement(const sf::Time& deltaFrame);
		void						HitPoint(int damageRate);
const	sf::Sprite&					GetSprite() const;

};

#endif // BALDUS_H
