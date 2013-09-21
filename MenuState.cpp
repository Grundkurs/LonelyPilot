#include "MenuState.h"
#include "Game.h"
#include <iostream>
class Game; 

MenuState::MenuState( Game* game ) 
	: 
	_game( game ), 
	_spaceShipVelocity( 10.f ),
	_currentOption( nullptr )
{

	if( !_backgroundTexture1.loadFromFile("..\\Art\\Visual\\MainMenuParts\\Background1.jpg") )
		{
			std::cout << "error loading Background-Texture\n"; 
		}
		
		if( !_backgroundTexture2.loadFromFile("..\\Art\\Visual\\MainMenuParts\\Background2.jpg") )
		{
			std::cout << "error loading Background-Texture\n"; 
		}
		
		
		if( !_spaceShipTexture.loadFromFile("..\\Art\\Visual\\MainMenuParts\\Spaceship.png") )
		{
			std::cout << "error loading Spaceship-Texture\n"; 
		}

		if( !_starStripeTexture.loadFromFile("..\\Art\\Visual\\MainMenuParts\\StarStripe.jpg") )
		{
			std::cout << "error loading StarStripe-Texture\n"; 
		}
		




		_spaceShipSprite.setTexture( _spaceShipTexture );
		_spaceShipSprite.setPosition( sf::Vector2f(0.f, 250.f) );
		_backgroundSprite1.setTexture(_backgroundTexture1);
		
		_backgroundSprite2.setTexture( _backgroundTexture2 );
		_backgroundSprite2.setPosition( sf::Vector2f(1024.f, 0.f) );
		
		_starStripeSprite.setTexture(_starStripeTexture); 
		_starStripeSprite.setPosition( sf::Vector2f(1024.f, 100.f) ); 

		int rectHeight = _game->_height; 
		int rectWidth = _game->_width /3; 
		_rectShape.setFillColor( sf::Color(255,165,0) );
		_rectShape.setSize( sf::Vector2f(rectWidth,rectHeight) ); 
		_rectShape.setPosition( sf::Vector2f((_game->_width - rectWidth), (_game->_height - rectHeight) ) ); 

		if( !_font.loadFromFile("..\\Art\\Fonts\\Acme.ttf") )
		{
			std::cout << "could not load font!\n"; 
		}
		_NewGameText.setFont( _font ); 
		_NewGameText.setString( "New Game" ); 
		_NewGameText.setCharacterSize( 40 );  
		_NewGameText.setColor( sf::Color::Red ); 
		_NewGameText.setPosition( _game->_width /4, _game->_height - _NewGameText.getCharacterSize() ); 


		sPtr_NewGame = std::shared_ptr<Option>( new Option("New Game", sf::Vector2f(_game->_width -_game->_width/4, 100), sf::Color::Red) );
		sPtr_Options =  std::shared_ptr<Option>( new Option("Options", sf::Vector2f(_game->_width - _game->_width/4, 300), sf::Color::Black) );
		sPtr_Exit = std::shared_ptr<Option>( new Option("Exit", sf::Vector2f(_game->_width - _game->_width/4, 500), sf::Color::Black) );
		_currentOption = sPtr_NewGame.get(); 
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
	
	//TODO: Change this Check to ENUM (its faster)
	if( _currentOption->_string == "New Game" )
	{
		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )
		{
			_game->_switchStateInput.reset(); 
			return new GameState( _game );
		}
	}

	else if( _currentOption->_string == "Exit" )
	{
		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )
		{
			_game->renderWindow.close(); 
		}
	}

	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
	
			_game->_switchStateInput.reset(); 
			_game->renderWindow.close(); 
		}

		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
		{
			 _game->_switchStateInput.reset(); 
			 if( _currentOption->_next )
			 { 
				_currentOption = _currentOption->GoNext();
			 }

		}
		
		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
		{
			 _game->_switchStateInput.reset(); 
			 if( _currentOption->_front )
			 {
				 _currentOption= _currentOption->GoFront(); 
			 }
			
		}

	return this; 
} 
void MenuState::Update( const sf::Time& deltaFrame ){

/**Background
*
*/
	sf::Vector2f newPosition = _backgroundSprite1.getPosition();


	newPosition.x -= 5.f * deltaFrame.asSeconds();
	_backgroundSprite1.setPosition( newPosition ); 
	
	newPosition = _backgroundSprite2.getPosition();
	newPosition.x -= 5.f * deltaFrame.asSeconds();
	_backgroundSprite2.setPosition( newPosition ); 
	
	if( _backgroundSprite1.getPosition().x < -1024 )
	{
		_backgroundSprite1.setPosition( sf::Vector2f(1024.f, 0) );
	}
	else if( _backgroundSprite2.getPosition().x < -1024 )
	{
		_backgroundSprite2.setPosition( sf::Vector2f(1024.f, 0) );
	}

/**SpaceShip
*
*/
	newPosition = _spaceShipSprite.getPosition();

	newPosition.y += _spaceShipVelocity * deltaFrame.asSeconds();

	if( newPosition.y > 260 )
	{
		newPosition.y = 259.f;
		_spaceShipVelocity = -_spaceShipVelocity;
	}
	else if( newPosition.y < 240 )
	{
		newPosition.y = 241.f;
		_spaceShipVelocity = -_spaceShipVelocity;
	
	}

	_spaceShipSprite.setPosition( newPosition );
//End of Spaceship

//----------------------------------------------------------------------------------------------------------
	/**StarStripe
	*/
	newPosition = _starStripeSprite.getPosition(); 
	newPosition.x -= 8500.f *deltaFrame.asSeconds(); //Speed of Stripe
	
	//if x-position smaller than width of stripe-texture + random-amount 
	if(newPosition.x < -( (int)_starStripeTexture.getSize().x + ( _game->_randomNumGenerator.getRandomInt(15000) ) ) )
	{
		newPosition.x = _game->_width + _game->_randomNumGenerator.getRandomInt( 15000 ); 
		newPosition.y = _game->_randomNumGenerator.getRandomInt( _game->_height );
	}
		_starStripeSprite.setPosition( newPosition ); 
}
void MenuState::Render(){
	_game->renderWindow.clear( sf::Color::Black );
	_game->renderWindow.draw( _backgroundSprite1 ); 
	_game->renderWindow.draw( _backgroundSprite2 ); 
	_game->renderWindow.draw( _spaceShipSprite ); 
	_game->renderWindow.draw( _starStripeSprite ); 
	_game->renderWindow.draw( _rectShape ); 
	_game->renderWindow.draw( sPtr_NewGame->_text );
	_game->renderWindow.draw( sPtr_Options->_text ); 
	_game->renderWindow.draw( sPtr_Exit->_text ); 
	_game->renderWindow.display(); 
} 