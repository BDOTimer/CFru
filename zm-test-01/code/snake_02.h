#ifndef SNAKE_01_H
#define SNAKE_01_H
///----------------------------------------------------------------------------|
/// "sanake_01.h"
///----------------------------------------------------------------------------:
#include <iostream>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#define l(a) std::cout  << #a << ": " << (a) << '\n';
#define ASSERT(U) if(!(U)) {std::cout  << "\aASSERT: FILE: "   \
                                       << cutpath(__FILE__)    \
                                       << ", LINE: "           \
                                       << __LINE__ << '\n';}

inline std::string cutpath  (std::string s)
{   auto p = s.find  ("code");
    return   s.substr(p , s.size() - p);
}

namespace win
{
    #include <windows.h>

    void cls  (      ){ std::system("cls"); }
    void sleep(int ms){ Sleep      ( ms  ); }
    void set_cursor_to_start()
    {   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 2 });
    }
    void carret_visible(bool visible = false)
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

        SetConsoleTitleW(L"Zмейка-2023");
    }
}

namespace snake
{

    const std::vector<std::string_view> map_01
    {
        "####-------------------------------------------",
        "####|            |eeee                        |",
        "####|        A   |               A            |",
        "|----            |                            |",
        "|                |       ----------------     |",
        "|       eee      |               |            |",
        "|          eeee  |      eee      |            |",
        "|                |      eee      |            |",
        "|                |               |            |",
        "|  A          A  |               |            |",
        "|                |               |            |",
        "|       ------------------       |            |",
        "|----                           e|            |",
        "####|                A          e|       A    |",
        "####|                         eee|            |",
        "####------------------------------------------'"
    };

    struct  vec2i
    {   size_t x, y;
    };

    ///-----------------------|
    /// Потом на sf::Vector2i |
    ///-----------------------:
/// using  vec2i_t   =   vec2i;
    using  vec2i_t   =   sf::Vector2u;

    ///-----------------------|
    /// Конфиг.               |
    ///-----------------------:
    struct  Config
    {       Config() : pmap(&map_01)
            {
                if(pmap != nullptr)
                {   sizefield.y   = pmap->        size();
                    sizefield.x   = pmap->front().size();
                    sizedisplay.y = sizefield.y + start.y * 2;
                    sizedisplay.x = sizefield.x + start.x * 2;
                }
            }

        vec2i sizefield  {20, 12};
        vec2i sizedisplay{26, 16};
        vec2i start      { 3,  2};

        const size_t STATUS     = size_t(' ');
        const size_t STATUSDISP = size_t('.');
        const size_t APPLE      = size_t('A');
        const size_t ZM         = size_t('o');

        const std::vector<std::string_view>* pmap = nullptr;

        bool is_free(size_t  status)
        {   return status == STATUS     ||
                   status == STATUSDISP ||
                   status == ZM;
        }

        bool is_apple(size_t status){ return status == APPLE; }

        void verificate()
        {   /// ASSERT(...)
            /// ...
        }

    } config;

    Config* cfg = &config;

    ///-----------------------|
    /// Ячейка матрицы.       |
    ///-----------------------:
    struct  Cell
    {       Cell() = default;
            Cell(int st) : status(st) {}

        vec2i_t position;

        size_t  get(                )const{ return         status     ; }
        void set(const size_t status)     { this->status = status     ; }
        void cls(                   )     { this->status = cfg->STATUS; }

    private:
        size_t status;
    };

    ///-----------------------|
    /// Для удобства.         |
    ///-----------------------:
    using massiv_t = std::vector<Cell    >;
    using matrix_t = std::vector<massiv_t>;

    std::ostream& operator<<(std::ostream& o, const matrix_t& m)
    {   for    (const auto& r : m)
        {       o << "   ";
            for(const auto& e : r)
            {   o << char(e.get());
            }   o << '\n' ;
        }       o << '\n' ;
        return  o;
    }

