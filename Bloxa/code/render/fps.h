#ifndef FPS_H
#define FPS_H
///----------------------------------------------------------------------------|
/// "fps.h"
///----------------------------------------------------------------------------:
#include "../global.h"

///----------------------------------------------------------------------------|
/// Инфа о FPS.
///----------------------------------------------------------------------------:
struct  Fps : public sf::Text, protected Global
{       Fps(const sf::View& view)
        {
            setFont                  (*font);
            setCharacterSize           (14);
            setStyle    (sf::Text::Regular);
            setFillColor(sf::Color(0,255,0));

            auto sz = view.getSize();
            setPosition({float(-sz.x/2 + PAD), -sz.y/2 + PAD});
        }

    void update()
    {
        if (f  += deltaTime; f > 1.f)
        {   f  -= 1.f;
            uptext ();
            cnt =   1;
        }
        else    ++cnt;
    }

private:
    int  cnt =  1  ;
    float  f =  0.f;

    const float PAD = 10;

    void uptext()
    {   std::string s("FPS: ");
                    s += std::to_string(cnt);
        setString  (s);
        //dub2right  ( );
    }

    void dub2right()
    {   const sf::FloatRect& BOUND = getLocalBounds();
        if(BOUND.width > Cfg::p->winsize.x - getPosition().x)
        {   setPosition({Cfg::p->winsize.x - BOUND.width - PAD, PAD});
        }
    }
};

#endif // FPS_H
