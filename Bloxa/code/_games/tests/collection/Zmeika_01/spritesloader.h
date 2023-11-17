#ifndef SPRITESLOADER_H
#define SPRITESLOADER_H
///----------------------------------------------------------------------------|
///
///----------------------------------------------------------------------------:
#include "base.h"

void tests();

struct Config
{
    const size_t fon{' '};

    sf::Vector2i winsize{500 * 1366 / 768, 500};

}config;

Config* cfg = &config;

namespace sprites
{
    std::string_view DIR_FOR_SPRITES{"res_zmei_img/"};

///----------------------------------------------------------------------------|
/// Словарь для ручного редактора карт.
///----------------------------------------------------------------------------:
#define T (size_t)

std::map<size_t, std::string_view> voc
{
    {T ' ', "w.jpg"},
    {T '#', "stone01-128.png"},
    {T 'A', "apple02-128.png"},
    {T '.', "grass02-128.jpg"},
    {T '|', "stone01-128.png"},
    {T '-', "stone01-128.png"},
    {T'\'', "stone01-128.png"},

    {T 'o', "ball01o-128.png"},
    {T 'O', "ball01s-128.png"},
    {T 'e',         "eee.png"}
};

#undef T

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

    ///------------------------------------------------------------------------|
    /// Матрица с данными для рендера.
    ///------------------------------------------------------------------------:
    struct  Map4Render_t : matrix_t
    {       Map4Render_t (const Map_t& m)
                :   matrix_t(m.H(), masive_t(m.W())),
                    mat     ( *this)
            {
                load(m);
            }

        size_t W() const{   return front().size(); }
        size_t H() const{   return         size(); }

    private:
        matrix_t& mat;
        void load(const Map_t& m)
        {
            for     (size_t y = 0, Y = H(); y < Y; ++y)
            {   for (size_t x = 0, X = W(); x < X; ++x)
                {   mat[y][x] = size_t(m[y][x]);
                }
            }
        }
    };

    ///------------------------------------------------------------------------|
    /// Все текстуры хранятся здесь + загрузка текстур в примитивы.
    ///------------------------------------------------------------------------:
    struct  TxtrHolder
    {       TxtrHolder()
            {
            }

        static std::string dir(std::string_view name)
        {   return std::string(DIR_FOR_SPRITES) + name.data();
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
        /// o.setOrigin (64,  64);
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
            {   std::cerr << "ERROR: load \""
                          << filename
                          << "\" texture\n";
                return;
            }

          //m.back().setRepeated(repeate);
          //m.back().setSmooth  (true   );

            o.setTexture(&m.back() );

        /// o.setOrigin (getTSize().x/2,  getTSize().y/2);
        }

        sf::Vector2u getTSize() const
        {   if(m.empty())
            {   std::cout << "ERROR:...\n"; return {0, 0};
            }
            return m.back().getSize();
        }

        std::list<sf::Texture> m;
    };

    const std::string_view NONAME{"<?>"};
    ///------------------------------------------------------------------------|
    /// Тайл.
    ///------------------------------------------------------------------------:
    struct  Tile : sf::Sprite
    {
        std::string_view filename{NONAME};
    };

    ///------------------------------------------------------------------------|
    /// Promt.
    ///------------------------------------------------------------------------:
    struct  Promt : sf::Text
    {       Promt()
            {
                font.loadFromFile  ("c:/windows/fonts/georgia.ttf"); ///<----!!!

                setFont                  (font);
                setCharacterSize           (20);
                setStyle    (sf::Text::Regular);
                setFillColor(sf::Color::Yellow);
                setPosition      (20.f,   20.f);
                setString        (promt.data());
            }

    private:
        std::wstring_view promt{L"Управление: 0, 1, 2, 3, 4, 5, R, W, S, курсор."};
        sf::Font          font;
    };

    ///------------------------------------------------------------------------|
    /// Загрузчик спрайтов.
    ///------------------------------------------------------------------------:
    struct  Loader
    {       Loader() :
                SZMAX(2048),
                tiles{std::vector<Tile>(SZMAX)}
            {
                ids.reserve(SZMAX);

                if(auto error = load_textures(); !error.empty())
                {     l(error)
                }
            }

        const std::vector<Tile>& getTiles() const { return tiles; }

        void setCam(sf::View& cam, size_t NX, size_t NY) const
        {
            float K = float(cfg->winsize.x) / cfg->winsize.y;

            const sf::Vector2u     szu = txtr.getTSize();
            const float TX = float(szu.x);
            const float TY = float(szu.y);
            sf::Vector2f           sz;

            if(NX > NY)
            {   sz = sf::Vector2f (
                               TX * NX,
                               TY * NX / K);
                cam.setCenter( sz.x / 2, TY * NY / 2);
            }
            else
            {
                sz = sf::Vector2f (
                               TX * NY * K,
                               TY * NY);
                cam.setCenter( TX * NX / 2, sz.y / 2);
            }
            cam.setSize(sz);
        }

        bool checked_isbad(const Map4Render_t& m)
        {
            for    (const auto& r : m)
            {   for(const auto  e : r)
                {
                    if( std::string::npos == ids.find(wchar_t(e)))
                    {   std::cout << "ERROR: line: " << __LINE__ << '\n'
                                  << "       find ID without texture!\n\n";
                        return true;
                    }
                }
            }
            return false;
        }

    private:
        const size_t      SZMAX;
        TxtrHolder         txtr;
        std::vector<Tile> tiles;
        std::wstring        ids;

        std::string_view load_textures()
        {
            for(const auto&[id, filename] : voc)
            {
                Tile& tile = tiles[id];

                if(tile.filename != NONAME)
                {   return "ERROR: voc have duplication.";
                }

                ids.push_back((wchar_t)id);

                txtr.setTexture2Sprite(tile, filename);

                tile.filename = filename;
            }
            return "";
        }

        template<typename T>
        const std::string_view& getFilename(T id)
        {   const auto i = (size_t)id;
            if(i < tiles.size()) return tiles[i].filename;
            return "error: id >= tiles.size()";
        }

        void debug()
        {   for(const auto& id : ids)
            {   std::wcout  << std::setw(5) << id;
                std:: cout  << " : "        << tiles[id].filename
                            << '\n';
            }
        }

        static void   test ();
        friend void ::tests();
    };

    ///----------------------|
    /// Тест.                |
    ///----------------------:
    void Loader::test()
    {
        std::cout << "sprites::Loader::test()\n";

        Loader loader;
               loader.debug();

        std::cout << "\n";
        std::cin.   get();
    }
}

#endif // SPRITESLOADER_H
