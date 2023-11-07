#ifndef SHADER_TOY_H
#define SHADER_TOY_H
///----------------------------------------------------------------------------|
/// "shaders_toy.h"
///----------------------------------------------------------------------------:

#define SIZEARR(A) sizeof A / sizeof *A

///----------------------------------------------------------------------------|
/// class Effect;
///----------------------------------------------------------------------------:
#include "IEffect.hpp"

namespace toy
{

///----------------------------------------------------------------------------|
/// "myEffect.frag" fragment shader                                       ---> 5
///----------------------------------------------------------------------------:
    struct  myEffect                      : public IEffect
    {       myEffect(std::string_view fn) :        IEffect(fn),
                filename(fn)
            {   load    (  );

                auto sz = m_sprite.getGlobalBounds();
                m_sprite.setOrigin(sz.width / 2, sz.height / 2);

                m_sprite.setScale  (2.f, 2.f);
            }

        std::string filename;

        bool onLoad()
        {   if (!m_texture.loadFromFile(DIR+"myres/background_min.jpg"))
                return false;

            m_sprite.setTexture(m_texture );
            if (!m_shader.loadFromFile(filename, sf::Shader::Fragment))
                return false;

            //m_shader.setUniform("textureA", sf::Shader::CurrentTexture);

            return true;
        }

        void onUpdate(float time, float x, float y)
        {   m_shader.setUniform("iTime", time       );
            //m_shader.setUniform("textureA"        , m_texture  );
            //m_shader.setUniform("pixel_threshold" ,(x + y) / 30);
        }

        void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
        {   states.shader = &m_shader;
            target.draw     (m_sprite, states);
        }

    private:
        sf::Texture m_texture;
        sf::Sprite  m_sprite ;
        sf::Shader  m_shader ;
    };
}

#endif // SHADER_TOY_H
