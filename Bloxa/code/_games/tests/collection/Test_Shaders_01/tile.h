#ifndef TILE_H
#define TILE_H
///----------------------------------------------------------------------------|
/// "tile.h"
/// Инфа о тайле тут.
///----------------------------------------------------------------------------:
#include <SFML/Graphics.hpp>

struct  Tile : public sf::Sprite, sf::Texture
{       Tile()
        {
        }
        Tile(const sf::Texture& txtr)
        {   setTexture (txtr);
        }
        Tile(const char* namefile)
        {   sf::Texture::loadFromFile(namefile);
            sf::Sprite ::setTexture  (*this   );
        }

private:

};

#endif // TILE_H
