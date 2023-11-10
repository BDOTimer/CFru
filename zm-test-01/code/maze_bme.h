#ifndef MAZE_BESTMORDAEVER_H
#define MAZE_BESTMORDAEVER_H
///----------------------------------------------------------------------------|
/// Лабиринт BestMordaEver.
/// https://habr.com/ru/articles/319532/
///----------------------------------------------------------------------------:
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using matrix_t = std::vector<std::vector<int>>;

namespace labitinth
{
    ///-------------------------|
    /// Интерфейс Лабиринта.    |--------------------------------------------!!!
    ///-------------------------:
    struct      Interface
    {   virtual~Interface() {}

        virtual void             generator(size_t w, size_t h) = 0;
        virtual const std::vector<std::string>& get_conv2str() = 0;

        std::string_view  name = "noname";

        static Interface* make_BestMordaEver();
    };

    ///------------------------------------------------------------------------|
    /// Лабиринт BestMordaEver.
    ///------------------------------------------------------------------------:
    struct  BestMordaEver : matrix_t, Interface
    {       BestMordaEver(size_t H, size_t W) :
                matrix_t( H, std::vector<int>(W, wall)),
                height  ( H   ),
                width   ( W   ),
                maze    (*this)
            {
                gen();
            }
            BestMordaEver() : maze(*this) { name = "BestMordaEver"; }

        enum eTYPE
        {   wall = 0,
            pass = 1
        };

        ///---------------------------------|
        /// Показать в консольном окне.     |
        ///---------------------------------:
        void debug() const
        {   for    (auto&  r : maze)
            {   for(auto&  e : r   )
                {   switch(e)
                    {   case wall:
                            std::cout << "0 ";
                            break;
                        case pass:
                            std::cout << "  ";
                            break;
                    }
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }

        const std::vector<std::string>& get_conv2str()
        {   mazestr = std::vector<std::string>(height, std::string(width, ' '));

            size_t y = 0;
            for    (auto&  r : maze)
            {   size_t x = 0;
                for(auto&  e : r   )
                {   if(e == wall) mazestr[y][x] = '#';
                    ++x;
                }
                ++y;
            }
            return mazestr;
        }

        size_t height, width;

        std::vector<std::string>       mazestr;
        std::vector<std::vector<int>>& maze;

        void generator(size_t w, size_t h)
        {
            if(w < 3 || h < 3)
            {   height = 3;
                width  = 3;
            }
            else
            {
                height = h + (h&1 ? 0 : 1);
                width  = w + (w&1 ? 0 : 1);

                height%= 100;
                width %= 100;
            }

            /// Массив заполняется землей-ноликами:
            maze = std::vector<std::vector<int>>(height,
                               std::vector<int> (width , wall));
            gen();
        }

    private:
        ///---------------------------------|
        /// Собственно сам алгоритм.        |
        ///---------------------------------:
        void gen()
        {   size_t x = 3,
                       y = 3;

            /// TODO ...
            /// Да, 10000 это костыль, ...
            for(int a = 0; a < 10000; ++a)
            {   ///----------------------------|
                /// Уменьшаем костыль.         |
                ///----------------------------:
                if(a%500 == 0 && ended()) break;

                maze[y][x] = pass;

                while(true)
                {   ///---------------------------------------------|
                    /// По две клетки в одном направлении за прыжок.|
                    ///---------------------------------------------:
                    switch(rand()%4)
                    {   ///---------|
                        /// Вверх.  |
                        ///---------:
                        case 0:
                        {   if( y != 1 &&
                                    maze[y-2][x] == wall)
                            {   maze[y-1][x]  = pass;
                                maze[y-2][x]  = pass;
                                y-=2;
                            }
                        }
                        ///---------|
                        /// Вниз.   |
                        ///---------:
                        case 1:
                        {   if( y != height-2 &&
                                    maze[y+2][x] == wall)
                            {   maze[y+1][x]  = pass;
                                maze[y+2][x]  = pass;
                                y+=2;
                            }
                        }
                        ///---------|
                        /// Налево. |
                        ///---------:
                        case 2:
                        {   if( x != 1 &&
                                    maze[y][x-2] == wall)
                            {   maze[y][x-1]  = pass;
                                maze[y][x-2]  = pass;
                                x-=2;
                            }
                        }
                        ///---------|
                        /// Направо.|
                        ///---------:
                        case 3:
                        {   if( x != width-2 &&
                                    maze[y][x+2] == wall)
                            {   maze[y][x+1]  = pass;
                                maze[y][x+2]  = pass;
                                x+=2;
                            }
                        }
                    }
                    if(deadend(x,y)) break;
                }

                if(deadend(x,y))
                {   ///--------------------------------|
                    /// Вытаскиваем крота из тупика    |
                    ///--------------------------------:
                    do
                    {   x = 2*(rand()%((width -1)/2))+1;
                        y = 2*(rand()%((height-1)/2))+1;
                    }
                    while(maze[y][x] != pass);
                }
            }
        }

        ///---------------------------------|
        /// Определяет тупики.              |
        ///---------------------------------:
        bool deadend(size_t x, size_t y) const
        {   int a = 0;

            if(x == 1        || maze[y][x-2] == pass) a+=1;
            if(y == 1        || maze[y-2][x] == pass) a+=1;
            if(x == width -2 || maze[y][x+2] == pass) a+=1;
            if(y == height-2 || maze[y+2][x] == pass) a+=1;

            return a == 4 ? 1 : 0;
        }

        ///---------------------------------|
        /// Если что копать?                |
        ///---------------------------------:
        bool ended()
        {   for    (auto& r : maze )
            {   for(auto& e : r    )
                {   if   (e == wall) return false;
                }
            }
            return true;
        }

        public:static void test();
    };

    Interface* Interface::make_BestMordaEver()
    {   return new  BestMordaEver;
    }

///----------------------------------------------------------------------------|
/// Тест.
///----------------------------------------------------------------------------:
    void BestMordaEver::test()
    {   srand((unsigned)time(NULL));

        std::cout << "labitinth::BestMordaEver::test();\n";

        BestMordaEver  run;

        while(true)
        {   std::cout << "New Labitinth:\n";
            while(true)
            {   std::string bufw, bufh;

                size_t W;
                std::cout << "W = ";
                std::getline(std::cin, bufw);
                size_t H;
                std::cout << "H = ";
                std::getline(std::cin, bufh);

                try
                {   W = size_t(std::stod(bufw));
                    H = size_t(std::stod(bufh));
                    run.generator         (W,H);

                    break;
                }
                catch(...)
                {   std::cout << "Error input ...\n\n";
                }
            }

            for    (auto&    s : run.get_conv2str())
            {   std::cout << s << '\n';
            }
            std::cout      << '\n';
        }
    }
}

#endif // MAZE_BESTMORDAEVER_H
