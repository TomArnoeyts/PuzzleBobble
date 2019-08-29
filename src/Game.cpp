#include "Game.h"

Game::Game():_window(sf::VideoMode(600, 600), "Puzzle Bobble")
{
   _world=new World(_window);

   initGame();
}

Game::~Game()
{
    delete _world;
}
void Game::run(int frames_per_second)
{
    //initGame();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame=sf::seconds(1.f/frames_per_second);
    while (_window.isOpen())
    {
        //We gaan ALTIJD de events verwerken
        processEvents();

        bool repaint=false;
        timeSinceLastUpdate+=clock.restart();
        while (timeSinceLastUpdate>TimePerFrame)
        {
            timeSinceLastUpdate-=TimePerFrame;
            repaint=true;
            //update 30 keer per seconde

            update(TimePerFrame);
        }

        //We renderen eigenlijk maar 30 keer per seconde
        if (repaint)
            render();
    }
}
void Game::processEvents()
{
    sf::Event event;
    while(_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            //_gameStatus=StatusExit;
            _window.close();
        }

        switch (_GameState)
        {
        case GameState::Playing:
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code==sf::Keyboard::Space)
                    if (balReadyToLaunch)
                        balReadyToLaunch->releaseBalloon(StdAngle::CalculateStdAngle(sprtRotator.getRotation()));
            }
            break;
        default:
                break;
        }
    }
    switch (_GameState)
    {
        case GameState::Playing:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rotateTimer<=sf::Time::Zero)
            {
                rotateRotator(direction::Left);
                rotateTimer=sf::seconds(0.025);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rotateTimer<=sf::Time::Zero)
            {
                rotateRotator(direction::Right);
                rotateTimer=sf::seconds(0.025);
            }

            break;
        default:
            break;
    }
}
void Game::update(sf::Time deltaTime)
{
    std::stringstream ssScore;
    switch (_GameState)
    {

        case GameState::Playing:
            if (rotateTimer>sf::Time::Zero)
                rotateTimer-=deltaTime;
            _world->update(deltaTime);

            if (_world->bBalloonLocked)
            {
                 setNextBalloon();
            }



            ssScore << "Score: " << _world->iScore;
            txtScore.setString(ssScore.str());
            break;
        default:
            break;
    }
}

void Game::render()
{
    _window.clear(sf::Color::White);

    switch (_GameState)
    {

    case GameState::Playing:
        _window.draw(sprtCartoon);
        for (int i=0;i<10;i++)
        {
            for (int j=0; j<8; j++)
            {
                _window.draw((*backgroundSprites[i][j]));
            }
        }
        _window.draw(*_world);
        _window.draw(sprtRotator);
        _window.draw(txtScore);
        break;
    default:
        break;

    }

    _window.display();
}

void Game::initGame()
{

    _GameState=GameState::Playing;

    sprtRotator.setTexture(Configuration::resVarious["Rotator"]);
    sprtRotator.setOrigin(64,63);
    sprtRotator.setPosition(160+4*48, 64+10*48);

    sprtCartoon.setTexture(Configuration::resVarious["Cartoon"]);
    sprtCartoon.setScale(0.25,0.25);
    sprtCartoon.setPosition(0,260);

    backgroundSprites=new sf::Sprite**[10];
    for (int i=0;i<10;i++)
    {
        backgroundSprites[i]=new sf::Sprite*[8];
        for (int j=0; j<8; j++)
        {
            backgroundSprites[i][j]=new sf::Sprite();
            if (i % 2 == 1)
            {
                if (j % 2 == 1)
                {
                    (*backgroundSprites[i][j]).setTexture(Configuration::resBackgrounds["Pattern0"]);
                }
                else
                {
                    (*backgroundSprites[i][j]).setTexture(Configuration::resBackgrounds["Pattern1"]);
                }

            }
            else
            {
                if (j % 2 == 0)
                {
                    (*backgroundSprites[i][j]).setTexture(Configuration::resBackgrounds["Pattern0"]);
                }
                else
                {
                    (*backgroundSprites[i][j]).setTexture(Configuration::resBackgrounds["Pattern1"]);
                }

            }

            (*backgroundSprites[i][j]).setPosition(160+j*48, 64+i*48);
            (*backgroundSprites[i][j]).setScale(0.375,0.375);
        }
    }
    txtScore.setCharacterSize(24);
    txtScore.setPosition(20,20);
    txtScore.setFillColor(sf::Color::Black);
    txtScore.setFont(Configuration::resFonts["InGameFont"]);
    txtScore.setString("Score: 0");
    setNextBalloon();
    setNextBalloon();
}

void Game::rotateRotator(direction dir)
{
    bool bRotateAllowed=false;

    if (sprtRotator.getRotation()<90)
        bRotateAllowed=true;
    else
    {
        if (sprtRotator.getRotation()>270)
            bRotateAllowed=true;
    }
    if (bRotateAllowed)
    {
        if (dir==direction::Left)
            sprtRotator.rotate(-1);
        if (dir==direction::Right)
            sprtRotator.rotate(+1);
    }

    if (sprtRotator.getRotation()>180)
    {
        if (sprtRotator.getRotation()<=270)
            sprtRotator.setRotation(271);
    }
    else
    {
        if (sprtRotator.getRotation()<=90)
        {
            if (sprtRotator.getRotation()>89)
                sprtRotator.setRotation(89);
        }

    }

   // std::cout << sprtRotator.getRotation() << std::endl;

}


void Game::setNextBalloon()
{
    std::string BalloonType;

    int r=rand() % 8;

    switch (r)
    {
    case 0:
        BalloonType="BlackBalloon";
        break;
    case 1:
        BalloonType="BlueBalloon";
        break;
    case 2:
        BalloonType="CyanBalloon";
        break;
    case 3:
        BalloonType="GreenBalloon";
        break;
    case 4:
        BalloonType="PurpleBalloon";
        break;
    case 5:
        BalloonType="RedBalloon";
        break;
    case 6:
        BalloonType="WhiteBalloon";
        break;
    case 7:
        BalloonType="YellowBalloon";
        break;

    }


    Balloon* b=new Balloon(BalloonType, *_world);
    b->setPosition(sprtRotator.getPosition().x-64, sprtRotator.getPosition().y);
    b->_sprite.setOrigin(16,16);

    balReadyToLaunch=balNextBalloon;
    if (balReadyToLaunch)
        balReadyToLaunch->setPosition(sprtRotator.getPosition());
    balNextBalloon=b;
    _world->addBalloon(b);
    _world->bBalloonLocked=false;
}
