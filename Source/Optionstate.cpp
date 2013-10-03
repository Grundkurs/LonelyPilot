#include "Optionstate.h"

OptionState::OptionState(Game *pGame) : mpGame(pGame), mState(State::Options)
    {
    sf::Vector2u size = mpGame->mRenderWindow.getSize();
    int rectHeight = size.y;
    int rectWidth = size.x / 3;
    mRectShape.setFillColor( sf::Color(255,165,0) );
    mRectShape.setSize( sf::Vector2f(rectWidth,rectHeight) );
    mRectShape.setPosition( sf::Vector2f((size.x - rectWidth), (size.y - rectHeight) ) );

    }


OptionState::~OptionState()
    {
    std::cout << "deleting OptionState\n";
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
    mpGame->mRenderWindow.clear(sf::Color::Black);
    mpGame->mRenderWindow.draw(mRectShape);
    mpGame->mRenderWindow.display();
    }
