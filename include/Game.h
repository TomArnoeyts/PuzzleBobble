#ifndef GAME_H
#define GAME_H
#include <Configuration.h>
#include <StdAngle.h>

#include <SFML/Graphics.hpp>

#include <World.h>
#include <iostream>
#include <Balloon.h>

#include <strstream>

class Game
{
    public:
        Game();
        Game(const Game& other)=delete;
        Game& operator=(const Game& other)=delete;
        ~Game();
        void run(int frames_per_second);


    protected:

    private:
        sf::RenderWindow _window;

        void processEvents();
        void update (sf::Time deltaTime);
        void render();

        enum GameState {Menu, Playing, Credits, GameOver};
        GameState _GameState;
        World* _world;

        void initGame();

        sf::Sprite*** backgroundSprites;

        sf::Sprite sprtRotator;
        enum direction {Left, Right};
        void rotateRotator(direction dir);

        sf::Time rotateTimer=sf::Time::Zero;

        sf::Sprite sprtCartoon;

        Balloon* balReadyToLaunch;

        sf::Text txtScore;

};

#endif // GAME_H
