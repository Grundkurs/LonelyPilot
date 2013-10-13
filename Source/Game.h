#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include "Optionstate.h"
#include "RandomNumberGenerator.h"
#include "AudioManager.h"
#include "ConfigLoader.h"
#include "inputinterval.h"
#include <iostream>



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



        std::shared_ptr<IState> uPtr_CurrentState;
        std::shared_ptr<IState> uPtr_RunningState;
        State                   mCurrState;
        State                   mOldState;

        InputInterval           mInputInterval;

        //Content
        sf::Texture				mStarTexture;
        sf::Texture				mPlayerTexture;
        sf::Texture				mBackgroundTexture;
        sf::Texture				mAmbulanceTexture;
        sf::Texture             mBaldusTexture;
        sf::Texture             mLaserTexture;


        ConfigLoader mConfig;

        AudioManager mAudioMan;
};
#endif //GAME_H
