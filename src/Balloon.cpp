#include "Balloon.h"

Balloon::Balloon(std::string tex_id,World& world) :  _world(world)
{
    _sprite.setTexture(Configuration::resEntities[tex_id]);
    _Alive=true;
    //_sprite.setOrigin(texture.getSize().x/2.f,texture.getSize().y);
     if (!tex_id.compare("BlackBalloon"))
        myBalloonType=enBalloonType::Black;
     if (!tex_id.compare("CyanBalloon"))
        myBalloonType=enBalloonType::Cyan;
     if (!tex_id.compare("GreenBalloon"))
        myBalloonType=enBalloonType::Green;
     if (!tex_id.compare("BlueBalloon"))
        myBalloonType=enBalloonType::Blue;
     if (!tex_id.compare("PurpleBalloon"))
        myBalloonType=enBalloonType::Purple;
     if (!tex_id.compare("RedBalloon"))
        myBalloonType=enBalloonType::Red;
     if (!tex_id.compare("WhiteBalloon"))
        myBalloonType=enBalloonType::White;
     if (!tex_id.compare("YellowBalloon"))
        myBalloonType=enBalloonType::Yellow;

    _sprite.setScale(1.5, 1.5);

    for (int x=0; x<12; x++)
    {
        sf::IntRect frame(x*96,0,96,92);
        animExplosion.addFrame(1,frame);
    }
    animator.addAnimation("explode", animExplosion, sf::seconds(2));

    txtScore.setCharacterSize(12);
    txtScore.setOrigin(6,6);
    txtScore.setString("10");
    txtScore.setFillColor(sf::Color::Green);
    txtScore.setFont(Configuration::resFonts["InGameFont"]);

}

Balloon::~Balloon()
{
    //dtor
}
void Balloon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite,states);
    if (bIsExploding)
        target.draw(txtScore, states);
}

void Balloon::update(sf::Time deltaTime)
{
    if (bIsReleased)
    {
        _sprite.move(iMultiplierX*iMoveSpeed*cos(fLaunchedAngle)*deltaTime.asSeconds(),-iMoveSpeed*deltaTime.asSeconds()*sin(fLaunchedAngle));
    }
    if (_sprite.getPosition().x<=160+16  || _sprite.getPosition().x>160+8*48-16)
        iMultiplierX*=-1;

    if (bIsExploding)
    {
        if (tmrExplosion>sf::Time::Zero)
        {
            tmrExplosion-=deltaTime;
            animator.update(deltaTime);
            animator.animate(_sprite);
            txtScore.move(0,-40*deltaTime.asSeconds());
        }
        else
        {
            _Alive=false;
        }
    }
}


void Balloon::processEvents()
{

}

bool Balloon::isAlive()const
{
	return _Alive;
}

void Balloon::onPopTheBalloon(bool bScoreCounts)
{
    if (bScoreCounts)
    {
        if (!bIsExploding)
            _world.iScore+=10;
        std::cout << _world.iScore;
        _sprite.setTexture(Configuration::resVarious["Explosion"]);

        bIsExploding=true;
        _sprite.setScale(0.5,0.5);
        _sprite.setOrigin(24,24);
        animator.playAnimation("explode");
    }
    else
        _Alive = false;
}

void Balloon::releaseBalloon(float LaunchedAngle)
{
    fLaunchedAngle=LaunchedAngle;
    bIsReleased=true;
}
