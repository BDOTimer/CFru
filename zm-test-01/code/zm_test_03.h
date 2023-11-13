#ifndef ZM_TEST_03_H
#define ZM_TEST_03_H
///----------------------------------------------------------------------------|
///
///----------------------------------------------------------------------------:
#include "spritesloader.h"
#include "maze_bme.h"
#include "snake_02.h"

namespace sprites3
{
    using pmapr_t = std::unique_ptr<sprites::Map4Render_t>;
    using  maze_t = std::unique_ptr<labitinth::Interface>;

    struct  Renderspites : Objects::IObject
    {       Renderspites (      )
            {
                maze = maze_t(labitinth::Interface::make_BestMordaEver());

                name = "Renderspites";
            /// setMap (sprites::map_01);

                loader.setCam(camsp, game.getdisplay().W(),
                                     game.getdisplay().H());

                bg.setTexture2RS (bgbase, "bp-2.jpg");
                bg.setTexture2RS (bgbord, "bp-2.png");
                resize_bg();

                promt.setString(L"Управление: W, S, курсор.");
            }

        sprites::Loader  loader;
        pmapr_t  pmap = nullptr;
        sf::View          camsp;
        sprites::Promt    promt;

        snake::Game        game;
        sf::Clock         clock;


        sprites::TxtrHolder    bg;
        sf::RectangleShape bgbase;
        sf::RectangleShape bgbord;

              float a    = 0.f;
        const float TICK = 0.1f;

        ///------------------------------------------------------------ IObject:
        void update   ()
        {   a += clock.restart().asSeconds();

            if(a > TICK)
            {
                game.loopone();
                a        = 0.f;
            }
        }
    /// void input(const sf::Event&        event) {};
        bool RPControl( std::string_view command,
                        std::vector<float>&  arg) { return false; }
        ///--------------------------------------------------------------------:

        ///-----------------------------------------|
        /// Управление: 0,1,2,3,4,5,R,W,S, курсор.  |
        ///-----------------------------------------:
        const float ZMU = 0.995f;
        const float ZMD = 1.005f;
        void input(const sf::Event& event)
        {
            if (event.type != sf::Event::KeyPressed) return;

            using namespace sprites;

            switch (event.key.code)
            {
                case sf::Keyboard::Num1 : setMap(map_01); break;
                case sf::Keyboard::Num2 : setMap(map_02); break;
                case sf::Keyboard::Num3 : setMap(map_03); break;
                case sf::Keyboard::Num4 : setMap(map_04); break;
                case sf::Keyboard::Num5 : setMap(map_05); break;


                case sf::Keyboard::Up   : camsp.move(  0  ,-15.f); break;
                case sf::Keyboard::Down : camsp.move(  0  , 15.f); break;
                case sf::Keyboard::Left : camsp.move(-15.f,  0  ); break;
                case sf::Keyboard::Right: camsp.move( 15.f,  0  ); break;

                case sf::Keyboard::W    : camsp.zoom(ZMU); break;
                case sf::Keyboard::S    : camsp.zoom(ZMD); break;

                case sf::Keyboard::Num0 :
                case sf::Keyboard::R    : genmaze(); break;

                default: break;
            }
        }

        void setMap(const sprites::Map_t& m)
        {   _setMap(m);
            loader.checked_isbad(*pmap);
            loader.setCam( camsp, pmap->W(), pmap->H());
        }

    private:
        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates  states) const
        {
            auto temp = target.getView();

            target.draw(bgbase, states);
            target.draw(promt , states);

            target.setView(camsp);

            const auto& ts = loader.getTiles();

            sf::Vector2f pos{0, 0};

            for    (size_t y = 0, Y = game.getdisplay().H(); y < Y; ++y)
            {
                    pos   .x = 0;

                for(size_t x = 0, X = game.getdisplay().W(); x < X; ++x)
                {
                    const size_t id = game.getdisplay()[y][x].get();

                    sf::Sprite spr = ts[cfg->fon];

                    spr.move   (pos);
                    target.draw(spr,  states);

                               spr = ts[id];

                    spr.move   (pos);
                    target.draw(spr,  states);

                    pos.x += 128;
                }   pos.y += 128;
            }

            target.setView(temp );
            target.draw   (bgbord, states);
        }

