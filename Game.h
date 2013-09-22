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
{								//private copy constructor, prevents that Game can be copied
								Game(const Game& game); 
public:
								Game(int width, int height);
								~Game(void);
		
		bool					Initialize(); 
		int						Run(); 
		void					ProcessHandle(); 
		
		
		//Fields
		RandomNumberGenerator	mRandomNumGenerator; 
		int						mWidth, mHeight; 
		sf::Clock				mStartTime; 
		sf::Time				mFrameDelta;
		
		SwitchStateInput		mSwitchStateInput; 
		
		sf::RenderWindow		mRenderWindow;
		IState*					mpCurrentState; 
		IState*					mpPreviousState; 
		
		
		
		sf::Texture				mStarTexture; 
		sf::Texture				mPlayerTexture;
		sf::Texture				mBackgroundTexture; 
	
		
};
#endif //GAME_H