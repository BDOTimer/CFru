#ifndef GLOBAL_H
#define GLOBAL_H
///----------------------------------------------------------------------------|
/// "global.h"
///----------------------------------------------------------------------------:
#include <SFML/Graphics.hpp>

#include "mylib/mylib.h"

///-------------------------------|
/// Конфиг.                       |
///-------------------------------:
struct Cfg
{   sf::Vector2i winsize{500 * 1366 / 768, 500};

    static Cfg* p;
};

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

namespace obj = Objects;

///----------------------------------------------------------------------------|
/// Псевдоглобальные данные.
///----------------------------------------------------------------------------:
struct Global
{
    static void info()
    {   l(pwindow->getSize().x)
        l(pwindow->getSize().y)
    }

    static void init()
    {   font = new sf::Font();
      //font->loadFromFile("sansation.ttf");                       ///<------!!!
        font->loadFromFile  ("C:/windows/fonts/arial.ttf");       ///<-------!!!
    }

    static void del()
    {   delete  font;
    }

    static const sf::Font* getFont() { return  font; }

protected:
    static float           deltaTime;
    static sf::Font*            font;
    static sf::Font            font2;
    static sf::RenderWindow* pwindow;
};

#include "_log/logout.h"
extern logout::Log* plog;

#define LOG (*plog)

#endif // GLOBAL_H
