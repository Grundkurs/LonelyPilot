#include "MenuState.h"
#include "Game.h"
#include "StringUtilities.h"

#include <iostream>

class Game;

MenuState::MenuState( Game* game )
	:
	mpGame( game ),
	mSpaceShipVelocity( 10.f ),
	mpCurrentOption( nullptr )
	{
	string file("..\\Art\\Visual\\MainMenuParts\\Background1.jpg");

	if( !mBackgroundTexture1.loadFromFile(ToPlatformPath(file) ) )
			{
			std::cout << "error loading Background-Texture\n";
			}

	file = "..\\Art\\Visual\\MainMenuParts\\Background2.jpg";
	if( !mBackgroundTexture2.loadFromFile(ToPlatformPath(file) ) )
		{
		std::cout << "error loading Background-Texture\n";
		}

	file = "..\\Art\\Visual\\MainMenuParts\\Spaceship.png";
	if( !mSpaceShipTexture.loadFromFile( ToPlatformPath(file)) )
		{
		std::cout << "error loading Spaceship-Texture\n";
		}
	file = "..\\Art\\Visual\\MainMenuParts\\StarStripe.jpg";
	if( !mStarStripeTexture.loadFromFile(ToPlatformPath(file)) )
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

		int rectHeight = mpGame->mHeight;
		int rectWidth = mpGame->mWidth /3;
		mRectShape.setFillColor( sf::Color(255,165,0) );
		mRectShape.setSize( sf::Vector2f(rectWidth,rectHeight) );
		mRectShape.setPosition( sf::Vector2f((mpGame->mWidth - rectWidth), (mpGame->mHeight - rectHeight) ) );

		//Setup Menu-Options
		sPtr_NewGame = std::shared_ptr<Option>( new Option("New Game", sf::Vector2f(mpGame->mWidth -mpGame->mWidth/4, 100), sf::Color::Red) );
		sPtr_Options =  std::shared_ptr<Option>( new Option("Options", sf::Vector2f(mpGame->mWidth - mpGame->mWidth/4, 300), sf::Color::Black) );
		sPtr_Exit = std::shared_ptr<Option>( new Option("Exit", sf::Vector2f(mpGame->mWidth - mpGame->mWidth/4, 500), sf::Color::Black) );
		mpCurrentOption = sPtr_NewGame.get();
		sPtr_NewGame->ConnectNext( sPtr_Options.get() );
		sPtr_Options->ConnectFront( sPtr_NewGame.get() );
		sPtr_Options->ConnectNext( sPtr_Exit.get() );
		sPtr_Exit->ConnectFront(sPtr_Options.get());


	}


MenuState::~MenuState()
	{
	std::cout << "Destroying MenuState\n";
	}


IState* MenuState::ProcessStateInput( const sf::Event& event )
{

	//TODO: Change this Check to ENUM (its faster!)
	if( mpCurrentOption->mString == "New Game" )
		{
		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )
			{
			mpGame->mSwitchStateInput.reset();
			return new GameState( mpGame );
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
			mpGame->mSwitchStateInput.reset();
			mpGame->mRenderWindow.close();
			}

		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
			{
			 mpGame->mSwitchStateInput.reset();
			 if( mpCurrentOption->mpNext )
				{
				mpCurrentOption = mpCurrentOption->GoNext();
				}

			}

		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
			{
			 mpGame->mSwitchStateInput.reset();
			 if( mpCurrentOption->mpFront )
				{
				 mpCurrentOption= mpCurrentOption->GoFront();
				 }

			}
	return this;
	}
void MenuState::Update( const sf::Time& deltaFrame )
	{
/**Background
*
*/
	sf::Vector2f newPosition = mBackgroundSprite1.getPosition();


	newPosition.x -= 5.f * deltaFrame.asSeconds();
	mBackgroundSprite1.setPosition( newPosition );

	newPosition = mBackgroundSprite2.getPosition();
	newPosition.x -= 5.f * deltaFrame.asSeconds();
	mBackgroundSprite2.setPosition( newPosition );

	if( mBackgroundSprite1.getPosition().x < -1024 )
		{
		mBackgroundSprite1.setPosition( sf::Vector2f(1024.f, 0) );
		}
	else if( mBackgroundSprite2.getPosition().x < -1024 )
		{
		mBackgroundSprite2.setPosition( sf::Vector2f(1024.f, 0) );
		}

/**SpaceShip
*
*/
	newPosition = mSpaceShipSprite.getPosition();
	newPosition.y += mSpaceShipVelocity * deltaFrame.asSeconds();

	if( newPosition.y > 260 )
		{
		newPosition.y = 259.f;
		mSpaceShipVelocity = -mSpaceShipVelocity;
		}
	else if( newPosition.y < 240 )
		{
		newPosition.y = 241.f;
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
		newPosition.x = mpGame->mWidth + mpGame->mRandomNumGenerator.getRandomInt( 15000 );
		newPosition.y = mpGame->mRandomNumGenerator.getRandomInt( mpGame->mHeight );
		}
		mStarStripeSprite.setPosition( newPosition );
	}
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
