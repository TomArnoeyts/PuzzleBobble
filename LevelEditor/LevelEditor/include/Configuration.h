#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
class Configuration
{
    public:
        Configuration() = delete;
        Configuration(const Configuration& other) = delete;
        Configuration& operator=(const Configuration& other) = delete;

        static thor::ResourceHolder <sf::Texture, std::string> resEntities;

        static void initialize();
        static void release();
    protected:

    private:
};

#endif // CONFIGURATION_H
