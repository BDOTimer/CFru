#ifndef MYLIB_H
#define MYLIB_H
///----------------------------------------------------------------------------|
/// "mylib.h"
///----------------------------------------------------------------------------:
#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "debug.h"

namespace myl
{

    template<typename T>
    void setOrigin(T& o)
    {   o.setOrigin({o.getSize().x / 2, o.getSize().y / 2});
    }

    inline const sf::Vector2f U2F(const sf::Vector2u& o)
    {   return   sf::Vector2f( o.x, o.y );
    }


    ///------------------------------------------------------------------------|
    /// Обвёртка над системным временем.
    ///------------------------------------------------------------------------:
    struct  Time_t
    {
        int sec () const { return info->tm_sec ; }
        int min () const { return info->tm_min ; }
        int hour() const { return info->tm_hour; }

        bool update()
        {   ///-------------------------|
            /// Читаем время из системы.|
            ///-------------------------:
            now  = std::time      (&now);
            info = std::localtime (&now);

            ///-------------------------|
            /// Если тика не было.      |
            ///-------------------------:
            if(s == sec()) return  false;
               s  = sec();

            ///-------------------------|
            /// Секунда тикнула.        |
            ///-------------------------:
            return                  true;
        }

    private:
        std::time_t now ;
        std::tm*    info;

        int s = -1;
    };
}

#endif // MYLIB_H
