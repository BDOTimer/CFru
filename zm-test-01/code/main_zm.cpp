#define SFML_STATIC
///----------------------------------------------------------------------------|
/// Подготовка к змейке.
///----------------------------------------------------------------------------:
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

#include "maze_bme.h"

///----------------------------------------------------------------------------|
/// Вспомогательное...
///----------------------------------------------------------------------------:
#define l(a) std::cout  << #a << ": " << (a) << '\n';

template<typename T>
std::ostream& operator<<(std::ostream& o, const sf::Vector2<T>& a)
{   o << "{" << a.x << ", " << a.y << "}"; return o;
}

struct  Map_t :      std::vector<std::string_view>
{       Map_t (const std::vector<std::string_view>& m)
              :      std::vector<std::string_view> (m)
        {
        }
        Map_t() = default;

        void cpy(const std::vector<std::string>& m)
        {   clear(); for(const auto& s : m) push_back(s);
        }

    size_t W() const { return front().size(); }
    size_t H() const { return         size(); }
};

///----------------------------------------------------------------------------|
/// Карты для тестов.
///----------------------------------------------------------------------------:
Map_t map_01
({
    "#########", /// 9 x 3
    "#       #",
    "#########"
});

Map_t map_02
({
    "##########",/// 10 x 4
    "# A      #",
    "#   A   A#",
    "##########"
});

Map_t map_03
({
    "###",       ///  3 x 5
    "# #",
    "# #",
    "# #",
    "###"
});

Map_t map_04
({
    "####",      ///  4 x 6
    "# A#",
    "#  #",
    "#A #",
    "#  #",
    "####"
});

Map_t map_05
({
    "#######################################",
    "#             #                       #",
    "#  A          #                       #",
    "#             # A                     #",
    "#             #        #     ##########",
    "#             ##########     #        #",
    "#                                     #",
    "#          A                          #",
    "#                                     #",
    "#######################################"
});

///----------------------------------------------------------------------------|
/// Все текстуры хранятся здесь + загрузка текстур в примитивы.
///----------------------------------------------------------------------------:
struct  TxtrHolder
{       TxtrHolder()
        {
        }

    static std::string dir(std::string_view name)
    {   return std::string("res_zmei_img/") + name.data();
    }

    ///-----------------------------------------|
    /// Для Sprite.                             |
    ///-----------------------------------------:
    void setTexture2Sprite(sf::Sprite&      o,
                    std::string_view filename,
                    bool             repeate = false)
    {

        m.push_back ( sf::Texture() );

        if( !m.back().loadFromFile(dir(filename)) )
        {   std::cerr << "ERROR: load texture\n"; return;
        }

      //m.back().setRepeated(repeate);
        m.back().setSmooth  (true   );

        o.setTexture(m.back());
        o.setOrigin (64,  64);
    }

    ///-----------------------------------------|
    /// Для RectangleShape.                     |
    ///-----------------------------------------:
    void setTexture2RS(sf::RectangleShape& o,
                       std::string_view    filename,
                       bool                repeate = false)
    {
        m.push_back ( sf::Texture() );

        if( !m.back().loadFromFile(dir(filename)) )
        {   std::cerr << "ERROR: load texture\n"; return;
        }

      //m.back().setRepeated(repeate);
      //m.back().setSmooth  (true   );

        o.setTexture(&m.back() );
    }

    sf::Vector2u getTSize()
    {   if(m.empty())
        {   std::cout << "ERROR:...\n";
        }
        return m.back().getSize();
    }

    std::list<sf::Texture> m;
};

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

            setmap(map_01);

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
    TxtrHolder           txtr;

    ///----------------------|
    /// Текущая карта.       |
    ///----------------------:
    Map_t*     mapp = nullptr;

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

        const Map_t& m = *mapp;

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

        switch (event.key.code)
        {
            case sf::Keyboard::Num1: setmap(map_01); break;
            case sf::Keyboard::Num2: setmap(map_02); break;
            case sf::Keyboard::Num3: setmap(map_03); break;
            case sf::Keyboard::Num4: setmap(map_04); break;
            case sf::Keyboard::Num5: setmap(map_05); break;


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


    void setmap(Map_t& p)
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

    Map_t mazestr;
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

///----------------------------------------------------------------------------|
/// Start.
///----------------------------------------------------------------------------:
int main()
{   srand((unsigned)time(NULL));

    std::cout << "PROGRAMM START ...\n\n";

/// labitinth::BestMordaEver::test();

    std::unique_ptr<Zm_test_01> run(new Zm_test_01);

    std::cout << "\nProgramm FINISHED!\n";
}
