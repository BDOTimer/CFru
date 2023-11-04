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
      //font->loadFromFile("sansation.ttf");                       ///<------!!!
        font->loadFromFile  ("C:/windows/fonts/arial.ttf");       ///<-------!!!
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

        std::string_view     name;

    private:
    };

}

#endif // GLOBAL_H
