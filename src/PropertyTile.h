#ifndef PropertyTile_h
#define PropertyTile_h
#include <SFML/Graphics.hpp>
#include "GameTile.h"

struct PropertyTile : virtual public GameTile{
    PropertyTile();
  
    sf::Sprite& GetTileSprite();
    void SetTileSprite(std::string& property);
    void RunProperty();
    void Clicked();
};

#endif /* PropertyTile_h */