        void _setMap(const sprites::Map_t& m)
        {   pmap = pmapr_t(new sprites::Map4Render_t(m));
        }

        ///----------------------|
        /// Генератор лабиринтов.|
        ///----------------------:
        maze_t maze =     nullptr;

        sprites::Map_t mazestr;
        void  genmaze()
        {
            size_t W = size_t(rand()%60 + 10);
            size_t H = size_t(rand()%30 + 10);

            maze->generator(W, H);

            mazestr.cpy(maze->get_conv2str());

         //mazestr.clear();
         //for(const auto& s : maze.get_conv2str()) mazestr.push_back(s);

            setMap(mazestr);
        }

        ///----------------------|
        /// Установка фона.      |
        ///----------------------:
        void resize_bg()
        {
            const sf::Vector2f SXV{ (float)cfg->winsize.x,
                                    (float)cfg->winsize.y};
            bgbase.setSize    (SXV);
            bgbord.setSize    (SXV);
        }

        static void   test ();
        friend void ::tests();
    };

    ///----------------------|
    /// Тест Renderspites.   |
    ///----------------------:
    void Renderspites::test()
    {
        std::cout << "sprites3::Renderspites::test()\n";

        Renderspites r;

        deb::pause();
    }

    ///------------------------------------------------------------------------|
    /// Runner
    ///------------------------------------------------------------------------:
    struct  Runner
    {       Runner() : window(sf::VideoMode(cfg->winsize.x,
                                            cfg->winsize.y), "zm-test-02")
            {
                cambs = window.getView();

                const auto& sz = cfg->winsize;

                hero.setPosition    ( (sz.x - 700) / 2 ,
                                      (sz.y - 450) / 2 );
                hero.setFillColor   (sf::Color::White  );
                hero.setSize        ({700, 450}        );
                hero.setOutlineColor(sf::Color(222,0,0));
                hero.setOutlineThickness           (5.f);

                font .loadFromFile  ("c:/windows/fonts/georgia.ttf"); ///<---!!!

                text.setFont                (font);
                text.setCharacterSize         (14);
                text.setStyle  (sf::Text::Regular);
                text.setFillColor(sf::Color::Blue);
            }

        sf::RenderWindow window;
        sf::RectangleShape hero;
        sf::Font           font;
        sf::Text           text;

        sf::View          cambs;
        sf::Clock         clock;

        void process_mouse(const sf::Vector2i& mouse_pos)
        {   std::string s("XY: [");
            s += std::to_string(mouse_pos.x) + ", ";
            s += std::to_string(mouse_pos.y) + "]" ;
            text.setString(s);
        }

        void loop()
        {   sf::Vector2i mouse_pos;

            while (window.isOpen())
            {   for (sf::Event event; window.pollEvent(event);)
                {   if (event.type == sf::Event::Closed) window.close();

                    ///------------------------------------|
                    /// MouseMoved только здесь.           |
                    ///------------------------------------:
                    if (event.type == sf::Event::MouseMoved)
                    {   mouse_pos  =  sf::Mouse::getPosition(window);
                        process_mouse(mouse_pos);
                    }

                    for(const auto& o : m) o->input(event);
                }

                window.clear  ();

                window.setView(cambs);
            /// window.draw   (hero);
            /// window.draw   (text);

                for(const auto& o : m) o->update(    );
                for(const auto& o : m) window.draw(*o);

                window.display ();
            }
        }

        std::vector<Objects::IObject*> m;
        void add(   Objects::IObject*  o){ m.push_back(o); }

        static void   test ();
        friend void ::tests();
    };

    ///----------------------|
    /// Тест Runner.         |
    ///----------------------:
    void Runner::test()
    {
        std::cout << "sprites3::Runner::test()\n";

        std::unique_ptr<Runner> run(new Runner);
        Renderspites                       spr ;
                                run->add (&spr);
                                run->    loop();
        deb::pause();
    }
}

#endif // ZM_TEST_03_H
