#include "MenuState.h"
#include "Game.h"

#include "RandomGenerator.h"
#include "StringUtilities.h"

#include "SFML/Window.hpp"

#include <iostream>

class Game;

MenuState::MenuState( Game* pGame )
    :
    mpGame( pGame ),
    mSpaceShipVelocity( 100.f ),
    mShipDirectionChangeTrigger(0.0f),
    mpCurrentOption( nullptr ),
    mState(State::Menu)
    {
    string file;

    file = "..\\Resources\\Audio\\Menu.ogg";
    pGame->mAudioMan.LoadAndPlayMusic( ToPlatformPath(file) );

    file = "..\\Resources\\Visual\\MainMenuParts\\Background1.jpg";

    if( !mBackgroundTexture1.loadFromFile( ToPlatformPath(file) ) )
        {
        std::cout << "error loading Background-Texture\n";
        }

    file = "..\\Resources\\Visual\\MainMenuParts\\Background2.jpg";
    if( !mBackgroundTexture2.loadFromFile( ToPlatformPath(file) ) )
        {
        std::cout << "error loading Background-Texture\n";
        }

    file = "..\\Resources\\Visual\\MainMenuParts\\Spaceship.png";
    if( !mSpaceShipTexture.loadFromFile( ToPlatformPath(file)) )
        {
        std::cout << "error loading Spaceship-Texture\n";
        }

    file = "..\\Resources\\Visual\\MainMenuParts\\StarStripe.jpg";
    if( !mStarStripeTexture.loadFromFile( ToPlatformPath(file)) )
        {
        std::cout << "error loading StarStripe-Texture\n";
        }

    mSpaceShipSprite.setTexture( mSpaceShipTexture );
    mSpaceShipSprite.setPosition( sf::Vector2f(0.f, 250.f) );
    mBackgroundSprite1.setTexture(mBackgroundTexture1);

    mBackgroundSprite2.setTexture( mBackgroundTexture2 );
    mBackgroundSprite2.setPosition( sf::Vector2f(1024.f, 0.f) );

    mStarStripeSprite.setTexture(mStarStripeTexture);
    mStarStripeSprite.setPosition( sf::Vector2f(1024.f, 100.f) );

    sf::Vector2u size = mpGame->mRenderWindow.getSize();
    int rectHeight = size.y;
    int rectWidth = size.x / 3;
    mRectShape.setFillColor( sf::Color(255,165,0) );
    mRectShape.setSize( sf::Vector2f(rectWidth,rectHeight) );
    mRectShape.setPosition( sf::Vector2f((size.x - rectWidth), (size.y - rectHeight) ) );

    //Setup Menu-Options

    sPtr_NewGame = std::shared_ptr<Option>( new Option("New Game", sf::Vector2f(size.x - size.x / 4, 100), sf::Color::Red) );
    sPtr_Options =  std::shared_ptr<Option>( new Option("Options", sf::Vector2f(size.x - size.x / 4, 300), sf::Color::Black) );
    sPtr_Exit = std::shared_ptr<Option>( new Option("Exit", sf::Vector2f(size.x - size.x / 4, 500), sf::Color::Black) );
    mpCurrentOption = sPtr_NewGame.get();
    sPtr_NewGame->ConnectNext( sPtr_Options.get() );
    sPtr_Options->ConnectFront( sPtr_NewGame.get() );
    sPtr_Options->ConnectNext( sPtr_Exit.get() );
    sPtr_Exit->ConnectFront(sPtr_Options.get());

    }


MenuState::~MenuState()
    {
    //mpGame->mAudioMan.StopMusic();
    std::cout << "Destroying MenuState\n";
    }


const State MenuState::GetStateInput()
    {
    if( mpCurrentOption->mString == "New Game" )
        {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )
            {

            return State::Game;
            }
        }
    else if( mpCurrentOption->mString == "Exit" )
        {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )
            {
            mpGame->mRenderWindow.close();
            }
        }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {

        mpGame->mRenderWindow.close();
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
    }



void MenuState::Update( const sf::Time& deltaFrame )
    {
    /**Background
    *
    */
    sf::Vector2f newPosition = mBackgroundSprite1.getPosition();


    //needs to be sf::Vector2f instead sf::Vector2u because otherwise you cant make
    //the variable negative. Example: "-windowSize.x" would not work
    sf::Vector2f windowSize (mpGame->mRenderWindow.getSize());

    newPosition.x -= 5.f * deltaFrame.asSeconds();
    mBackgroundSprite1.setPosition( newPosition );

    newPosition = mBackgroundSprite2.getPosition();
    newPosition.x -= 5.f * deltaFrame.asSeconds();
    mBackgroundSprite2.setPosition( newPosition );

    if( mBackgroundSprite1.getPosition().x < -windowSize.x )
        {
        mBackgroundSprite1.setPosition( sf::Vector2f(windowSize.x, 0) );
        }
    else if( mBackgroundSprite2.getPosition().x < -windowSize.x )
        {
        mBackgroundSprite2.setPosition( sf::Vector2f(windowSize.x, 0) );
        }

    /**SpaceShip
    *
    */

    float timeStamp = mpGame->mFrameStamp.asSeconds();

    newPosition = mSpaceShipSprite.getPosition();
    newPosition.y += mSpaceShipVelocity * deltaFrame.asSeconds();

    float maxPosition = windowSize.y - float(mSpaceShipSprite.getTextureRect().height);
    float minPosition = 0;

    if ( mShipDirectionChangeTrigger < timeStamp )
        {
        mSpaceShipVelocity = -mSpaceShipVelocity;
        mShipDirectionChangeTrigger = mpGame->mFrameStamp.asSeconds() + Random::Between( 1.0f, 5.0f );
        }

    if( newPosition.y > maxPosition )
        {
        newPosition.y = maxPosition - 1.0f;
        mSpaceShipVelocity = -mSpaceShipVelocity;
        }
    else if( newPosition.y < minPosition )
        {
        newPosition.y = minPosition + 1.0f;
        mSpaceShipVelocity = -mSpaceShipVelocity;
        }

    mSpaceShipSprite.setPosition( newPosition );
//End of Spaceship

//----------------------------------------------------------------------------------------------------------
    /**StarStripe
    */
    newPosition = mStarStripeSprite.getPosition();

    newPosition.x -= 8500.f *deltaFrame.asSeconds(); //Speed of Stripe

    //if x-position smaller than width of stripe-texture + random-amount
    if(newPosition.x < -( (int)mStarStripeTexture.getSize().x + ( mpGame->mRandomNumGenerator.getRandomInt(15000) ) ) )
        {
        newPosition.x = windowSize.x + mpGame->mRandomNumGenerator.getRandomInt( 15000 );
        newPosition.y = mpGame->mRandomNumGenerator.getRandomInt( windowSize.y );
        }
    mStarStripeSprite.setPosition( newPosition );


    }//End of MenuState::Update


void MenuState::Render()
    {
    mpGame->mRenderWindow.clear( sf::Color::Black );
    mpGame->mRenderWindow.draw( mBackgroundSprite1 );
    mpGame->mRenderWindow.draw( mBackgroundSprite2 );
    mpGame->mRenderWindow.draw( mSpaceShipSprite );
    mpGame->mRenderWindow.draw( mStarStripeSprite );
    mpGame->mRenderWindow.draw( mRectShape );
    mpGame->mRenderWindow.draw( sPtr_NewGame->mText );
    mpGame->mRenderWindow.draw( sPtr_Options->mText );
    mpGame->mRenderWindow.draw( sPtr_Exit->mText );
    mpGame->mRenderWindow.display();
    }
