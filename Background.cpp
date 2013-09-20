#include "Background.h"
#include <iostream>

Background::Background(Game* game) : _game(game){
}


Background::~Background(){
std::cout << "destroying Background\n"; 
}

void Background::Update(const sf::Time& deltaFrame){

}
	
void Background::SetTexture(const sf::Texture& tex){
	_sprite.setTexture(tex); 

}


const sf::Sprite& Background::GetSprite() const{

	return _sprite;

}