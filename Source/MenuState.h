#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include <memory>
#include "Option.h"
class Game;
class MenuState : public IState
{
        Game*                       mpGame;
const	State                       mState;

public:
                                    MenuState(Game* pGame);
                                    ~MenuState();

const   State                       GetStateInput();

        void						Update(const sf::Time& deltaFrame);
        void						Render();

        sf::Sprite					mBackgroundSprite1;
        sf::Sprite					mBackgroundSprite2;
        sf::Sprite					mSpaceShipSprite;
        sf::Sprite					mStarStripeSprite;
        sf::RectangleShape			mRectShape;
        float						mSpaceShipVelocity;
        float						mShipDirectionChangeTrigger;
        float                       mStarStripeDirectionChangeTrigger;

        std::shared_ptr<Option>		sPtr_NewGame;
        std::shared_ptr<Option>		sPtr_Options;
        std::shared_ptr<Option>		sPtr_Exit;

        Option*						mpCurrentOption;

        sf::Texture					mBackgroundTexture1;
        sf::Texture					mBackgroundTexture2;
        sf::Texture					mSpaceShipTexture;
        sf::Texture					mStarStripeTexture;

};

#endif //MENUSTATE_H
