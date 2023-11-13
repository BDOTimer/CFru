#ifndef ZM_TEST_01_H
#define ZM_TEST_01_H
///----------------------------------------------------------------------------|
/// zm_test_01.h
///----------------------------------------------------------------------------:
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

#include "maze_bme.h"
#include "spritesloader.h"

using maze_t = std::unique_ptr<labitinth::Interface>;

///----------------------------------------------------------------------------|
/// Zm_test_01
///----------------------------------------------------------------------------:
struct  Zm_test_01
{       Zm_test_01() : window(sf::VideoMode(800, 600), "zm-test-01")

        {   maze = maze_t(labitinth::Interface::make_BestMordaEver());

            camui = window.getView();

            l(camui.getSize())

            view.setCenter(0,0);

            txtr.setTexture2RS    (bgbase, "bp-2.jpg");
            txtr.setTexture2RS    (bgbord, "bp-2.png");
            txtr.setTexture2Sprite(field , "grass02-128.jpg");
            txtr.setTexture2Sprite(wall  , "stone01-128.png");
            txtr.setTexture2Sprite(apple , "apple02-128.png");

            setmap(sprites::map_01);

            font.loadFromFile  ("c:/windows/fonts/georgia.ttf"); ///<--------!!!

            text.setFont                  (font);
            text.setCharacterSize           (20);
            text.setStyle    (sf::Text::Regular);
            text.setFillColor(sf::Color::Yellow);
            text.setPosition      (20.f,   20.f);
            text.setString        (promt.data());

            loop();
        }

    ///----------------------|
    /// Все текстуры здесь!  |
    ///----------------------:
    sprites::TxtrHolder  txtr;

    ///----------------------|
    /// Текущая карта.       |
    ///----------------------:
    sprites::Map_t*     mapp = nullptr;

    sf::RenderWindow   window;
    sf::RectangleShape bgbase;
    sf::RectangleShape bgbord;
    sf::Sprite          field;
    sf::Sprite           wall;
    sf::Sprite          apple;
    sf::Font             font;
    sf::Text             text;

    sf::View             view;
    sf::View            cambg;
    sf::View            camui;

    ///----------------------|
    /// Генератор лабиринтов.|
    ///----------------------:
    maze_t maze =     nullptr;

    std::wstring_view promt{L"Управление: 0, 1, 2, 3, 4, 5, R, W, S, курсор."};

    void process_mouse(const sf::Vector2i& mouse_pos)
    {   std::string    s("XY:[");
                       s += std::to_string(mouse_pos.x) + ", ";
                       s += std::to_string(mouse_pos.y) + "]" ;
        text.setString(s);
    }

    ///-----------------------------------------|
    /// Главный луп.                            |
    ///-----------------------------------------:
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

                ///------------------------------------|
                /// Управляем полем.                   |
                ///------------------------------------:
                input(event);
            }

            window.clear        ();

            window.setView (cambg);
            window.draw   (bgbase);

            window.setView (camui);
            window.draw     (text);

            window.setView  (view);
            render_field        ();

            window.setView (cambg);
            window.draw   (bgbord);

            window.display      ();
        }
    }

    ///-----------------------------------------|
    /// Рисуем поле.                            |
    ///-----------------------------------------:
    void render_field()
    {
        if(nullptr == mapp) return;

        sf::Sprite sp = field;
        sf::Sprite wl = wall ;
        sf::Sprite ap = apple;

        const sprites::Map_t& m = *mapp;

        const auto W  = mapp->W();
        const auto H  = mapp->H();
        const auto WB =-128.f * W;

        for    (size_t y = 0; y < H; ++y)
        {   for(size_t x = 0; x < W; ++x)
            {
                window.draw  (sp);
                     if(m[y][x] == '#') window.draw(wl);
                else if(m[y][x] == 'A') window.draw(ap);
                sp.move(128,   0);
                wl.move(128,   0);
                ap.move(128,   0);
            }   sp.move( WB, 128);
                wl.move( WB, 128);
                ap.move( WB, 128);
        }
    }

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
            case sf::Keyboard::Num1 : setmap(map_01); break;
            case sf::Keyboard::Num2 : setmap(map_02); break;
            case sf::Keyboard::Num3 : setmap(map_03); break;
            case sf::Keyboard::Num4 : setmap(map_04); break;
            case sf::Keyboard::Num5 : setmap(map_05); break;


            case sf::Keyboard::Up   : view.move( 0  ,-5.f); break;
            case sf::Keyboard::Down : view.move( 0  , 5.f); break;
            case sf::Keyboard::Left : view.move(-5.f, 0  ); break;
            case sf::Keyboard::Right: view.move( 5.f, 0  ); break;

            case sf::Keyboard::W    : view.zoom(ZMU); break;
            case sf::Keyboard::S    : view.zoom(ZMD); break;

            case sf::Keyboard::Num0 :
            case sf::Keyboard::R    : genmaze(); break;

            default: break;
        }
    }


    void setmap(sprites::Map_t& p)
    {   mapp = &p;

        const auto W = mapp->W();
        const auto H = mapp->H();

        field.setPosition(0, 0);
        wall .setPosition(0, 0);
        apple.setPosition(0, 0);

        const auto& SZ = window.getSize();

        const float k1 = float(SZ.x) / SZ.y;

        view.setCenter(0,0);

        if(W  >  H) view.setSize((128.f * W)     , (128.f * W) / k1);
        else        view.setSize((128.f * H) * k1, (128.f * H)     );

        const float WM = -(128.f * W) / 2 + 64;
        const float HM = -(128.f * H) / 2 + 64;

        field.move( WM, HM);
        wall .move( WM, HM);
        apple.move( WM, HM);

        cambg = view;

        resize_bg();
    }

    void resize_bg()
    {
        const sf::Vector2f& SZV = view.getSize();
        bgbase.setSize     (SZV);
        bgbord.setSize     (SZV);

        const float W2 = SZV.x / 2;
        const float H2 = SZV.y / 2;

        bgbase.setOrigin ( W2, H2);
        bgbord.setOrigin ( W2, H2);
    }

    sprites::Map_t mazestr;
    void  genmaze()
    {
        size_t W = size_t(rand()%60 + 10);
        size_t H = size_t(rand()%30 + 10);

        maze->generator(W, H);

        mazestr.cpy(maze->get_conv2str());

      //mazestr.clear();
      //for(const auto& s : maze.get_conv2str()) mazestr.push_back(s);

        setmap(mazestr);
    }
};

#endif // ZM_TEST_01_H
