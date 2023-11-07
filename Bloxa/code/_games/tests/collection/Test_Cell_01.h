#ifndef TEST_CELL_01_H
#define TEST_CELL_01_H
///----------------------------------------------------------------------------|
/// "Test_Clock_01.h"
///----------------------------------------------------------------------------:
#include "../../../global.h"

namespace Objects
{
///----------------------------------------------------------------------------|
/// Декартовы оси.
///----------------------------------------------------------------------------:
    struct  Test_Axis_01 : IObject, Global
    {       Test_Axis_01(sf::View& v) : view(v), lines(sf::Lines, NLINES)
            {
                name = "Test_Axis_01";

                sf::Vector2f m[NLINES] =
                {   {   0, 400},
                    {   0,-400},
                    {-400,   0},
                    { 400,   0}
                };
                size_t i = 0;
                for(const auto& p : m)
                {   lines[i].position = p;
                    lines[i].color    = sf::Color::Red;
                        ++i;
                }
            };

        void update   () {}
        bool RPControl(std::string_view command, std::vector<float>& arg)
        {   /// TODO2 ...

            l(command)

            return false;
        }
        void input(const sf::Event& event){}

    private:
        ///-----------------|
        /// Камера.         |
        ///-----------------:
        sf::View&       view;

        const size_t NLINES = 4;
        sf::VertexArray   lines;

        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates states ) const
        {   target.draw(lines, states);
        }
    };

///----------------------------------------------------------------------------|
/// Маркировачная сетка.
///----------------------------------------------------------------------------:
    struct  Test_Cell_01 : IObject, Global
    {       Test_Cell_01(sf::View& v) : view(v), lines(sf::Lines, 0)
            {
                name = "Test_Cell_01";

                build(Nx, Ny);

                return;

                const int left = size_x * (Nx - 1) / 2;
                const int up   = size_y * (Ny - 1) / 2;

                unsigned i = 0;

                for(int x = -left; x <= left; x += size_x)
                {   lines[i  ].position = {(float)x, (float)-up};
                    lines[i++].color    = color;

                    lines[i  ].position = {(float)x, (float) up};
                    lines[i++].color    = color;
                }

                //return;

                for(int y = -up; y <= up; y += size_y)
                {   lines[i  ].position = {(float)-left, (float)y};
                    lines[i++].color    = color;

                    lines[i  ].position = {(float) left, (float)y};
                    lines[i++].color    = color;
                }
            };

        unsigned size_x =  70,
                 size_y =  35;
        unsigned Nx     =   5,
                 Ny     =   9;

        void update   () {}
        bool RPControl(std::string_view command, std::vector<float>& arg)
        {   /// TODO2 ...

            l(command)

            ///-------------------------------------|
            /// build(123,456)                      |
            ///-------------------------------------:
            if(command.find("build") != command.npos)
            {
                if(arg.size() == 2)
                {
                    build((size_t)arg[0], (size_t)arg[1]);
                }
                else {/* ОШИБКА КОЛИЧЕСТВА АРГУМЕНТОВ. */}
            }

            return true;
        }
        void input(const sf::Event& event){}

    private:
        ///-----------------|
        /// Камера.         |
        ///-----------------:
        sf::View&       view;

        sf::VertexArray lines;
        const sf::Color color  = sf::Color::Black;

        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates  states) const
        {   target.draw(lines, states);
        }

        void build(const size_t nx, const size_t ny)
        {
            Nx = nx;
            Ny = ny;

            const size_t NLINES = (Nx + Ny) * 4;

            lines.resize(NLINES);

            const int left = size_x * (Nx - 1) / 2;
            const int up   = size_y * (Ny - 1) / 2;

            unsigned i = 0;

            for(int x = -left; x <= left; x += size_x)
            {   lines[i  ].position = {(float)x, (float)-up};
                lines[i++].color    = color;

                lines[i  ].position = {(float)x, (float) up};
                lines[i++].color    = color;
            }

            //return;

            for(int y = -up; y <= up; y += size_y)
            {   lines[i  ].position = {(float)-left, (float)y};
                lines[i++].color    = color;

                lines[i  ].position = {(float) left, (float)y};
                lines[i++].color    = color;
            }
        }
    };
}


#endif // TEST_CELL_01_H
