#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include <memory>
#include "Option.h"
class Game;
class MenuState :
	public IState
{
	Game* _game; 
	
public:
	MenuState(Game* game);
	~MenuState();


	IState* ProcessStateInput(const sf::Event& event); 
	void Update(const sf::Time& deltaFrame); 
	void Render(); 

	sf::Sprite _backgroundSprite1;
	sf::Sprite _backgroundSprite2;
	sf::Sprite _spaceShipSprite;
	sf::Sprite _starStripeSprite;
	sf::RectangleShape _rectShape; 
	float _spaceShipVelocity;
	sf::Font _font; 

	sf::Text _NewGameText; 

	std::shared_ptr<Option> sPtr_NewGame; 
	std::shared_ptr<Option> sPtr_Options; 
	std::shared_ptr<Option> sPtr_Exit;

	Option* _currentOption; 
	
	sf::Texture _backgroundTexture1;
	sf::Texture _backgroundTexture2;
	sf::Texture _spaceShipTexture;
	sf::Texture _starStripeTexture; 
	sf::Texture _titleScreenTexture; 
};

#endif //MENUSTATE_H