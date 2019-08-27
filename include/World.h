#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics.hpp>
#include <list>
#include <Balloon.h>
#include <iostream>
class Balloon;
class World:public sf::Drawable
{
    public:
        World(sf::RenderWindow& window);
        virtual ~World();
        World(const World& other) = delete;
        World& operator=(const World& other)=delete;

        void update(sf::Time deltaTime);

        void processEvents();

        void addBalloon(Balloon* b);

        void initBalloonGrid();

        void disposeBalloonGrid();

        bool bBalloonLocked=true;

        int iScore=0;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//MOET je implementeren om over te erven van sf::Drawable
        sf::RenderWindow& _window;

        std::list<Balloon*> _balloons;

        Balloon*** balloonGrid;

        void setBalloonPositions();

        void checkTriplesOrMore();

        void removeFreeBalloons();
};

#endif // WORLD_H
