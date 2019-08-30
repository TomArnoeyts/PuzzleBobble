#ifndef PROGRAM_H
#define PROGRAM_H
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <nlohmann/json.hpp>
#include <Configuration.h>

#include <fstream>
class Program
{
    public:

        Program();
        Program(const Program& other)=delete;
        Program& operator=(const Program& other)=delete;
        ~Program();
        void run(int frames_per_second);

        enum enBalloonType {Black, Blue, Cyan, Green, Purple, Red, White, Yellow, Empty};

        enBalloonType selectedType=enBalloonType::Blue;

    protected:

    private:
        sf::RenderWindow _window;

        void processEvents();
        void update (sf::Time deltaTime);
        void render();

        tgui::Gui* gui;

        nlohmann::json j;

        sf::Sprite*** grid;
        enBalloonType** colors;

        sf::RectangleShape currentColor;

        void createGui();
};

#endif // PROGRAM_H
