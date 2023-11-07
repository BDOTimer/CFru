#ifndef CAMERAS_H
#define CAMERAS_H
///----------------------------------------------------------------------------|
/// "cameras.h"
///----------------------------------------------------------------------------:
#include "../global.h"

namespace Cameras
{
    ///-------------------------|
    /// Интерфейс камеры.       |
    ///-------------------------:
    struct      Camera : sf::View
    {   virtual~Camera(){}

        void keyboard (){ /* ... ? */ }

    private:
        /// ...
    };

    ///-------------------------|
    /// Камера игры.            |
    ///-------------------------:
    struct  CameraGUI : Camera
    {       CameraGUI(const sf::RenderWindow& window)
            {   *((sf::View*)(this)) = window.getView();
            }

    private:
    };

    ///-------------------------|
    /// Камера редактора.       |
    ///-------------------------:
    struct  CameraRed : Camera
    {       CameraRed(const sf::RenderWindow& window)
            {   setCenter( 0, 0);
            }

    private:
        /// ...
    };

    ///-------------------------|
    /// Камера игры.            |
    ///-------------------------:
    struct  CameraGame : Camera
    {       CameraGame(const sf::RenderWindow& window)
            {   setCenter( 0, 0);
            }

    private:
    };

    ///-------------------------|
    /// Камера лога.            |
    ///-------------------------:
    struct  CameraLog : Camera
    {       CameraLog(const sf::RenderWindow& window)
            {   setCenter( 0, 0);
            }

    private:
    };

    enum class eCAMERA
    {   E_GUI ,
        E_RED ,
        E_GAME,
        E_LOG
    };

    ///------------------------------------------------------------------------|
    /// Менеджер камер.
    ///------------------------------------------------------------------------:
    struct  ManagerCameras
    {       ManagerCameras(sf::RenderWindow& w) : window(w)
            {   m.push_back(new CameraGUI (window));
                m.push_back(new CameraRed (window));
                m.push_back(new CameraGame(window));
                m.push_back(new CameraLog (window));

                ///-------------------------|
                /// Описатель топологии.    |
                ///-------------------------:
                const float X0 = 0.10f;
                const float X1 = 0.50f;
                const float Y0 = 0.07f;
                const float Y1 = 0.81f;

                const float W0 = 0.39f;
                const float W1 = 0.49f;
                const float W3 = 0.39f;
                const float H0 = 0.73f;
                const float H1 = 0.18f;
                ///-------------------------.

                m[1]->setViewport(sf::FloatRect(X0, Y0, W0, H0));
                m[2]->setViewport(sf::FloatRect(X1, Y0, W1, H0));
                m[3]->setViewport(sf::FloatRect(X1, Y1, W3, H1));

                setSize(m[1]);
                //setSize(m[2]);
                m[2]->setSize(800,600);
                setSize(m[3]);

                //m[2]->zoom( .3f);

            }
           ~ManagerCameras() { for(auto& p : m) delete p; }

    sf::View& get(eCAMERA T) { return *(sf::View*)(m[size_t(T)]);}

    void set(eCAMERA T)
    {   window.setView(*(sf::View*)(m[size_t(T)]));
    }

    private:
        std::vector<Camera*>   m;
        sf::RenderWindow& window;

        ///-------------------------|
        /// Актуальный размер.      |
        ///-------------------------:
        void setSize(Camera* p)
        {
            sf::FloatRect psz = p->getViewport();
            sf::Vector2u  wsz = window.getSize();

            p->setSize(psz.width * wsz.x, psz.height * wsz.y);
        }
    };
}

namespace cam = Cameras;

#endif // CAMERAS_H
