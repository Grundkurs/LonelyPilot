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
#include "Ambulance.h"


class Game;

typedef std::shared_ptr<IEntity> sptr_entity;

class GameState : public IState
{
	Game * mpGame;

	std::vector<sptr_entity> entities;
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Ambulance> mAmbulance;
	std::unique_ptr<Background> mBackground;
public:
	GameState(Game * pGame);
	~GameState();


	 IState* ProcessStateInput(const sf::Event& event);
	 void Update(const sf::Time& deltaFrame);
	 void Render();
};


#endif //GAMESTATE_H
