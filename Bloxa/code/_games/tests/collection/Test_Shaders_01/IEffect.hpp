#ifndef EFFECT_HPP
#define EFFECT_HPP

////////////////////////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// Base class for effects
////////////////////////////////////////////////////////////////////////////////
struct       IEffect : public sf::Drawable
{
    virtual ~IEffect(){}

    static void setFont(const sf::Font& font)
    {   s_font = &font;
    }

    const std::string_view getName() const { return m_name; }

    void load() ///-------------------------------------------------------: load
    {   m_isLoaded = sf::Shader::isAvailable() && onLoad();
    }

    void update(float  time, float x, float y) ///----------------------: update
    {   if(m_isLoaded) onUpdate(time, x,    y);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const ///: draw
    {
        if (m_isLoaded)
        {
            onDraw(target, states);
        }
        else
        {
            sf::Text error("Shader not\nsupported", getFont());
            error .setCharacterSize(36);

            error.setOrigin(error.getGlobalBounds().width  / 2,
                            error.getGlobalBounds().height / 2);

            target.draw (error, states);
        }
    }

    static const sf::Font& getFont()
    {   assert    (s_font != NULL);
        return    *s_font;
    }

protected:
    IEffect(const std::string_view& name) : m_name    (name ),
                                            m_isLoaded(false)
    {
    }

private:
    virtual bool onLoad                              () = 0;
    virtual void onUpdate(float time, float x, float y) = 0;
    virtual void onDraw(sf::RenderTarget& target,
                        sf::RenderStates  states) const = 0;
private:
    const std::string      m_name    ;
    bool                   m_isLoaded;
    static const sf::Font* s_font    ;
};

inline const std::string DIR{"test-Shaders/"};

#endif // EFFECT_HPP
