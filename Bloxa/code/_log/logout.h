#ifndef LOGOUT_H
#define LOGOUT_H
///----------------------------------------------------------------------------|
/// "logout.h"
///----------------------------------------------------------------------------:
#include "../global.h"
#include <list>


namespace logout
{
    struct  Log              : obj::IObject, Global
    {       Log(sf::View& v) : view(v)
            {
                text.setFont                (*font);
                text.setCharacterSize          (12);
                text.setStyle  (sf::Text::Regular );
                text.setFillColor(sf::Color::White);

                const auto& sz = view.getSize(    );
                text.setPosition(-sz.x/ 2 +8,-sz.y/ 2 -20);

                m.push_back(L"Привет, Я Блоха!" );
                m.push_back(L"... тут лог ...");
                m.push_back(L"");
            }

        ///--------------------------|
        /// Интерфейсные методы.     |
        ///--------------------------:
        void update   ()
        {
        }
        bool RPControl(std::string_view command, std::vector<float>& arg)
        {   /// TODO2 ...

            l(command)

            return false;
        }
        void input(const sf::Event& event){}

        ///--------------------------|
        /// +++                      |
        ///--------------------------:
        Log& operator<<(std::wstring_view s)
        {   m.back() += s;
            return  *this;
        }

        Log& operator<<(char c)
        {   m.push_back(L"");
            return     *this;
        }

        void  clear()
        {   m.clear();
            m.push_back(L"");
        }

    private:
        ///-----------------|
        /// Камера.         |
        ///-----------------:
        sf::View&     view;

        ///-----------------|
        /// Камера.         |
        ///-----------------:
        std::vector<std::wstring> m{L""};
        sf::Text                    text;

        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates  states ) const
        {   sf::Text t(text);

            size_t i = 0;

            if(m.size() > 8)
            {   i = m.size() - 8;
            }

            for(; i < m.size(); ++i)
            {   t.setString(m[i]);
                t.move  (0, 12.f);
                target.draw(t, states);
            }
        }
    };
}

#endif // LOGOUT_H
