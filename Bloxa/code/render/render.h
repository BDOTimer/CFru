#ifndef RENDER_H
#define RENDER_H
///----------------------------------------------------------------------------|
/// "render.h"
///----------------------------------------------------------------------------:
#include "../global.h"

#include "../_gui/gui.h"
#include "../_redactor/redactor.h"
#include "../_games/games.h"
#include "../_log/logout.h"

#include "fps.h"
#include "resources.h"
#include "cameras.h"


///----------------------------------------------------------------------------|
/// Render.
///----------------------------------------------------------------------------:
struct  Render   : Global
{       Render() :

            window     (sf::VideoMode(Cfg::p->winsize.x,
                                      Cfg::p->winsize.y), "Bloxa-2023"),
            managerCams(window),
            bg         (window),
            blocksWin  (window, managerCams.get(cam::eCAMERA::E_RED )),
            gameWin    (window, managerCams.get(cam::eCAMERA::E_GAME)),
            logWin     (window, managerCams.get(cam::eCAMERA::E_LOG )),
            fps        (        managerCams.get(cam::eCAMERA::E_LOG ))

        {
          //window.setVerticalSyncEnabled(true);
            window.setFramerateLimit     (50  );

            font .loadFromFile  ("sansation.ttf");                ///<-------!!!
          //font .loadFromFile  ("C:/windows/fonts/arial.ttf");   ///<-------!!!

            text.setFont                 (font);
            text.setCharacterSize          (14);
            text.setStyle  (sf::Text::Regular );
            text.setFillColor(sf::Color::White);
            text.setString              ("...");

            Global::pwindow = &window;
        }

    ///-------------------------|
    /// Запус главного цикла.   |
    ///-------------------------:
    void run(){ loop(); }

    ///-------------------------|
    /// Добавить объект.        |
    ///-------------------------:
    void add(obj::IObject* po){ objects.push_back(po); }

    sf::View& get(cam::eCAMERA T){ return managerCams.get(T); }

private:
    sf::RenderWindow  window;
    sf::Font            font;
    sf::Text            text;

    cam::ManagerCameras managerCams;

    res::Background       bg;
    res::BlocksWin blocksWin;
    res::GameWin     gameWin;
    res::LogWin       logWin;
    res::HeaderStr headerStr;

    sf::Clock          clock;
    Fps                  fps;

    void loop()
    {
        sf::Vector2i mouse_pos;

        while (window.isOpen())
        {
            for (sf::Event event; window.pollEvent(event);)
            {
                if (event.type == sf::Event::Closed) window.close();

                ///------------------------------------|
                /// MouseMoved только здесь.           |
                ///------------------------------------:
                if (event.type == sf::Event::MouseMoved)
                {   mouse_pos  =  sf::Mouse::getPosition(window);
                  //process_mouse(mouse_pos);
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2f coord = window.mapPixelToCoords(
                        sf::Vector2i( event.mouseButton.x,
                                      event.mouseButton.y),
                        managerCams.get(cam::eCAMERA::E_GUI)
                    );

                    process_mouse(sf::Vector2i(coord.x, coord.y));
                }
            }

            //window.clear(sf::Color(0,0,64));

                update();
            fps.update();

            managerCams.set(cam::eCAMERA::E_GUI);
            window.draw(bg       );
            window.draw(headerStr);

            managerCams.set(cam::eCAMERA::E_RED);
            window.draw(blocksWin);

            managerCams.set(cam::eCAMERA::E_GAME);
            window.draw(gameWin  );

            for(auto po : objects)
            {   window.draw(*po  );
            }

            managerCams.set(cam::eCAMERA::E_LOG);
            window.draw(logWin);
            window.draw(   fps);

            window.display();

            Global::deltaTime = clock.restart().asSeconds();
        }
    }

    void update()
    {
        for(auto po : objects)
        {   po->update();
        }
    }

    std::vector<obj::IObject*> objects;

    void process_mouse(const sf::Vector2i& mouse_pos)
    {   std::wstring   s(L"Я XY: [");
                       s += std::to_wstring(mouse_pos.x) + L", ";
                       s += std::to_wstring(mouse_pos.y) + L"]" ;
        text.setString(s);
    }
};

#endif // RENDER_H
