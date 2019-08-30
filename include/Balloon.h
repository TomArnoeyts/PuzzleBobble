#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <World.h>
#include <Configuration.h>
#include <iostream>
#include <Thor/Animations.hpp>
class World;
class Balloon : public sf::Drawable
{
    public:
        Balloon(std::string textureId,World& world);
        virtual ~Balloon();
        Balloon(const Balloon& other) = delete;
        Balloon& operator=(const Balloon& other) = delete;

        template<typename ... Args>
		void setPosition(Args&& ... args)
		{
			_sprite.setPosition(std::forward<Args>(args)...);
			if (!bIsExploding)
                txtScore.setPosition(std::forward<Args>(args)...);
		}

		virtual bool isAlive()const;

        virtual void update(sf::Time deltaTime);
        virtual void processEvents();
		virtual void onPopTheBalloon(bool bScoreCounts);

		sf::Sprite _sprite;

		enum enBalloonType {Black, Blue, Cyan, Green, Purple, Red, White, Yellow};

		enBalloonType myBalloonType;

		void releaseBalloon(float LaunchedAngle);

		bool bIsReleased=false;

		int myXPos=0, myYPos=0;

		bool bIsExploding=false;

    protected:
        World& _world;

        bool _Alive;
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        int iMoveSpeed=500;


        float fLaunchedAngle;

        int iMultiplierX=1;

        thor::FrameAnimation animExplosion;

        thor::Animator<sf::Sprite, std::string> animator;

        sf::Time tmrExplosion=sf::seconds(2);

        sf::Text txtScore;

        bool bIsFalling=false;
};

#endif // ENTITY_H
