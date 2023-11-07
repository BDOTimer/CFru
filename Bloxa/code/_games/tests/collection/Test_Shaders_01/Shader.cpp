/// #define SFML_STATIC
////////////////////////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <cmath>

#include "!start.h"

#include "tile.h"
#include "shaders_sdk.h"
#include "shaders_toy.h"

std::string clip_annex(std::string  s)
{   return  s.substr(s.rfind("Source"), s.size());
}

const sf::Font* IEffect::s_font = NULL;

const sf::Vector2f getxy(const sf::RenderWindow& win)
{   return sf::Vector2f (
        static_cast<float>(sf::Mouse::getPosition(win).x) / win.getSize().x,
        static_cast<float>(sf::Mouse::getPosition(win).y) / win.getSize().y
    );
}


///----------------------------------------------------------------------------|
/// TestShaders.
///----------------------------------------------------------------------------:
struct  TestShaders : obj::IObject, Global //sf::Drawable
{       TestShaders(sf::View& v) : view(v)
        {
            view.setCenter(sf::Vector2f(0.f, 0.f));

            load_effects();

            ASSERT(current < effects.size());

            const auto& font = IEffect::getFont();

            nameef = CEstr + effects[current]->getName().data();


            if (!BackgroundTexture.
                 loadFromFile(DIR + "resources/text-background.png"))
            {   std::cerr << "ERROR: load texture\n"; return;// EXIT_FAILURE;
            }

            auto sz = view.getSize();

            textBackground.setTexture (BackgroundTexture);
            textBackground.setPosition(-sz.x/2, sz.y/2 - 60);
            textBackground.setColor   (sf::Color(255, 255, 255, 255));

            description.setFont         (font);
            description.setCharacterSize(20);
            description.setString       (nameef);
            description.setPosition     (-sz.x/2, sz.y/2 - 60);
            description.setFillColor    (sf::Color(0, 0, 0));

            instructions.setFont         (font);
            instructions.setCharacterSize(20);
            instructions.setString(
                    "Press left and right arrows to change the current shader");
            instructions.setPosition (-sz.x/2, sz.y/2 - 30);
            instructions.setFillColor(sf::Color(80, 80, 80));
        }
       ~TestShaders(){ del_effects(); }

    std::size_t        current{};
    std::string        nameef   ;

    ///-------------------------|
    /// Create the effects.     |
    ///-------------------------:
    std::vector<IEffect*> effects;

    sf::Texture BackgroundTexture;

    sf::Sprite  textBackground;
    sf::Text    description   ;
    sf::Text    instructions  ;

    const std::string CEstr = "Current effect: ";

    void update(const sf::Vector2f& xy, float sec)
    {   effects[current]->update(sec, xy.x,  xy.y);
    }

    void effect_next()
    {   if (current == effects.size() - 1) current = 0;
        else                               current++;

        description.setString(CEstr + effects[current]->getName().data());
        LOG << description.getString().toWideString() << '\n';
    }

    void effect_back()
    {   if (current == 0) current = effects.size() - 1;
        else              current--;

        description.setString(CEstr + effects[current]->getName().data());
        LOG << description.getString().toWideString() << '\n';
    }

    ///------------------------------------------------------------------------|
    /// Интерфейс.
    ///------------------------------------------------------------------------:
    ///-----------------------------------------|
    /// ...                                     |
    ///-----------------------------------------:
    double time = 0.0;
    void update()
    {   time += deltaTime;

        update(getxy(*pwindow), time);
    }

    ///-----------------------------------------|
    /// ...                                     |
    ///-----------------------------------------:
    bool RPControl(std::string_view command, std::vector<float>& arg)
    {
        /// TODO2 ...

        l(command)

        return false;
    }

    ///-----------------------------------------|
    /// ...                                     |
    ///-----------------------------------------:
    void input(const sf::Event& event)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Left:
                effect_back();
                break;

            case sf::Keyboard::Right:
                effect_next();
                break;

            default:
                break;
        }
    }
    ///------------------------------------------------------------------------.

private:
    ///-------------------|
    /// На рендер.        |
    ///-------------------:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates  states) const
    {
        target.draw(*effects[current], states);
        target.draw(textBackground, states);
        target.draw(description   , states);
        target.draw(instructions  , states);
    }

    ///-----------------|
    /// Камера.         |
    ///-----------------:
    sf::View&       view;

    ///-------------------|
    /// Загрузка эффектов.|
    ///-------------------:
    void load_effects()
    {     del_effects();

        for(const auto shader : nameshader)
        {   effects.push_back(new toy::myEffect(DIR + shader));
        }

        ///---------------|
        /// SDK.          |
        ///---------------:
        effects.push_back(new sdk::Pixelate  );
        effects.push_back(new sdk::WaveBlur  );
        effects.push_back(new sdk::StormBlink);
        effects.push_back(new sdk::Edge      );
        effects.push_back(new sdk::Geometry  );

        l(effects.size())
    }

    void del_effects()
    {   for (auto& e : effects) delete e; effects.clear();
    }

    ///-----------------------|
    /// Name of shader.       |
    ///-----------------------:
    const char* const nameshader[2]
    {   "restoy/shader_toy.frag"        ,              /// 0
        "restoy/shader_toy_cloud2d.frag"               /// 1
      //"restoy/shader_toy_Voxels_in_480_chars.frag"   /// 2
    };
};

namespace Test_Shaders_01
{
    obj::IObject* create(sf::View& v)
    {
        IEffect::setFont(*Global::getFont());

        return new TestShaders(v);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// not use.
////////////////////////////////////////////////////////////////////////////////
int xmain()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shader",
                            sf::Style::Titlebar | sf::Style::Close);
                     window.setVerticalSyncEnabled(true);

    sf::View view = window.getDefaultView();

    ///----------------------|
    /// Глобал-инициализация.|
    ///----------------------:
    //Global::init();

    //Tile tile("myres/background.jpg");

    ///----------------------|
    /// testShaders.         |
    ///----------------------:
    TestShaders   testShaders(view);

    sf::Clock           clock;

    ///----------------------|
    /// Start the game loop. |
    ///----------------------:
    while (window.isOpen())
    {
        for (sf::Event event; window.pollEvent(event); )
        {
            if (event.type == sf::Event::Closed    ) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;

                    default:
                        testShaders.input(event);
                        break;
                }
            }
        }

        ///------------------------|
        /// Update the now effect. |
        ///------------------------:
        const sf::Vector2f xy = getxy(window);
        testShaders.update(xy,  clock.getElapsedTime().asSeconds());

        window.clear(sf::Color(0, 128, 128));

        ///------------------------|
        /// Draw ...               |
        ///------------------------:
        // window.draw( tile);

        ///------------------------|
        /// Draw the testShaders.  |
        ///------------------------:
        window.draw(testShaders   );

        window.display();
    }

    return EXIT_SUCCESS;
}