    ///-----------------------|
    /// ...                   |
    ///-----------------------:
    void cpy(const vec2i& start, matrix_t& o, const matrix_t& m)
    {   for     (size_t y = 0,
                        Y = m.size(),
                       sy = start.y,
                       sY = o.size(); y < Y && sy < sY; ++y, ++sy)
        {   for (size_t x = 0,
                        X = m.front().size(),
                       sx = start.x,
                       sX = o.front().size(); x < X && sx < sX; ++x, ++sx)
            {   o[sy][sx].set(m[y][x].get());
            }
        }
    }

    ///------------------------------------------------------------------------|
    /// Эмулятор Дисплея ...
    ///------------------------------------------------------------- EmDisplay:
    struct  EmDisplay   : matrix_t
    {       EmDisplay() : matrix_t(cfg->sizedisplay.y,
                          massiv_t(cfg->sizedisplay.x, Cell(cfg->STATUSDISP))),
                          mat(*this)
            {
            }

       matrix_t& mat;

       size_t W() const { return mat.front().size(); }
       size_t H() const { return mat.        size(); }

    private:
        /// ...
    };

    ///------------------------------------------------------------------------|
    /// Поле для змейки это не весь Мир для поля ...
    ///------------------------------------------------------------------ Field:
    struct  Field   : matrix_t
    {       Field() : matrix_t(cfg->sizefield.y,
                      massiv_t(cfg->sizefield.x, Cell(cfg->STATUS))),
                      mat(*this)
            {   init       (mat);
                add_walls  (mat);
            }
            Field(const std::vector<std::string_view>* Map) : mat(*this)
            {   load(Map);
                init(mat);
            }

        matrix_t& mat               ;
        vec2i     start = cfg->start;

        ///-----------------------|
        /// Гет свободную клетку. |
        ///-----------------------:
        Cell* getfree() const
        {
            for(int cnt = 500; cnt != 0; --cnt)
            {   const auto Y = (size_t)rand()%mat.        size();
                const auto X = (size_t)rand()%mat.front().size();

                if(cfg->is_free(getstatus(X, Y))) return &mat[Y][X];
            }
            return nullptr;
        }

        int getstatus(size_t x, size_t y) const
        {   return mat[y][x].get();
        }

    private:
        ///-----------------------|
        /// Инициализация.        |
        ///-----------------------:
        static void init(matrix_t& m)
        {   for     (unsigned y = 0, Y = m.        size(); y < Y; ++y)
            {   for (unsigned x = 0, X = m.front().size(); x < X; ++x)
                {   m[y][x].position = {x, y};
                }
            }
        }

        ///-----------------------|
        /// Добавим стенки.       |
        ///-----------------------:
        static void add_walls(matrix_t& m)
        {   for(auto& e : m.front()) e.set(size_t('#'));

            m.back() = m.front();

            for(auto& r : m)
            {   r.front().set(size_t('#'));
                r.back () =   r.front();
            }
        }

        void load(const std::vector<std::string_view>* Map)
        {
            mat = matrix_t(Map->        size(),
                  massiv_t(Map->front().size()));

            for    (size_t y = 0; y < Map->        size(); ++y)
            {   for(size_t x = 0; x < Map->front().size(); ++x)
                {
                    mat[y][x].set((int)((*Map)[y][x]));
                }
            }
        }
    };

    ///-----------------------|
    /// EmDisplay << Field    |
    ///-----------------------:
    EmDisplay& operator<<(EmDisplay& o, const Field& m)
    {          cpy(m.start, o.mat, m.mat);
        return o;
    }

    ///------------------------------------------------------------------------|
    /// Элемент тела змейки.
    ///------------------------------------------------------------------ Snake:
    struct  SnakeNode
    {       SnakeNode() = default;
            SnakeNode(Cell* p, int color) : pcell(p), color(color)
            {
            }

        Cell* pcell = nullptr;

        void set2head (                     ){       color = int('O'); }
        void set2color(const int color = 'o'){ this->color = color   ; }
        int  get      (                )const{ return        color   ; }

    protected:
        int  color = int('O');
    };

