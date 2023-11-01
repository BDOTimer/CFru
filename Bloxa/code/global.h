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
        font->loadFromFile("sansation.ttf");                       ///<------!!!
    }

    static void del()
    {   delete  font;
    }

protected:
    static float           deltaTime;
    static sf::Font*            font;
    static sf::Font            font2;
    static sf::RenderWindow* pwindow;
};

//sf::Font*   Global::font = nullptr;

#endif // GLOBAL_H
