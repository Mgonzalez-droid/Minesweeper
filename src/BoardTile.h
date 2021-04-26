#ifndef BoardTile_h
#define BoardTile_h
#include <SFML/Graphics.hpp>
#include "GameTile.h"
#include <vector>
#include "MineCounter.h"
struct BoardTile : virtual public GameTile{
    bool mine;
    bool clickable;
    bool flagged;
    bool rightLocked;
    bool leftLocked;
    int number;
    std::vector<BoardTile*> neighbors;
    
  
    BoardTile();
    void ResetDefauts();
  
    sf::Sprite& GetTileSprite();
    void SetTileSprite();
    void AssignNeighbors(std::vector<BoardTile>& tiles);
    void SetNumber();
    void ClickingNeighbors();
    void Clicked(sf::Sprite &backgroundTile, std::string click, bool flagged = false, bool alreadyFlagged = false, bool unclick = false);
    void RevealMines(sf::Sprite &backgroundTile,MineCounter &mineCounter, bool gameOver);
};

#endif /* BoardTile_h */
