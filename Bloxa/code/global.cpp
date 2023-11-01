///----------------------------------------------------------------------------|
/// Global.
///----------------------------------------------------------------------------:
#include "global.h"

Cfg            cfg_default;
Cfg* Cfg::p = &cfg_default;

float             Global::deltaTime =     0.0;
sf::Font*         Global::font      = nullptr;
sf::RenderWindow* Global::pwindow   = nullptr;
