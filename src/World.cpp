#include "World.h"

World::World(sf::RenderWindow& window):_window(window)
{
    initBalloonGrid();
}

World::~World()
{
    disposeBalloonGrid();
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

void World::update(sf::Time dt)
{
    for (Balloon* b : _balloons)
    {
        b->update(dt);
        if (b->bIsReleased)
        {
            int currentX, currentY;
            currentX=(b->_sprite.getPosition().x-160) / 48;//Verschuiven?
            currentY=(b->_sprite.getPosition().y-64) / 48;

            std::cout << "X=" << currentX << " Y=" << currentY << std::endl;

            bool bHaveToLock=false;

            if (currentY==1)
            {
                if (balloonGrid[0][currentX-1]||balloonGrid[0][currentX])
                {
                    balloonGrid[1][currentX]=b;
                }
                else
                {
                    if (balloonGrid[0][currentX])
                        balloonGrid[0][currentX+1]=b;
                    else
                        balloonGrid[0][currentX]=b;
                }
                bHaveToLock=true;
            }
            else
            {

                if (currentY % 2 == 0)
                {
                    if (currentX==0)
                    {
                        if (balloonGrid[currentY-1][0])
                        {
                            balloonGrid[currentY][0]=b;
                            bHaveToLock=true;
                        }

                    }
                    else if (currentX==7)
                    {
                        if (balloonGrid[currentY-1][6])
                        {
                            balloonGrid[currentY][7]=b;
                            bHaveToLock=true;
                        }

                    }
                    else
                    {
                        if (balloonGrid[currentY-1][currentX-1] || balloonGrid[currentY-1][currentX])
                        {
                            balloonGrid[currentY][currentX]=b;
                            bHaveToLock=true;
                        }
                    }
                }
                else
                {
                    if (currentX==0)
                    {
                        if (balloonGrid[currentY-1][0])
                        {
                            balloonGrid[currentY][0]=b;
                            bHaveToLock=true;
                        }

                    }
                    else if (currentX==7)
                    {
                        if (balloonGrid[currentY-1][7])
                        {
                            balloonGrid[currentY][6]=b;
                            bHaveToLock=true;
                        }

                    }
                    else
                    {
                        if (balloonGrid[currentY-1][currentX] || balloonGrid[currentY-1][currentX+1])
                        {
                            bHaveToLock=true;
                            balloonGrid[currentY][currentX]=b;
                        }

                    }
                }
            }
            if (bHaveToLock)
            {

                setBalloonPositions();

                b->bIsReleased=false;

                bBalloonLocked=true;

                checkTriplesOrMore();

                removeFreeBalloons();
            }
        }
    }

    //Haal de slechte ervan tussen:
    for (Balloon* b:_balloons)
    {
        if (!b->isAlive())
            _balloons.remove(b);
    }
}

void World::initBalloonGrid()
{
    balloonGrid=new Balloon**[10];
    for (int i=0; i<10; i++)
    {
        balloonGrid[i]=new Balloon*[8];
        for (int j=0; j<8; j++)
        {
            balloonGrid[i][j]=nullptr;
        }
    }
}
void World::disposeBalloonGrid()
{
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (balloonGrid[i][j]!=nullptr)
                delete balloonGrid[i][j];
        }
        delete balloonGrid[i];
    }
    delete balloonGrid;
}
void World::checkTriplesOrMore()
{

    //Beginnen met 3 naast mekaar:
    for (int y=0; y<10; y++)
    {
        for (int x=0; x<6; x++)
        {
            if (balloonGrid[y][x] && balloonGrid[y][x+1] && balloonGrid[y][x+2])
            {
                if ((balloonGrid[y][x])->myBalloonType == (balloonGrid[y][x+1])->myBalloonType && (balloonGrid[y][x])->myBalloonType == (balloonGrid[y][x+2])->myBalloonType)
                {
                    (balloonGrid[y][x])->onPopTheBalloon(true);
                    (balloonGrid[y][x+1])->onPopTheBalloon(true);
                    (balloonGrid[y][x+2])->onPopTheBalloon(true);
                }
            }
        }
    }
}
void World::setBalloonPositions()
{
    for (int currentY=0; currentY<10; currentY++)
    {
        for (int currentX=0; currentX<8; currentX++)
        {
            if (balloonGrid[currentY][currentX])
            {
                if (currentY % 2 == 0)
                {
                    balloonGrid[currentY][currentX]->setPosition(160+currentX*48+24, 64 + 24+ currentY*48);

                }
                else
                {
                    balloonGrid[currentY][currentX]->setPosition(160+((currentX+1)*48), 64 + 24 + currentY*48);
                }
            }
        }
    }
}
void World::removeFreeBalloons()
{


}
