#include "PropertyTile.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "GameAction.h"

PropertyTile::PropertyTile():GameTile(){
  isClicked = false;
}

sf::Sprite& PropertyTile::GetTileSprite(){
  return tile;
}
void PropertyTile::SetTileSprite(string& property){
  
}

void PropertyTile::RunProperty(){
  
}
