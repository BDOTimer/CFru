///----------------------------------------------------------------------------|
/// ...
///----------------------------------------------------------------------------:
#include <string_view>
#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "../global.h"

namespace ui
{
    ///------------------------------------------------------------------------|
    /// ButtonStyle.
    ///------------------------------------------------------------------------:
    struct  ButtonStyle
    {       ButtonStyle(std::string_view name_) : name(name_), textures(N)
            {   std::string nm{"ui"}; nm += name_;

                for(unsigned i = 0; i < N; ++i)
                {   textures[i].loadFromFile(nm + txr[i]);
                }
            }

        std::string name;

    private:
        const char* txr[3] { "0.png", "1.png", "2.png" };

        std::vector<sf::Texture> textures;

        static const unsigned N;
        friend struct    Button;
    };
    const unsigned ButtonStyle::N = 3;

    ///------------------------------------------------------------------------|
    /// ButtonStyleCollection.
    ///------------------------------------------------------------------------:
    struct  ButtonStyleCollection
    {       ButtonStyleCollection()
            {   for(const auto   nm : styles)
                {   buttonStyles[nm] = new ButtonStyle(nm);
                }
            }
           ~ButtonStyleCollection()
            {   for(const auto&[nm, e] : buttonStyles) delete e;
            }

        const char* styles[3]{ "/0/", "/1/", "/2/" };

        ButtonStyle* get(std::string_view name)
        {
            IFERROR_EXCEPTION(buttonStyles.empty())

            if(auto    a  = buttonStyles.find(name);
                       a != buttonStyles.end())
            {   return a -> second;
            }
            return buttonStyles.begin()->second;
        }

    private:
        std::map<std::string_view, ButtonStyle*> buttonStyles;
    };

    ///------------------------------------------------------------------------|
    /// Button.
    ///------------------------------------------------------------------------:
    struct  Button : public sf::Drawable, protected Global
    {       Button(std::wstring_view name_    ,
                   std::string_view namestyle) : name   (name_.data()),
                                                 sprites(ButtonStyle::N)
            {
                buttonStyle = collection.get(namestyle);

                for(unsigned i = 0; i < ButtonStyle::N; ++i)
                {
                    sprites [i].setTexture(&buttonStyle->textures[i]);
                    sprites [i].setSize   ({70, 20});

                    //sf::Vector2f sz =
                    //    sf::Vector2f(buttonStyle->textures[i].getSize());
                    //sprites[i].setOrigin(sz.x / 2, sz.y / 2);

                    //sprites [i].setColor(sf::Color(244,128,128));
                }
            }

        std::wstring name;

        sf::Text text;

        enum eSTATUS
        {   E_FREE,
            E_OVER,
            E_DOWN,
            /// ...
            E_END
        };

        eSTATUS status = E_FREE;

        ButtonStyle* buttonStyle = nullptr;

        float scale = 0.1f;

        void setPosition(sf::Vector2f pos)
        {   for(auto& e : sprites) e.setPosition(pos);
            setupText();
        }

        void prosses(const sf::Vector2i& mouse_pos, const sf::Event& event)
        {
            const sf::FloatRect& rect = sprites[0].getGlobalBounds();
            const bool    b = rect.contains(sf::Vector2f(mouse_pos));

            if (event.type == sf::Event::MouseMoved)
            {
                if( b ) status = E_OVER;
                else    status = E_FREE;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
                && status == E_OVER)
            {   if(status != E_DOWN) callback();
                   status  = E_DOWN;
            }
            else if( b )
            {      status  = E_OVER;
            }
            else   status  = E_FREE;
        }

        void setCallback(std::function<void()> cb)
        {   callback = cb;
        }

    private:
        std::function<void()>     callback{[](){}};
        std::vector  <sf::RectangleShape> sprites;
        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates  states) const
        {   target.draw(sprites[status], states);
            target.draw(text           , states);
        }

        void setupText()////////////////////////////////////////////////////////
        {
            text.setFont                 (*Global::font);
            text.setCharacterSize                   (14);
            text.setStyle       (sf::Text::Regular     );
            text.setFillColor   (sf::Color(  0,  0,  0));
            text.setOutlineColor(sf::Color(255,255,255));
            text.setOutlineThickness               (1.f);

            text.setString(name);

          //const sf::FloatRect& rspr = sprites[0].getLocalBounds();
            const sf::FloatRect& rtxt = text      .getLocalBounds();
            const sf::Vector2f&  sz   = sprites[0].getSize       ();
                  sf::Vector2f   spos = sprites[0].getPosition   ();

            spos.x += (sz.x - rtxt.width ) / 2;
            spos.y += (sz.y - rtxt.height) / 2;

            text.setPosition(spos.x, spos.y);
        }

        static ButtonStyleCollection collection;
    };
    ButtonStyleCollection Button::collection;

    ///------------------------------------------------------------------------|
    /// ButtonsHolder.
    ///------------------------------------------------------------------------:
    struct  ButtonsHolder : public sf::Drawable
    {       ButtonsHolder(sf::RenderWindow& win) : window(win)
            {
                //auto win_sz = sf::Vector2f(window.getSize());

                float H = 10.f;

                bts.push_back(Button(L"ИГРА",     "/1/"));
                bts.back().setPosition({0,    H        });

                bts.push_back(Button(L"Tuning",   "/1/"));
                bts.back().setPosition({0,    H += step});

                bts.push_back(Button(L"1",      "/1/"));
                bts.back().setPosition({0,    H += step});

                bts.push_back(Button(L"2",      "/1/"));
                bts.back().setPosition({0,    H += step});

                bts.push_back(Button(L"3",      "/0/"));
                bts.back().setPosition({0,    H += step});

                bts.push_back(Button(L"4",      "/0/"));
                bts.back().setPosition({0,    H += step});

                bts.push_back(Button(L"5",      "/2/"));
                bts.back().setPosition({0,    H += step});
            }

        void prosses(const sf::Vector2i& mouse_pos, sf::Event& event)
        {   for(auto& b : bts) b.prosses(mouse_pos, event);
        }

        bool setCallback(std::wstring_view name, std::function<void()> cb)
        {   for(auto& e : bts)
            {   if( e.name == name)
                {   e.setCallback(cb); return true;
                }
            }
            return false;
        }

    private:
        std::vector<Button>  bts;
        sf::RenderWindow& window;

        float step = 25;

        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates  states) const
        {
            for(auto& b : bts) target.draw(b, states);
        }
    };
}

///----------------------------------------------------------------------------|
/// testclass.
///----------------------------------------------------------------------------:
inline void testclass_ButtonStyle()
{   ui::ButtonStyle bs("/2/");
}