    ///-----------------------|
    /// Field << SnakeNode    |
    ///-----------------------:
    Field& operator<<(Field& o, const SnakeNode& n)
    {   const auto& pos = n.pcell->position;
                o[pos.y][pos.x].set(n.get());
        return  o;
    }

    ///------------------------------------------------------------------------|
    /// Яблоко.
    ///------------------------------------------------------------------ Apple:
    struct  Apple : SnakeNode
    {       Apple()
            {
            }

        void set(Cell* p, int color = (int)'A')
        {   pcell            = p;
            SnakeNode::color = color;

            //l(pcell->position.x)
            //l(pcell->position.y)
        }
    };

    ///-----------------------|
    /// Field << Apple        |
    ///-----------------------:
    Field& operator<< (Field& o, const Apple& a)
    {            o << (SnakeNode)a;
        return   o;
    }

    ///------------------------------------------------------------------------|
    /// Всё тело змейки.
    ///------------------------------------------------------------------ Snake:
    struct  SnakeBody : std::list<SnakeNode>
    {       SnakeBody(Cell* p)
            {   push_front(SnakeNode(p, int('O')));
            }

        ///----------------------------------|
        /// Сожрать яблоко.                  |
        ///----------------------------------:
        void eat(Cell* p)
        {   front().set2color();
            push_front(SnakeNode(p, int('O')));
        }

        ///----------------------------------|
        /// Переползти.                      |
        ///----------------------------------:
        void moved(Cell* p)
        {   front().set2color();
            push_front(SnakeNode(p, int('O')));
            pop_back  ();
        }

    private:

    };

    ///-----------------------|
    /// Field << SnakeBody    |
    ///-----------------------:
    Field& operator<<(Field& o, const SnakeBody& m)
    {   for(const auto& e : m) o <<  e; return o;
    }

    ///------------------------------------------------------------------------|
    /// ...
    ///------------------------------------------------------------------ Snake:
    struct  Snake
    {       Snake  (Field& f, const vec2i_t& position)
                :   field (f),
                    body (&field[position.y][position.x])
            {
            }

        const SnakeNode& get_head () const { return body.front(); }

        ///----------------------------------|
        /// Сожрать яблоко.                  |
        ///----------------------------------:
        void eat(Cell* p)
        {   body.eat  (p);
        }

        ///----------------------------------|
        /// Переползти.                      |
        ///----------------------------------:
        void moved(Cell* p)
        {   const auto& pos = body.back().pcell->position;
            field[pos.y][pos.x].cls();

            body.moved(  p);
        }

    private:
        Field&   field;
        SnakeBody body;

        static void test ();
        friend void tests();
        friend Field& operator<<(Field&, const Snake&);
        friend struct AIdefault;
    };

    ///-----------------------|
    /// Field << Snake        |
    ///-----------------------:
    Field& operator<<(Field& o, const Snake& m)
    {            o << m.body;
        return   o;
    }

    ///-----------------------|
    /// Test Snake.           |
    ///-----------------------:
    void Snake::test()
    {
        std::cout << "   snake::Snake::test()\n";

        EmDisplay display;
        Field       field;
        Apple       apple;
                    apple.set(field.getfree(), cfg->APPLE);
        Snake snake(field, {10,   10});

        field   << snake << apple;
        display << field;

        std::cout << display.mat << '\n';
    }

    ///------------------------------------------------------------------------|
    /// Начинка для мозгов(AIdefault). Движение.
    ///------------------------------------------------------------------ Moved:
    struct  Moved
    {
        enum eDIR
        {   UP  ,
            DOWN,
            LEFT,
            RIGHT
        };

        ///------------------------|
        /// Куда можно двигаться.  |
        ///------------------------:
        const std::vector<vec2i_t>& what_go(
            const Field&     f,
            const SnakeNode& head)
        {
            dir.clear();

            vec2i_t pos = head.pcell->position;

            is(f, {pos.x  , pos.y-1}); /// UP
            is(f, {pos.x  , pos.y+1}); /// DOWN
            is(f, {pos.x-1, pos.y  }); /// LEFT
            is(f, {pos.x+1, pos.y  }); /// RIGHT

            what_apple(f);

            return dir;
        }

