#ifndef RESOURCES_H
#define RESOURCES_H
///----------------------------------------------------------------------------|
/// "resources.h"
///----------------------------------------------------------------------------:
#include "../mylib/mylib.h"

namespace Resource
{
    ///------------------------------------------------------------------------|
    /// Фон GUI.
    ///------------------------------------------------------------------------:
    struct  Background : sf::RectangleShape
    {       Background(const sf::RenderWindow& window)
            {   t.loadFromFile("img/bg.png");
                setTexture(&t);
                setSize   (sf::Vector2f(window.getSize().x,
                                        window.getSize().y));
            }

    private:
        sf::Texture t;
    };

    ///------------------------------------------------------------------------|
    /// Фон BlocksWin.
    ///------------------------------------------------------------------------:
    struct  BlocksWin : sf::RectangleShape
    {       BlocksWin(const sf::RenderWindow& window,
                      const sf::View&         view  )

            {
                setSize(sf::Vector2f(view.getSize().x-thickness*2,
                                     view.getSize().y-thickness*2));

                setFillColor   (sf::Color::White    );
                setOutlineColor(sf::Color(64,64,128));
                setOutlineThickness       (thickness);

                myl::setOrigin(*this);
            }

    private:
        const float thickness = 4;
    };

    ///------------------------------------------------------------------------|
    /// Фон GameWin.
    ///------------------------------------------------------------------------:
    struct  GameWin : sf::RectangleShape
    {       GameWin(const sf::RenderWindow& window,
                    const sf::View&         view  )
            {
                setSize   (sf::Vector2f(view.getSize().x-thickness*2,
                                        view.getSize().y-thickness*2));
                setFillColor   (sf::Color( 0, 0,64 ));
                setOutlineColor(sf::Color(255,255,255));
                setOutlineThickness       (thickness);

                myl::setOrigin(*this);
            }

    private:
        const float thickness = 4;
    };

    ///------------------------------------------------------------------------|
    /// Фон лога.
    ///------------------------------------------------------------------------:
    struct  LogWin : sf::RectangleShape
    {       LogWin(const sf::RenderWindow& window,
                   const sf::View&         view  )
            {
                setSize(sf::Vector2f(view.getSize().x-thickness*2,
                                     view.getSize().y-thickness*2));

                setFillColor   (sf::Color::Black  );
                setOutlineColor(sf::Color::White  );
                setOutlineThickness     (thickness);

                myl::setOrigin(*this);
            }

    private:
        const float thickness = 4;
    };

    ///------------------------------------------------------------------------|
    /// Текст заголовка.
    ///------------------------------------------------------------------------:
    struct  HeaderStr : sf::Text
    {       HeaderStr()
            {
                font.loadFromFile  ("C:/windows/fonts/arial.ttf");///<-------!!!

                setFont                 (font);
                setCharacterSize          (28);
                setStyle  (sf::Text::Regular );
                setFillColor(sf::Color::Black);
                setString(L"Конструктор Блок-Схем");

                setPosition(270, 0);
            }

    private:
        sf::Font font;
    };
}

namespace res = Resource;

#endif // RESOURCES_H
