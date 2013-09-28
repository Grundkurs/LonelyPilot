#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include "RandomNumberGenerator.h"
#include "AudioManager.h"
#include "ConfigLoader.h"

#include <iostream>


class SwitchStateInput
{
private:
    float mPress_Button_Trigger;
    const float PRESS_RELEASE_TIME;
public:
    SwitchStateInput(float pressRelease)
        :

        mPress_Button_Trigger(0.f),
        PRESS_RELEASE_TIME(pressRelease)
        {}

    void process(const sf::Time& frameDelta)
        {
        mPress_Button_Trigger += frameDelta.asSeconds();
        }

    void reset()
        {
        mPress_Button_Trigger = 0.f;
        }

    bool canChange()
        {
        if(mPress_Button_Trigger > PRESS_RELEASE_TIME)
            {
            return true;
            }
        return false;
        }
};

class Game
{								//private copy constructor, prevents that Game can be copied
                                Game(const Game& game);
public:
                                Game();
                                ~Game(void);

        bool					Initialize();
        int						Run();
        void					ProcessHandle();


        //Fields
        sf::RenderWindow		mRenderWindow;
        RandomNumberGenerator	mRandomNumGenerator;
        sf::Clock				mStartClock;
        sf::Time				mFrameDelta;
        sf::Time				mFrameStamp;

        //IState*					mpCurrentState;
        //IState*					mpPreviousState;
        std::unique_ptr<IState> mpCurrentState;

        SwitchStateInput		mSwitchStateInput;



        sf::Texture				mStarTexture;
        sf::Texture				mPlayerTexture;
        sf::Texture				mBackgroundTexture;
        sf::Texture				mAmbulanceTexture;

        ConfigLoader mConfig;

        AudioManager mAudioMan;
};
#endif //GAME_H
