#include "Configuration.h"
thor::ResourceHolder <sf::Texture, std::string> Configuration::resBackgrounds;
thor::ResourceHolder <sf::Texture, std::string> Configuration::resEntities;
thor::ResourceHolder <sf::Texture, std::string> Configuration::resVarious;

thor::ResourceHolder <sf::SoundBuffer, std::string> Configuration::resSoundEffects;

thor::ResourceHolder <sf::Font, std::string> Configuration::resFonts;

void Configuration::initialize()
{
    srand(time(0));

    initTextures();
    initSounds();
    initFonts();
}
void Configuration::release()
{
    releaseTextures();
    releaseSounds();
    releaseFonts();

}

void Configuration::initTextures()
{
    resBackgrounds.acquire("Pattern0", thor::Resources::fromFile<sf::Texture>("resources/various/Pattern0.png"));
    resBackgrounds.acquire("Pattern1", thor::Resources::fromFile<sf::Texture>("resources/various/Pattern1.png"));

    resEntities.acquire("BlackBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/Black.png"));
    resEntities.acquire("BlueBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/Blue.png"));
    resEntities.acquire("CyanBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/Cyan.png"));
    resEntities.acquire("GreenBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/Green.png"));
    resEntities.acquire("PurpleBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/Purple.png"));
    resEntities.acquire("RedBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/Red.png"));
    resEntities.acquire("WhiteBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/White.png"));
    resEntities.acquire("YellowBalloon", thor::Resources::fromFile<sf::Texture>("resources/balloons/Yellow.png"));

    resVarious.acquire("Rotator", thor::Resources::fromFile<sf::Texture>("resources/various/Rotator.png"));
    resVarious.acquire("Cartoon", thor::Resources::fromFile<sf::Texture>("resources/various/Cartoon.png"));
}

void Configuration::releaseTextures()
{
    resBackgrounds.release("Pattern0");
    resBackgrounds.release("Pattern1");

    resEntities.release("BlackBalloon");
    resEntities.release("BlueBalloon");
    resEntities.release("CyanBalloon");
    resEntities.release("GreenBalloon");
    resEntities.release("PurpleBalloon");
    resEntities.release("WhiteBalloon");
    resEntities.release("YellowBalloon");

    resVarious.release("Rotator");
}

void Configuration::initSounds()
{

}

void Configuration::releaseSounds()
{

}

void Configuration::initFonts()
{
    //resFonts.acquire("Demonized", thor::Resources::fromFile<sf::Font>("resources/fonts/Demonized.ttf"));
}

void Configuration::releaseFonts()
{
   // resFonts.release("Demonized");
}

