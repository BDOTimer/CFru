#ifndef BASE_H
#define BASE_H
///----------------------------------------------------------------------------|
///
///----------------------------------------------------------------------------:
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <list>
#include <map>

#include <SFML/Graphics.hpp>
#include "base.h"

///----------------------------------------------------------------------------|
/// Вспомогательное...
///----------------------------------------------------------------------------:
#define l(a) std::cout  << #a << ": " << (a) << '\n';

template<typename T>
std::ostream& operator<<(std::ostream& o,  const sf::Vector2<T>& a)
{   o << "{" << a.x << ", " << a.y << "}"; return o;
}

namespace deb
{
    void pause(std::string_view mess = "\nTEST END.\n")
    {   std::cout << mess;
        std::cin   .get();
    }
}

namespace sprites
{
    using masive_t = std::vector<  size_t>;
    using matrix_t = std::vector<masive_t>;

    struct  Map_t :      std::vector<std::string_view>
    {       Map_t (const std::vector<std::string_view>& m)
                  :      std::vector<std::string_view> (m)
            {
            }
            Map_t() = default;

        void cpy(const std::vector<std::string>& m)
        {   clear(); for(const auto& s : m) push_back(s);
        }

        size_t W() const{   return front().size(); }
        size_t H() const{   return         size(); }
    };

}

/*
namespace Objects
{
    ///-------------------------|
    /// Интерфейс объекта.      |--------------------------------------------!!!
    ///-------------------------:
    struct      IObject : sf::Drawable
    {   virtual~IObject(){}

        virtual void update   (                         ) = 0;
        virtual void input    ( const sf::Event&   event) = 0;
        virtual bool RPControl( std::string_view command,
                                std::vector<float>&  arg) = 0;

        std::string_view name;

    private:
    };
}
*/

#endif // BASE_H
