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
            int currentY=(int)(b->_sprite.getPosition().y-64+24)/48;
            if (b->_sprite.getPosition().y-(((currentY+1)*48)+64-24)<2)
            {
                int currentX=0;
                if (currentY % 2 == 0)
                {

                    currentX=(int)(b->_sprite.getPosition().x-160-24)/48;
                   /* float diff1=160 + 24 + currentX*48 - ((b->_sprite.getPosition().x -160-24)/48);

                    if (diff1>2)
                        currentX++;*/

                }
                else
                {
                    currentX=(int)(b->_sprite.getPosition().x-160)/48;
                    /*float diff1=160 + currentX*48 - ((b->_sprite.getPosition().x -160)/48);

                    if (diff1<2)
                        currentX--;*/
                }

                if (currentY==0)
                {
                    if (balloonGrid[0][currentX])
                    {
                        lockBalloon(b, currentX+1, 0);
                    }
                    else
                    {
                        lockBalloon(b, currentX, 0);
                    }

                }
                else
                {
                    if (bHaveToLock(currentX, currentY))
                    {
                        if (currentY % 2 == 0)
                            lockBalloon(b, currentX, currentY);
                        else
                            lockBalloon(b, currentX-1, currentY);
                    }
                }
            }
        }
    }

    setBalloonPositions();

    checkTriplesOrMore();

    removeFreeBalloons();
    //Haal de slechte ervan tussen:



    for (int y=0; y<10; y++)
    {
        for (int x=0; x<8; x++)
        {
            if (balloonGrid[y][x])
            {
                if (!balloonGrid[y][x]->isAlive())
                {
                    _balloons.remove(balloonGrid[y][x]);
                    delete balloonGrid[y][x];
                    balloonGrid[y][x]=nullptr;
                }
            }
        }
    }

}
void World::lockBalloon(Balloon* b, int myXPos, int myYPos)
{
    b->myXPos=myXPos;
    b->myYPos=myYPos;

    if (balloonGrid[myYPos][myXPos])
    {
        if (myYPos % 2 == 0)
        {
            lockBalloon(b, myXPos-1, myYPos);
            return;
        }
        else
        {
            lockBalloon(b, myXPos+1, myYPos);
            return;
        }
    }
    else
        balloonGrid[myYPos][myXPos]=b;

    b->bIsReleased=false;

    bBalloonLocked=true;
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
                if (!balloonGrid[y][x]->bIsExploding && !balloonGrid[y][x+1]->bIsExploding && !balloonGrid[y][x+2]->bIsExploding)
                    if ((balloonGrid[y][x])->myBalloonType == (balloonGrid[y][x+1])->myBalloonType && (balloonGrid[y][x])->myBalloonType == (balloonGrid[y][x+2])->myBalloonType)
                    {
                        if (!balloonGrid[y][x]->bIsExploding)
                            (balloonGrid[y][x])->onPopTheBalloon(true);
                        if (!balloonGrid[y][x+1]->bIsExploding)
                            (balloonGrid[y][x+1])->onPopTheBalloon(true);
                        if (!balloonGrid[y][x+2]->bIsExploding)
                            (balloonGrid[y][x+2])->onPopTheBalloon(true);
                    }
            }
        }
    }

    //Check 2+1:

    for (int y=0; y<10; y++)
    {
        for (int x=0; x<7; x++)
        {
            if (y % 2 == 0)
            {
                if (balloonGrid[y][x] && balloonGrid[y][x+1] && balloonGrid[y+1][x])
                {
                    if (balloonGrid[y][x]->myBalloonType==balloonGrid[y][x+1]->myBalloonType && balloonGrid[y][x+1]->myBalloonType==balloonGrid[y+1][x]->myBalloonType)
                    {
                        if (!balloonGrid[y][x]->bIsExploding)
                            (balloonGrid[y][x])->onPopTheBalloon(true);
                        if (!balloonGrid[y][x+1]->bIsExploding)
                            (balloonGrid[y][x+1])->onPopTheBalloon(true);
                        if (!balloonGrid[y+1][x]->bIsExploding)
                            (balloonGrid[y+1][x])->onPopTheBalloon(true);
                    }
                }
            }
            else
            {
                if (balloonGrid[y][x] && balloonGrid[y][x+1] && balloonGrid[y+1][x+1])
                {
                    if (balloonGrid[y][x]->myBalloonType==balloonGrid[y][x+1]->myBalloonType && balloonGrid[y][x+1]->myBalloonType==balloonGrid[y+1][x+1]->myBalloonType)
                    {
                        if (!balloonGrid[y][x]->bIsExploding)
                            (balloonGrid[y][x])->onPopTheBalloon(true);
                        if (!balloonGrid[y][x+1]->bIsExploding)
                            (balloonGrid[y][x+1])->onPopTheBalloon(true);
                        if (!balloonGrid[y+1][x+1]->bIsExploding)
                            (balloonGrid[y+1][x+1])->onPopTheBalloon(true);
                    }
                }
            }
        }
    }

    //Check 1+2:
    for (int y=0; y<10; y++)
    {
        for (int x=0; x<8; x++)
        {
            if (y%2==0)
            {
                if (x!=0)
                {
                    if (balloonGrid[y][x] && balloonGrid[y+1][x] && balloonGrid[y+1][x-1])
                    {
                        if (balloonGrid[y][x]->myBalloonType==balloonGrid[y+1][x]->myBalloonType && balloonGrid[y+1][x]->myBalloonType==balloonGrid[y+1][x-1]->myBalloonType)
                        {
                            if (!balloonGrid[y][x]->bIsExploding)
                                (balloonGrid[y][x])->onPopTheBalloon(true);
                            if (!balloonGrid[y+1][x]->bIsExploding)
                                (balloonGrid[y+1][x])->onPopTheBalloon(true);
                            if (!balloonGrid[y+1][x-1]->bIsExploding)
                                (balloonGrid[y+1][x-1])->onPopTheBalloon(true);
                        }
                    }
                }
            }
            else
            {
                if (x!=7)
                {
                    if (balloonGrid[y][x] && balloonGrid[y+1][x] && balloonGrid[y+1][x+1])
                    {
                        if (balloonGrid[y][x]->myBalloonType==balloonGrid[y+1][x]->myBalloonType && balloonGrid[y+1][x]->myBalloonType==balloonGrid[y+1][x+1]->myBalloonType)
                        {
                            if (!balloonGrid[y][x]->bIsExploding)
                                (balloonGrid[y][x])->onPopTheBalloon(true);
                            if (!balloonGrid[y+1][x]->bIsExploding)
                                (balloonGrid[y+1][x])->onPopTheBalloon(true);
                            if (!balloonGrid[y+1][x+1]->bIsExploding)
                                (balloonGrid[y+1][x+1])->onPopTheBalloon(true);
                        }
                    }
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
    for (int y=9; y>0; y--)
    {
        for (int x=0; x<8; x++)
        {
            if (balloonGrid[y][x])
            {
                if (y % 2 == 0)
                {
                     if (x==0)
                        {
                            if (!balloonGrid[y-1][x])
                            {
                                balloonGrid[y][x]->onPopTheBalloon(false);
                            }
                        }
                        else
                        {
                            if (!balloonGrid[y-1][x] && !balloonGrid[y-1][x-1])
                            {
                                balloonGrid[y][x]->onPopTheBalloon(false);
                            }
                        }
                }
                else
                {
                    if (x==7)
                    {
                        if (!balloonGrid[y-1][x])
                        {
                            balloonGrid[y][x]->onPopTheBalloon(false);
                        }
                    }
                    else
                    {
                        if (!balloonGrid[y-1][x+1] && !balloonGrid[y-1][x])
                        {
                            balloonGrid[y][x]->onPopTheBalloon(false);
                        }
                    }
                }
            }
        }
    }
}
bool World::bHaveToLock(int XPos, int YPos)
{
    if (YPos==0)
        return true;
    if (YPos % 2 == 0)
    {
        if (XPos==0)
        {
            if (balloonGrid[YPos-1][XPos])
                if (!balloonGrid[YPos-1][XPos]->bIsExploding)
                    return true;
        }
        else
        {
            if (balloonGrid[YPos-1][XPos-1])
            {
                if (balloonGrid[YPos-1][XPos-1])
                    if (!balloonGrid[YPos-1][XPos-1]->bIsExploding)
                        return true;

            }

        }
    }

    if (YPos % 2 == 1)
    {
        if (XPos==7)
        {
            if (balloonGrid[YPos-1][XPos])
                if (!balloonGrid[YPos-1][XPos]->bIsExploding)
                    return true;
        }
        else
        {
            if (balloonGrid[YPos-1][XPos] )
            {
                if (balloonGrid[YPos-1][XPos])
                    if (!balloonGrid[YPos-1][XPos]->bIsExploding)
                        return true;

            }
        }
    }

    return false;
}

void World::parseLevel(std::string strFilename)
{
    nlohmann::json j;
    std::ifstream i(strFilename);
    i >> j;

    for (nlohmann::json::iterator it = j["balloons"].begin(); it != j["balloons"].end(); ++it) {

        auto balloon=(*it);
        Balloon* bal=new Balloon(balloon["myColor"].get<std::string>(), *this);
        bal->myXPos=balloon["myX"].get<int>();
        bal->myYPos=balloon["myY"].get<int>();
        bal->_sprite.setOrigin(16,16);

        balloonGrid[bal->myYPos][bal->myXPos]=bal;
        addBalloon(bal);
    }

    setBalloonPositions();
}
bool World::isColorPresent(std::string testColor)
{
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (balloonGrid[i][j])
            {
                switch (balloonGrid[i][j]->myBalloonType)
                {
                case Balloon::enBalloonType::Black:
                    if (!testColor.compare("BlackBalloon"))
                        return true;
                    break;
                case Balloon::enBalloonType::Blue:
                    if (!testColor.compare("BlueBalloon"))
                        return true;
                    break;
                case Balloon::enBalloonType::Cyan:
                    if (!testColor.compare("CyanBalloon"))
                        return true;
                    break;
                case Balloon::enBalloonType::Green:
                    if (!testColor.compare("GreenBalloon"))
                        return true;
                    break;
                case Balloon::enBalloonType::Purple:
                    if (!testColor.compare("PurpleBalloon"))
                        return true;
                    break;
                case Balloon::enBalloonType::Red:
                    if (!testColor.compare("RedBalloon"))
                        return true;
                    break;
                case Balloon::enBalloonType::Yellow:
                    if (!testColor.compare("YellowBalloon"))
                        return true;
                    break;
                case Balloon::enBalloonType::White:
                    if (!testColor.compare("WhiteBalloon"))
                        return true;
                    break;
                }
            }
        }
    }
    return false;
}
