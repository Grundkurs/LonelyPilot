#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include <memory>
#include "Option.h"
#include "SFML/Graphics.hpp"

class Game;
class OptionState : public IState
{

public:
                                        OptionState(Game* pGame);
                                        ~OptionState();
    const   State                       GetStateInput();
            void						Update(const sf::Time& deltaFrame);
            void						Render();
            void                        SetResumeProperty(bool resume);
private:
            sf::RectangleShape          mRectShape;

            Game*                       mpGame;
    const	State                       mState;
            std::shared_ptr<Option>		sPtr_Back;
            std::shared_ptr<Option>		sPtr_Save;
            std::shared_ptr<Option>		sPtr_Load;

            Option*						mpCurrentOption;

            sf::Sprite					mSpaceShipSprite;
            sf::Texture                 mSpaceShipTex;
};

#endif // OPTIONSTATE_H
