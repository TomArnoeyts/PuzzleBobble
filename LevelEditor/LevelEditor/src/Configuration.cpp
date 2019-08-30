#include "Configuration.h"

thor::ResourceHolder <sf::Texture, std::string> Configuration::resEntities;

void Configuration::initialize()
{
    resEntities.acquire("BlackBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/Black.png"));
    resEntities.acquire("BlueBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/Blue.png"));
    resEntities.acquire("CyanBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/Cyan.png"));
    resEntities.acquire("GreenBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/Green.png"));
    resEntities.acquire("PurpleBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/Purple.png"));
    resEntities.acquire("RedBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/Red.png"));
    resEntities.acquire("WhiteBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/White.png"));
    resEntities.acquire("YellowBalloon", thor::Resources::fromFile<sf::Texture>("../../resources/balloons/Yellow.png"));
    resEntities.acquire("Empty", thor::Resources::fromFile<sf::Texture>("Empty.png"));
}

void Configuration::release()
{
    resEntities.release("BlackBalloon");
    resEntities.release("BlueBalloon");
    resEntities.release("CyanBalloon");
    resEntities.release("GreenBalloon");
    resEntities.release("PurpleBalloon");
    resEntities.release("RedBalloon");
    resEntities.release("WhiteBalloon");
    resEntities.release("YellowBalloon");
    resEntities.release("Empty");

}
