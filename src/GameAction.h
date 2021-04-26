#ifndef GameAction_h
#define GameAction_h
#include "BoardTile.h"
#include "MineCounter.h"
#include <vector>
struct GameAction{
    
    bool GameRunning = false;
    bool win = false;
    bool lose = false;
    
    static void EndGame(std::vector<BoardTile> &tiles, std::vector<sf::Sprite> &backgroundTiles, sf::Sprite& face, MineCounter &myCounter, bool win = false);
    static void DebugMode(std::vector<BoardTile> &tiles, sf::RenderWindow& window, bool debugModeOn = false);
    static std::vector<BoardTile> LoadTestOne();
    static std::vector<BoardTile> LoadTestTwo();
    static std::vector<BoardTile> LoadTestThree();
    static void StartNewGame(std::vector<BoardTile> &tiles, MineCounter &myMines, sf::Sprite& face, bool test = false, int testNum = 0);
    
};

#endif /* GameAction_h */
