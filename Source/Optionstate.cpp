#include "Optionstate.h"

OptionState::OptionState(Game *pGame) : mpGame(pGame), mState(State::Options)
    {
	string file; 
	file = mpGame->mConfig.GetPlayerTexFrontPath();
	if (!mSpaceShipTex.loadFromFile(ToPlatformPath(file) ) )
		{
		std::cout << "could not open Player Ship\n"; 
		}
	file = "..\\Resources\\Visual\\MainMenuParts\\Background1.jpg";

	if (!mBackgroundTexture1.loadFromFile(ToPlatformPath(file)))
	{
		std::cout << "error loading Background-Texture\n";
	}

	file = "..\\Resources\\Visual\\MainMenuParts\\Background2.jpg";
	if (!mBackgroundTexture2.loadFromFile(ToPlatformPath(file)))
	{
		std::cout << "error loading Background-Texture\n";
	}

	file = "..\\Resources\\Visual\\MainMenuParts\\StarStripe.jpg";
	if (!mStarStripeTexture.loadFromFile(ToPlatformPath(file)))
	{
		std::cout << "error loading starStripe-Texture\n";
	}

    mSpaceShipSprite.setTexture(mSpaceShipTex);
	mStarStripeSprite.setTexture(mStarStripeTexture);
	mBackgroundSprite1.setTexture(mBackgroundTexture1);
	mBackgroundSprite2.setTexture(mBackgroundTexture2);
	mBackgroundSprite2.setPosition(sf::Vector2f(0.f, -768.f));
	mStarStripeSprite.rotate(90.f);

    mSpaceShipSprite.setPosition(sf::Vector2f(100.f,100.f));
    sf::Vector2u size = mpGame->mRenderWindow.getSize();
    int rectHeight = size.y;
    int rectWidth = size.x / 3;
    mRectShape.setFillColor( sf::Color(255,165,0) );
    mRectShape.setSize( sf::Vector2f(rectWidth,rectHeight) );
    mRectShape.setPosition( sf::Vector2f((size.x - rectWidth), (size.y - rectHeight) ) );


    sPtr_Back = std::shared_ptr<Option>( new Option(OptionName::BACK, sf::Vector2f(size.x - size.x / 4, 100), sf::Color::Red) );
    sPtr_Save = std::shared_ptr<Option>(new Option(OptionName::SAVE, sf::Vector2f(size.x - size.x/4, 200),sf::Color::Black));
    sPtr_Load =  std::shared_ptr<Option>( new Option(OptionName::LOAD, sf::Vector2f(size.x - size.x / 4, 300), sf::Color::Black) );

    mpCurrentOption = sPtr_Back.get();
    sPtr_Back->ConnectNext(sPtr_Save.get());
    sPtr_Save->ConnectFront(sPtr_Back.get());
    sPtr_Save->ConnectNext(sPtr_Load.get());
    sPtr_Load->ConnectFront(sPtr_Save.get());
    }


OptionState::~OptionState()
    {
    std::cout << "destroying OptionState\n";
    }

const State OptionState::GetStateInput()
    {

    if(mpCurrentOption->mOptionName == OptionName::BACK)
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



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
        return State::Menu;
        }
    return mState;
    }
void OptionState::Update(const sf::Time& deltaFrame)
    {
	sf::Vector2f newPosition = mBackgroundSprite1.getPosition();
	sf::Vector2f windowSize(mpGame->mRenderWindow.getSize());
	
	//Background
	//-----
	newPosition.y += 10.f * deltaFrame.asSeconds();
	mBackgroundSprite1.setPosition(newPosition);

	newPosition = mBackgroundSprite2.getPosition();
	newPosition.y += 10.f * deltaFrame.asSeconds();
	mBackgroundSprite2.setPosition(newPosition);

	if (mBackgroundSprite1.getPosition().y > windowSize.y)
	{
		mBackgroundSprite1.setPosition(sf::Vector2f(0, -windowSize.y));
	}
	else if (mBackgroundSprite2.getPosition().y > windowSize.y)
	{
		mBackgroundSprite2.setPosition(sf::Vector2f(0, -windowSize.y));
	}

	// StarStripe
	//-------
	newPosition = mStarStripeSprite.getPosition();

	newPosition.y += 8500.f *deltaFrame.asSeconds(); //Speed of Stripe

	//if x-position smaller than width of stripe-texture + random-amount
	if (newPosition.y > ((int)windowSize.y + (mpGame->mRandomNumGenerator.getRandomInt(15000)) + mStarStripeTexture.getSize().y ))
	{
		newPosition.y = -windowSize.y - mpGame->mRandomNumGenerator.getRandomInt(15000);
		newPosition.x = mpGame->mRandomNumGenerator.getRandomInt(windowSize.y);
	}
	mStarStripeSprite.setPosition(newPosition);
    }
void OptionState::Render()
    {
    mpGame->mRenderWindow.clear(sf::Color::Black);
	mpGame->mRenderWindow.draw(mBackgroundSprite1);
	mpGame->mRenderWindow.draw(mBackgroundSprite2);
	mpGame->mRenderWindow.draw(mSpaceShipSprite);
	mpGame->mRenderWindow.draw(mStarStripeSprite);
	mpGame->mRenderWindow.draw(mRectShape);
    mpGame->mRenderWindow.draw(sPtr_Back->mText);
    mpGame->mRenderWindow.draw(sPtr_Save->mText);
    mpGame->mRenderWindow.draw(sPtr_Load->mText);

    mpGame->mRenderWindow.display();
    }

void OptionState::SetResumeProperty(bool resume){}
