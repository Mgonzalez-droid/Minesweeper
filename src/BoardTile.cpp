#include "BoardTile.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>

BoardTile* FindTile(std::vector<BoardTile>& tiles, float x, float y);

BoardTile::BoardTile():GameTile(){
    isClicked = false;
    clickable = true;
    mine = false;
    number = 0;
    rightLocked = false;
    leftLocked = false;
    flagged = false;
    SetTileSprite();
}

void BoardTile::ResetDefauts(){
    isClicked = false;
    clickable = true;
    mine = false;
    number = 0;
    rightLocked = false;
    leftLocked = false;
    flagged = false;
    SetTileSprite();
}

sf::Sprite& BoardTile::GetTileSprite(){
  return tile;
}
void BoardTile::SetTileSprite(){
  if(isClicked == false){
        tile.setTexture(TextureManager::GetTexture("tile_hidden"));
    } else{
        
        if(isClicked && (mine || flagged || number > 0)){
            if(number){
                switch(number){
                    case 1:
                        tile.setTexture(TextureManager::GetTexture("number_1"));
                        break;
                    case 2:
                        tile.setTexture(TextureManager::GetTexture("number_2"));
                        break;
                    case 3:
                        tile.setTexture(TextureManager::GetTexture("number_3"));
                        break;
                    case 4:
                        tile.setTexture(TextureManager::GetTexture("number_4"));
                        break;
                    case 5:
                        tile.setTexture(TextureManager::GetTexture("number_5"));
                        break;
                    case 6:
                        tile.setTexture(TextureManager::GetTexture("number_6"));
                        break;
                    case 7:
                        tile.setTexture(TextureManager::GetTexture("number_7"));
                        break;
                    case 8:
                        tile.setTexture(TextureManager::GetTexture("number_8"));
                        break;
                }
            }
            
            if(mine){
                tile.setTexture(TextureManager::GetTexture("mine"));
            }
            
            if(flagged){
                tile.setTexture(TextureManager::GetTexture("flag"));
            }
            
        } else{
           tile.setTexture(TextureManager::GetTexture("tile_revealed"));
        }
    }
}

void BoardTile::SetNumber(){
    int number = 0;
    
    for(unsigned long int i = 0; i < neighbors.size(); i++){
        if(neighbors[i]->mine == true){
            number++;
        }
    }
    this -> number = number;
    SetTileSprite();
}

void BoardTile::AssignNeighbors(std::vector<BoardTile>& tiles){
    
    neighbors.clear();
    
    BoardTile* adjacentOne = FindTile(tiles, x - 32.0f, y - 32.0f);
    BoardTile* adjacentTwo = FindTile(tiles, x + 32.0f, y - 32.0f);
    BoardTile* adjacentThree = FindTile(tiles, x + 32.0f, y + 32.0f);
    BoardTile* adjacentFour = FindTile(tiles, x - 32.0f, y + 32.0f);
    BoardTile* above = FindTile(tiles, x , y - 32.0f);
    BoardTile* below = FindTile(tiles, x, y + 32.0f);
    BoardTile* left = FindTile(tiles, x - 32.0f, y);
    BoardTile* right = FindTile(tiles, x + 32.0f, y);
    
    if(adjacentOne != nullptr)
        neighbors.push_back(adjacentOne);
        
    if(adjacentTwo != nullptr)
        neighbors.push_back(adjacentTwo);
        
    if(adjacentThree != nullptr)
        neighbors.push_back(adjacentThree);
    
    if(adjacentFour != nullptr)
    neighbors.push_back(adjacentFour);
        
    if(above != nullptr)
        neighbors.push_back(above);
        
    if(below != nullptr)
        neighbors.push_back(below);
        
    if(left != nullptr)
        neighbors.push_back(left);
        
    if(right != nullptr)
        neighbors.push_back(right);
    
    SetNumber();
}

BoardTile* FindTile(std::vector<BoardTile>& tiles, float x, float y){
    
    BoardTile* pntr = nullptr;
    
    if((x < 0 || y < 0) && (x < 800 || y < 512)){
        return pntr;
    } else{
        for(unsigned long int i = 0; i < tiles.size(); i++){
            if(tiles[i].x == x && tiles[i].y == y){
                pntr = &tiles[i];
            }
        }
    }
    
    return pntr;
}

void BoardTile::ClickingNeighbors(){
    this->isClicked = true;
    if(!(this-> mine) && this -> number == 0){
        for(unsigned long int i = 0; i < neighbors.size(); i++){
            if(!(neighbors[i]->mine) && neighbors[i]->isClicked == false){
                neighbors[i]->isClicked = true;
                neighbors[i]->clickable = false;
                neighbors[i]->leftLocked = true;
                neighbors[i]->SetTileSprite();
                neighbors[i]->ClickingNeighbors();
            }
        }
    }
}

void BoardTile::Clicked(sf::Sprite &backgroundTile,std::string click, bool flagged, bool alreadyFlagged, bool unclick){
    
    if(clickable && click == "LEFT" && rightLocked != true){
        if(flagged == false){
            isClicked = true;
            clickable = false;
            leftLocked = true;
            SetTileSprite();
            ClickingNeighbors();
            return;
        } else{
            return;
        }
    }
    
    if(rightLocked && click == "LEFT")
        return;
    
    if(clickable && click == "RIGHT" && !leftLocked){
        
        if(alreadyFlagged){
            this -> flagged = false;
            isClicked = false;
            rightLocked = false;
            SetTileSprite();
            backgroundTile.setTexture(TextureManager::GetTexture("tile_revealed"));
            
            return;
        }
        
        if(flagged){
            this -> flagged = flagged;
            isClicked = true;
            SetTileSprite();
            rightLocked = true;
            backgroundTile.setTexture(TextureManager::GetTexture("tile_hidden"));
            
        }
        
    }
}

void BoardTile::RevealMines(sf::Sprite &backgroundTile,MineCounter &mineCounter, bool gameOver){
    if(gameOver){
        tile.setTexture(TextureManager::GetTexture("mine"));
    } else{
        Clicked(backgroundTile,"RIGHT",true);
        
        mineCounter.DecrementCounter(true);
    }
}


