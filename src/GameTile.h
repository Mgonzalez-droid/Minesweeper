#ifndef GameTile_h
#define GameTile_h
#include <SFML/Graphics.hpp>

struct GameTile{
    sf::Sprite tile;
    bool isClicked;
    float x;
    float y;
    
    virtual void SetTileSprite() = 0;
};


#endif /* GameTile_h */
