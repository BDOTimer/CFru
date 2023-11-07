#ifndef TEST_CLOCK_01_H
#define TEST_CLOCK_01_H
///----------------------------------------------------------------------------|
/// "Test_Clock_01.h"
///----------------------------------------------------------------------------:
#include "../../../global.h"

namespace Objects
{
    ///------------------------------------------------------------------------|
    /// Тестовый объект Часы.
    ///------------------------------------------------------------------------:
    struct  Test_Clock_01 : IObject, Global
    {       Test_Clock_01(sf::View& v) : view(v)
            {
                name = "Test_Clock_01";

                ///---------------------------------|
                /// Секундная стрелка.              |
                ///---------------------------------:
                s.setSize   (sf::Vector2f(4,    -62));
                s.setFillColor   (sf::Color(255,0,0,128));
                s.setOutlineColor(sf::Color(128,128,128));
                s.setOutlineThickness          (1.f);
                s.setOrigin                    (2,-5);

                ///---------------------------------|
                /// Минутная стрелка.               |
                ///---------------------------------:
                m.setSize       (sf::Vector2f(35,6));
                //o.setPosition(0, 0);
                m.setFillColor  (sf::Color(0,196,0));
                m.setOutlineColor(sf::Color::Black );
                m.setOutlineThickness          (1.f);
                m.setOrigin                    (4,3);

                ///---------------------------------|
                /// Часовая стрелка.                |
                ///---------------------------------:
                h.setSize      (sf::Vector2f(25,12));
                //o.setPosition(0, 0);
                h.setFillColor   (sf::Color(0,128,0));
                h.setOutlineColor(sf::Color::Black );
                h.setOutlineThickness          (1.f);
                h.setOrigin                    (6,6);

                ///---------------------------------|
                /// Циферблатный круг.              |
                ///---------------------------------:
                c.setRadius                   (40.f);
                c.setPosition              (-40,-40);
                c.setFillColor (sf::Color(64,64,0));
                c.setOutlineColor(sf::Color::Blue  );
                c.setOutlineThickness          (1.f);

                ///---------------------------------|
                /// Часовые метки(12 штук).         |
                ///---------------------------------:
                float angle = 0.f;

                for(auto& e : o)
                {   e.setRadius                      (3);
                    e.setOrigin                    (3,3);
                    e.setFillColor   (sf::Color::White );
                    e.setOutlineColor(sf::Color::Blue  );
                    e.setOutlineThickness            (1);

                    e.setPosition( 50 * sinf(angle),
                                   50 * cosf(angle));

                    angle += M_PI / 6;
                }
            }

        // TODO:1 ...
        float speed = 0.5f;
        float aaa   = 0.2f;

        ///-----------------------------------------|
        /// Установить все стрелки в положение.     |
        ///-----------------------------------------:
        void        update()
        {   ///-------------------------------------|
            /// Если был секундный тик.             |
            ///-------------------------------------:
            if(time.update())
            {   s.setRotation(time.sec () *  6     );
                m.setRotation(time.min () *  6 - 90);
                h.setRotation(time.hour() * 30 - 90);
            }

            // TODO1 ...
            view.zoom(1.f - 0.004 * sinf(aaa));
            aaa += speed * Global::deltaTime  ;
        }

        ///-----------------------------------------|
        /// Команды поступающие из моска.           |
        ///-----------------------------------------:
        bool RPControl(std::string_view command, std::vector<float>& arg)
        {
            /// TODO2 ...

            l(command)

            return false;
        }
        void input(const sf::Event& event){}

    private:
        ///-----------------|
        /// Камера.         |
        ///-----------------:
        sf::View&       view;
        ///-----------------|
        /// Стрелки.        |
        ///-----------------:
        sf::RectangleShape s;
        sf::RectangleShape m;
        sf::RectangleShape h;
        ///-----------------|
        /// Циферблат.      |
        ///-----------------:
        sf::CircleShape    c;
        sf::CircleShape    o[12];

        ///-----------------|
        /// Время системы.  |
        ///-----------------:
        myl::Time_t     time;

        ///-----------------|
        /// На рендер.      |
        ///-----------------:
        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates  states) const
        {
            for(const auto& e : o) target.draw(e, states);

            target.draw(c, states);
            target.draw(h, states);
            target.draw(m, states);
            target.draw(s, states);
        }
    };
}


#endif // TEST_CLOCK_01_H
