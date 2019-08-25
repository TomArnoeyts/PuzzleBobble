#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <World.h>
#include <Configuration.h>
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
		}

		virtual bool isAlive()const;

        virtual void update(sf::Time deltaTime);
        virtual void processEvents();
		virtual void onDestroy();

		sf::Sprite _sprite;


    protected:
        World& _world;

        bool _Alive;
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // ENTITY_H