    private:
        std::vector<vec2i_t> dir;

        ///------------------------|
        /// А сюда можно ползти?   |
        ///------------------------:
        void is(const Field& f, const vec2i_t& posdir)
        {   const size_t& H = f.        size();
            const size_t& W = f.front().size();

            if(H <= (size_t)posdir.y) return;
            if(W <= (size_t)posdir.x) return;

            int status = f[posdir.y][posdir.x].get();

            if(cfg->is_free (status) ||
               cfg->is_apple(status)) dir.push_back(posdir);
        }

        ///------------------------|
        /// А есть ли рядом яблоко?|
        ///------------------------:
        void what_apple(const Field& f)
        {   for(const auto& d : dir)
            {   if( int status = f[d.y][d.x].get(); cfg->is_apple(status))
                {   dir.resize(1);
                    dir[0] = d;
                }
            }
        }
    };

    ///------------------------------------------------------------------------|
    /// Цифровой разум(рандомный).
    ///--------------------------------------------------------------------- AI:
    struct  IAI
    {      virtual ~IAI(){}

        virtual Cell* step(const Snake&) = 0;

        std::string_view name;

        bool isapple = false;
    };

    struct  AIdefault : IAI
    {       AIdefault()
            {   name = "AIdefault";
            }

        ///------------------------|
        /// Куда идём?!            |
        ///------------------------:
        Cell* step(const Snake& snake)
        {
            isapple = false;

            const auto& dir = moved.what_go(snake.field, snake.get_head());

            //l(dir.size())

            if(!dir.empty())
            {   auto n = size_t(rand()%dir.size());
                const vec2i_t& d = dir[n];

                if(1 == dir.size())
                {
                    int satatus = snake.field[dir[0].y][dir[0].x].get();
                    isapple     = cfg->is_apple(satatus);
                }
                return &snake.field[d.y][d.x];
            }
            return nullptr;
        }

    private:
        Moved moved;
    };

    ///------------------------------------------------------------------------|
    /// Игра.
    ///------------------------------------------------------------------- Game:
    struct  Game
    {       Game()
                :   field( cfg->pmap),
                    snake( field, {10, 10})
            {
                setapple();
                pIAI = new AIdefault;
            }
           ~Game(){ delete pIAI; }

        bool gameover;

        void loop ()
        {
            for(gameover = false; !gameover;)
            {
                win::set_cursor_to_start();

                loopone();

                std::cout << display.mat << '\n';
                win::sleep(100);
            }
        }

        void loopone()
        {    render ();
             gameover = !moved();
        }

        ///------------------------|
        /// Поменять мозги.        |
        ///------------------------:
        void set(IAI* p){ if(pIAI != nullptr) delete pIAI; pIAI = p; }

        const EmDisplay& getdisplay() const { return display; }

    private:
        EmDisplay display;
        Field       field;
        Apple       apple;
        Snake       snake;
        IAI*         pIAI = nullptr;

        void render()
        {   field     << snake << apple;
            display   << field;
        }

        bool moved()
        {   Cell* pcell = pIAI->step(snake);

            if(nullptr == pcell) return false;

            if(pIAI->isapple)
            {   snake.eat  (pcell);
                return setapple ();
            }
            else
            {   snake.moved(pcell);
            }
            return true;
        }

        bool setapple()
        {   if(nullptr == field.getfree()) return false;
            apple.set(field.getfree(), cfg->APPLE);
            return true;
        }

        static void test ();
        friend void tests();
    };

    ///-----------------------|
    /// Test Game.            |
    ///-----------------------:
    void Game::test()
    {    std::cout << "   snake::Game::test()\n";
         Game  run;
               run.loop();
    }

    inline void tests()
    {   win::carret_visible();
      //Snake::test();
        Game ::test();
    }
}

#endif // SNAKE_01_H
