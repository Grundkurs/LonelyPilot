#include "Optionstate.h"

OptionState::OptionState(Game *pGame) : mpGame(pGame), mState(State::Options)
    {

    }


OptionState::~OptionState()
    {

    }

const State OptionState::GetStateInput()
    {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
        return State::Menu;
        }
    return mState;
    }
void OptionState::Update(const sf::Time& deltaFrame)
    {

    }
void OptionState::Render()
    {
    mpGame->mRenderWindow.clear(sf::Color::Red);
    mpGame->mRenderWindow.display();
    }
