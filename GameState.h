#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "IState.h"
#include "Game.h"
#include "IEntity.h"
#include "Star.h"
#include "RandomNumberGenerator.h"
#include <memory>
#include "Player.h"
#include "Background.h"


class Game; 

typedef std::shared_ptr<IEntity> sptr_entity;

class GameState : public IState
{
	Game* _game; 
	
    std::vector<sptr_entity> entities;
	std::shared_ptr<Player> mPlayer; 
	std::unique_ptr<Background> mBackground; 
public:
	GameState(Game* game);
	~GameState();

	
	 IState* ProcessStateInput(const sf::Event& event);
	 void Update(const sf::Time& deltaFrame); 
	 void Render(); 
};


#endif //GAMESTATE_H
