#ifndef GAME_H
#define GAME_H
#include <SFML\Graphics.hpp>
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include "RandomNumberGenerator.h"
#include <iostream>
class SwitchStateInput{
private:
	float _press_Button_Trigger;
	const float PRESS_RELEASE_TIME; 
public:
	SwitchStateInput(float pressRelease) 
		: 
		PRESS_RELEASE_TIME(pressRelease),
		_press_Button_Trigger(0.f)
		{}

	void process(const sf::Time& frameDelta){
		_press_Button_Trigger += frameDelta.asSeconds(); 
	}

	void reset(){
		_press_Button_Trigger = 0.f; 
	}
	
	bool canChange(){
		if(_press_Button_Trigger > PRESS_RELEASE_TIME){
			return true; 
		}
		return false;  
	}
};

class Game
{
public:
	Game(int width, int height);
	~Game(void);

	bool Initialize(); 
	int Run(); 
	void ProcessHandle(); 


	//Fields
	RandomNumberGenerator _randomNumGenerator; 
	int _width, _height; 
	sf::Clock _start_time; 
	sf::Time _frame_delta;
 
	SwitchStateInput	_switchStateInput; 

	sf::RenderWindow	renderWindow;
	IState*				_currentState; 
	IState*				_previousState; 



	sf::Texture			_starTexture; 
	sf::Texture			_playerTexture;
	sf::Texture			_backgroundTexture; 
	sf::Texture			_titleScreen; 

};
#endif //GAME_H