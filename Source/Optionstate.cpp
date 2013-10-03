#include "Optionstate.h"

OptionState::OptionState(Game *pGame) : mpGame(pGame), mState(State::Options)
    {
    mSpaceShipTex.loadFromFile(mpGame->mConfig.GetPlayerTexFrontPath());
    mSpaceShipSprite.setTexture(mSpaceShipTex);
    mSpaceShipSprite.setPosition(sf::Vector2f(100.f,100.f));
    sf::Vector2u size = mpGame->mRenderWindow.getSize();
    int rectHeight = size.y;
    int rectWidth = size.x / 3;
    mRectShape.setFillColor( sf::Color(255,165,0) );
    mRectShape.setSize( sf::Vector2f(rectWidth,rectHeight) );
    mRectShape.setPosition( sf::Vector2f((size.x - rectWidth), (size.y - rectHeight) ) );


    sPtr_Back = std::shared_ptr<Option>( new Option("Back", sf::Vector2f(size.x - size.x / 4, 100), sf::Color::Red) );
    sPtr_Save = std::shared_ptr<Option>(new Option("Save", sf::Vector2f(size.x - size.x/4, 200),sf::Color::Black));
    sPtr_Load =  std::shared_ptr<Option>( new Option("Load", sf::Vector2f(size.x - size.x / 4, 300), sf::Color::Black) );

    mpCurrentOption = sPtr_Back.get();
    sPtr_Back->ConnectNext(sPtr_Save.get());
    sPtr_Save->ConnectFront(sPtr_Back.get());
    sPtr_Save->ConnectNext(sPtr_Load.get());
    sPtr_Load->ConnectFront(sPtr_Save.get());
    }


OptionState::~OptionState()
    {
    std::cout << "deleting OptionState\n";
    }

const State OptionState::GetStateInput()
    {

    if(mpCurrentOption->mString == "Back")
        {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
             return State::Menu;
            }
        }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        {
         mpGame->mInputInterval.Reset();
         if( mpCurrentOption->mpNext )
            {
            mpCurrentOption = mpCurrentOption->GoNext();
            }

        }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        {
         mpGame->mInputInterval.Reset();
         if( mpCurrentOption->mpFront )
            {
             mpCurrentOption= mpCurrentOption->GoFront();
            }

        }

        return mState;

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
    mpGame->mRenderWindow.draw(sPtr_Back->mText);
    mpGame->mRenderWindow.draw(sPtr_Save->mText);
    mpGame->mRenderWindow.draw(sPtr_Load->mText);
    mpGame->mRenderWindow.draw(mSpaceShipSprite);
    mpGame->mRenderWindow.display();
    }
