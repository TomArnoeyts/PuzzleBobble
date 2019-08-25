#include "Balloon.h"

Balloon::Balloon(std::string tex_id,World& world) :  _world(world)
{
    _sprite.setTexture(Configuration::resEntities[tex_id]);
    _Alive=true;
    //_sprite.setOrigin(texture.getSize().x/2.f,texture.getSize().y);
}

Balloon::~Balloon()
{
    //dtor
}
void Balloon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite,states);
}

void Balloon::update(sf::Time deltaTime)
{

}


void Balloon::processEvents()
{

}

bool Balloon::isAlive()const
{
	return _Alive;
}

void Balloon::onDestroy()
{
	_Alive = false;
}
