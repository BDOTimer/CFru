#define SFML_STATIC
///----------------------------------------------------------------------------|
/// ...
/// отключить консольное окно: -mwindows
///----------------------------------------------------------------------------:
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Objects
{
    ///-------------------------|
    /// Интерфейс объекта.      |--------------------------------------------!!!
    ///-------------------------:
    struct      IObject : sf::Drawable
    {   virtual~IObject(){}
        virtual void update   (                        ) = 0;
        virtual bool RPControl(std::string_view command,
                               std::vector<float>& arg ) = 0;
        virtual void input(const sf::Event&       event) = 0;

        std::string_view     name;

    private:
    };
}

///----------------------------------------------------------------------------|
/// ...
///----------------------------------------------------------------------------:
const int compassSize = 400;

struct  Compas   : Objects::IObject
{       Compas() :
            circle(compassSize / 2),
            center(18)
        {
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(2);
            circle.setOutlineColor(sf::Color::Black);
            circle.setOrigin(compassSize / 2, compassSize / 2);
            circle.setPosition(compassSize / 2, compassSize / 2);

            //////////////////
            northTriangle.setPointCount(3);
            northTriangle.setPoint(
                0,
                sf::Vector2f(compassSize / 2, compassSize / 2 - compassSize / 4 - 10));
            northTriangle.setPoint(
                1, sf::Vector2f(compassSize / 2 - 15, compassSize / 2 - 10));
            northTriangle.setPoint(
                2, sf::Vector2f(compassSize / 2 + 15, compassSize / 2 - 10));
            northTriangle.setFillColor(sf::Color::Red);

            ///////////////////
            eastTriangle.setPointCount(3);
            eastTriangle.setPoint(
                0,
                sf::Vector2f(compassSize / 2 + compassSize / 4 + 10, compassSize / 2));
            eastTriangle.setPoint(
                1, sf::Vector2f(compassSize / 2 + 10, compassSize / 2 - 15));
            eastTriangle.setPoint(
                2, sf::Vector2f(compassSize / 2 + 10, compassSize / 2 + 15));
            eastTriangle.setFillColor(sf::Color::Green);

            //////////////////
            southTriangle.setPointCount(3);
            southTriangle.setPoint(
                0,
                sf::Vector2f(compassSize / 2, compassSize / 2 + compassSize / 4 + 10));
            southTriangle.setPoint(
                1, sf::Vector2f(compassSize / 2 - 15, compassSize / 2 + 10));
            southTriangle.setPoint(
                2, sf::Vector2f(compassSize / 2 + 15, compassSize / 2 + 10));
            southTriangle.setFillColor(sf::Color::Blue);

            //////////////////
            westTriangle.setPointCount(3);
            westTriangle.setPoint(
                0,
                sf::Vector2f(compassSize / 2 - compassSize / 4 - 10, compassSize / 2));
            westTriangle.setPoint(
                1, sf::Vector2f(compassSize / 2 - 10, compassSize / 2 - 15));
            westTriangle.setPoint(
                2, sf::Vector2f(compassSize / 2 - 10, compassSize / 2 + 15));
            westTriangle.setFillColor(sf::Color::Magenta);

            //////////////////
            center.setFillColor(sf::Color::Black);
            center.setOrigin(13, 13);
            center.setPosition(compassSize / 2 - 5, compassSize / 2 - 5);

            //loop();
        }

    sf::CircleShape  circle       ;
    sf::ConvexShape  northTriangle;
    sf::ConvexShape  eastTriangle ;
    sf::ConvexShape  southTriangle;
    sf::ConvexShape  westTriangle ;
    sf::CircleShape  center       ;

    void update   (                        ){}
    bool RPControl(std::string_view command,
                  std::vector<float>& arg ) { return false;}
    void input(const sf::Event&       event){}

    ///-----------------|
    /// На рендер.      |
    ///-----------------:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates  states) const
    {
        target.draw(circle       , states);
        target.draw(northTriangle, states);
        target.draw(eastTriangle , states);
        target.draw(southTriangle, states);
        target.draw(westTriangle , states);
        target.draw(center       , states);
    }
};

///----------------------------------------------------------------------------|
/// Run
///----------------------------------------------------------------------------:
struct  Run
{   Run() : window(sf::VideoMode(800, 600), "Lesson")

    {   hero.setPosition    ( 50, 100          );
        hero.setFillColor   (sf::Color(0,128,0));
        hero.setSize        ({700, 450}        );
        hero.setOutlineColor(sf::Color(222,0,0));
        hero.setOutlineThickness           (5.f);

        font .loadFromFile  ("c:/windows/fonts/georgia.ttf"); ///<-------!!!

        text.setFont                (font);
        text.setCharacterSize         (50);
        text.setStyle  (sf::Text::Regular);
        text.setFillColor(sf::Color::Blue);

    }

    sf::RenderWindow window;
    sf::RectangleShape hero;
    sf::Font           font;
    sf::Text           text;

    void process_mouse(const sf::Vector2i& mouse_pos)
    {   std::string s("XY = {");
        s += std::to_string(mouse_pos.x) + ", ";
        s += std::to_string(mouse_pos.y) + "}" ;
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
            }

            window.clear   ();
            window.draw(hero);
            window.draw(text);

            for(const auto& o : m) window.draw(*o);

            window.display ();
        }
    }

    std::vector<Objects::IObject*> m;
    void add(Objects::IObject* o){m.push_back(o);}
};

///----------------------------------------------------------------------------|
/// Start.
///----------------------------------------------------------------------------:
int main()
{   std::unique_ptr<Run>      run(new Run);
    std::unique_ptr<Compas>   o  (new Compas);
                              run->add(o.get());
                              run->loop();
}
