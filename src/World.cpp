#include "World.h"

World::World(sf::RenderWindow& window):_window(window)
{

}

World::~World()
{
    //dtor
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (Balloon* b : _balloons)
        _window.draw(*b);
}

void World::addBalloon(Balloon* b)
{
    _balloons.push_back(b);
}
