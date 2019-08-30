#include "Program.h"

Program::Program():_window(sf::VideoMode(600, 600), "Puzzle Bobble Level Editor")
{
    createGui();

    grid=new sf::Sprite**[10];
    colors=new enBalloonType*[10];
    for (int y=0; y<10; y++)
    {
        grid[y]=new sf::Sprite*[8];
        colors[y]=new enBalloonType[8];
        for (int x=0; x<8; x++)
        {
            grid[y][x]=new sf::Sprite();
            grid[y][x]->setPosition(240+36*x, 40+36*y);
            grid[y][x]->setTexture(Configuration::resEntities["Empty"]);
            colors[y][x]=enBalloonType::Empty;
        }
    }

    currentColor.setFillColor(sf::Color::Black);
    currentColor.setSize(sf::Vector2f(10,10));
    currentColor.setPosition(400,440);
}

Program::~Program()
{
    //dtor
}
void Program::run(int frames_per_second)
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

void Program::processEvents()
{
    sf::Event event;
    while(_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            //_gameStatus=StatusExit;
            _window.close();
        }

        if (event.type==sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button==sf::Mouse::Left)
            {
                int xindex=(event.mouseButton.x-240)/36;
                int yindex=(event.mouseButton.y-40)/36;
                if (xindex>=0 && yindex>=0 && xindex<8 && yindex<10)
                {
                    colors[yindex][xindex]=selectedType;
                    switch (selectedType)
                    {
                    case enBalloonType::Black:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["BlackBalloon"]);
                        break;
                    case enBalloonType::Blue:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["BlueBalloon"]);
                        break;
                    case enBalloonType::Cyan:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["CyanBalloon"]);
                        break;
                    case enBalloonType::Green:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["GreenBalloon"]);
                        break;
                    case enBalloonType::Purple:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["PurpleBalloon"]);
                        break;
                    case enBalloonType::Red:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["RedBalloon"]);
                        break;
                    case enBalloonType::White:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["WhiteBalloon"]);
                        break;
                    case enBalloonType::Yellow:
                        grid[yindex][xindex]->setTexture(Configuration::resEntities["YellowBalloon"]);
                        break;
                    }

                }

            }
        }
        gui->handleEvent(event);
    }
}
void Program::update (sf::Time deltaTime)
{
    gui->updateTime(deltaTime);

    switch (selectedType)
    {
    case enBalloonType::Black:
        currentColor.setFillColor(sf::Color::Black);
        break;
    case enBalloonType::Blue:
        currentColor.setFillColor(sf::Color::Blue);
        break;
    case enBalloonType::Cyan:
        currentColor.setFillColor(sf::Color::Cyan);
        break;
    case enBalloonType::Green:
        currentColor.setFillColor(sf::Color::Green);
        break;
    case enBalloonType::Purple:
        currentColor.setFillColor(sf::Color::Magenta);
        break;
    case enBalloonType::Red:
        currentColor.setFillColor(sf::Color::Red);
        break;
    case enBalloonType::White:
        currentColor.setFillColor(sf::Color::White);
        break;
    case enBalloonType::Yellow:
        currentColor.setFillColor(sf::Color::Yellow);
        break;
    }
}
void Program::render()
{
    _window.clear(sf::Color::White);

    gui->draw();

    for (int y=0; y<10; y++)
    {
        for (int x=0; x<8; x++)
        {
            _window.draw(*grid[y][x]);
        }
    }

    _window.draw(currentColor);

    _window.display();
}
void Program::createGui()
{
    gui=new tgui::Gui(_window);
    gui->loadWidgetsFromFile("PBLevelEditor.txt");

    gui->get("btnBlackBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::Black;
                                                   });
    gui->get("btnBlueBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::Blue;
                                                   });
    gui->get("btnCyanBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::Cyan;
                                                   });
    gui->get("btnGreenBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::Green;
                                                   });
    gui->get("btnPurpleBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::Purple;
                                                   });
    gui->get("btnRedBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::Red;
                                                   });
    gui->get("btnWhiteBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::White;
                                                   });
    gui->get("btnYellowBalloon")->connect("pressed", [&](){

                                                        selectedType=enBalloonType::Yellow;
                                                   });
    gui->get("btnSaveFile")->connect("pressed", [&](){
                                        if (gui->get<tgui::EditBox>("edFileName")->getText().toAnsiString().compare(""))
                                        {
                                            j["balloons"]=nlohmann::json::array();
                                            for (int y=0; y<10; y++)
                                            {
                                                for (int x=0; x<8; x++)
                                                {
                                                    nlohmann::json balloon;

                                                    if (colors[y][x]!=enBalloonType::Empty)
                                                    {

                                                        balloon["myX"]=x;
                                                        balloon["myY"]=y;
                                                        switch (colors[y][x])
                                                        {
                                                        case enBalloonType::Black:
                                                            balloon["myColor"]="BlackBalloon";
                                                            break;
                                                        case enBalloonType::Blue:
                                                            balloon["myColor"]="BlueBalloon";
                                                            break;
                                                        case enBalloonType::Cyan:
                                                            balloon["myColor"]="CyanBalloon";
                                                            break;
                                                        case enBalloonType::Purple:
                                                            balloon["myColor"]="PurpleBalloon";
                                                            break;
                                                        case enBalloonType::Green:
                                                            balloon["myColor"]="GreenBalloon";
                                                            break;
                                                        case enBalloonType::Yellow:
                                                            balloon["myColor"]="YellowBalloon";
                                                            break;
                                                        case enBalloonType::White:
                                                            balloon["myColor"]="WhiteBalloon";
                                                            break;
                                                        case enBalloonType::Red:
                                                            balloon["myColor"]="RedBalloon";
                                                            break;
                                                        }
                                                    }
                                                    if (colors[y][x]!=enBalloonType::Empty)
                                                        j["balloons"].push_back(balloon);
                                                }
                                            }
                                            std::ofstream of(gui->get<tgui::EditBox>("edFileName")->getText().toAnsiString());

                                            of << j;
                                        }
                                     });
    gui->get("btnLoadFile")->connect("pressed", [&](){
                                        if (gui->get<tgui::EditBox>("edFileName")->getText().toAnsiString().compare(""))
                                        {
                                            std::ifstream infile(gui->get<tgui::EditBox>("edFileName")->getText().toAnsiString());
                                            j << infile;

                                             for (nlohmann::json::iterator it = j["balloons"].begin(); it != j["balloons"].end(); ++it) {

                                                auto balloon=(*it);

                                                int myX=balloon["myX"].get<int>();
                                                int myY=balloon["myY"].get<int>();
                                                std::string myColor=balloon["myColor"].get<std::string>();
                                                enBalloonType myType;
                                                if (!myColor.compare("BlackBalloon"))
                                                    myType=enBalloonType::Black;
                                                if (!myColor.compare("BlueBalloon"))
                                                    myType=enBalloonType::Blue;
                                                if (!myColor.compare("CyanBalloon"))
                                                    myType=enBalloonType::Cyan;
                                                if (!myColor.compare("GreenBalloon"))
                                                    myType=enBalloonType::Green;
                                                if (!myColor.compare("PurpleBalloon"))
                                                    myType=enBalloonType::Purple;
                                                if (!myColor.compare("RedBalloon"))
                                                    myType=enBalloonType::Red;
                                                if (!myColor.compare("WhiteBalloon"))
                                                    myType=enBalloonType::White;
                                                if (!myColor.compare("YellowBalloon"))
                                                    myType=enBalloonType::Yellow;
                                                colors[myY][myX]=myType;
                                                grid[myY][myX]->setTexture(Configuration::resEntities[myColor]);
                                            }
                                        }
                                      });
}
