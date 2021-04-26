#include <stdio.h>
#include "GameAction.h"
#include "BoardTile.h"
#include "PropertyTile.h"
#include "Random.h"
#include "MineCounter.h"
#include <map>
#include <vector>
#include <fstream>
#include "TextureManager.h"

void SetRandomMines(std::vector<BoardTile> &tiles, MineCounter &myMines);

void ResetDefaults(std::vector<BoardTile> &tiles, sf::Sprite& face){
    for(unsigned long int i = 0; i < tiles.size(); i++){
        tiles[i].ResetDefauts();
    }
    
    //Reset happy face
    face.setTexture(TextureManager::GetTexture("face_happy"));
}

void RevealMineTiles(std::vector<BoardTile> &tiles,std::vector<sf::Sprite> &backgroundTiles, MineCounter &myCounter, bool gameOver){
    
    for(unsigned long int i = 0; i < tiles.size(); i++){
        if(tiles[i].mine == true && !tiles[i].flagged){
            tiles[i].RevealMines(backgroundTiles[i],myCounter, gameOver);
        }
    }
}

void GameAction::StartNewGame(std::vector<BoardTile> &tiles, MineCounter &myMines, sf::Sprite& face, bool test, int testNum){
    
    ResetDefaults(tiles, face);
    
    
    if(test){
        
        switch(testNum){
            case 1:{
                
                int mines = 0;
                std::vector<BoardTile> tilesTestOne = LoadTestOne();
                for(unsigned long int i = 0; i < tilesTestOne.size(); i++){
                    tiles[i].mine = tilesTestOne[i].mine;
                    
                    if(tiles[i].mine)
                        mines++;
                }
                
                for(unsigned long int i = 0; i < tiles.size(); i++)
                tiles[i].AssignNeighbors(tiles);
                
                myMines.SetMines(mines);
                myMines.SetCounterNumber(mines);
            }
                break;
                
            case 2:{
                
                int mines = 0;
                std::vector<BoardTile> tilesTestTwo = LoadTestTwo();
                for(unsigned long int i = 0; i < tilesTestTwo.size(); i++){
                    tiles[i].mine = tilesTestTwo[i].mine;
                    
                    if(tiles[i].mine)
                        mines++;
                }
                
                for(unsigned long int i = 0; i < tiles.size(); i++)
                tiles[i].AssignNeighbors(tiles);
                myMines.SetMines(mines);
                myMines.SetCounterNumber(mines);
            }
                break;
                
            case 3:{
                
                int mines = 0;
                std::vector<BoardTile> tilesTestThree = LoadTestThree();
                for(unsigned long int i = 0; i < tilesTestThree.size(); i++){
                    tiles[i].mine = tilesTestThree[i].mine;
                    
                    if(tiles[i].mine)
                        mines++;
                }
                
                for(unsigned long int i = 0; i < tiles.size(); i++)
                tiles[i].AssignNeighbors(tiles);
                
                myMines.SetMines(mines);
                myMines.SetCounterNumber(mines);
            }
                break;
        }
    } else{
        //Normal game
        SetRandomMines(tiles, myMines);
        
        for(unsigned long int i = 0; i < tiles.size(); i++)
            tiles[i].AssignNeighbors(tiles);
    }
}

void SetRandomMines(std::vector<BoardTile> &tiles, MineCounter &myMines){
    int ranNum;
    std::map<int, bool> called;
    
    do{
        ranNum = Random::Int(0, 400);
        called[ranNum] = true;
    }while(called.size() != 50);
    
    for(auto iter = called.begin(); iter != called.end(); iter++){
        tiles[iter->first].mine = iter->second;
    }
    
    myMines.SetMines(50);
    myMines.SetCounterNumber(50);
    
}

void GameAction::EndGame(std::vector<BoardTile> &tiles, std::vector<sf::Sprite> &backgroundTiles,sf::Sprite& face, MineCounter &myCounter, bool win){
    
    if(win){
       //set face to cool guy face
        face.setTexture(TextureManager::GetTexture("face_win"));
        RevealMineTiles(tiles,backgroundTiles,myCounter,false);
    } else{
      //set face to sad face
        face.setTexture(TextureManager::GetTexture("face_lose"));
        RevealMineTiles(tiles,backgroundTiles,myCounter,true);
    }
    
    for(unsigned long int i = 0; i < tiles.size(); i++){
        //Game board unclickable
        tiles[i].clickable = false;
    }
    
    
    
}

void GameAction::DebugMode(std::vector<BoardTile> &tiles, sf::RenderWindow& window, bool debugModeOn){
    
    if(debugModeOn){
        for(unsigned long int i = 0; i < tiles.size(); i++){
            if(tiles[i].mine == true){
                sf::Sprite mine;
                mine.setTexture(TextureManager::GetTexture("mine"));
                mine.setPosition(tiles[i].x, tiles[i].y);
                
                window.draw(mine);
            }
        }
    }
}

std::vector<BoardTile> GameAction::LoadTestOne(){
    //load test one
    std::vector<BoardTile> tiles;
    BoardTile tempTile;
    //tempTile.clickable = true;
    std::ifstream file;
    file.open("boards/testboard1.brd");
    
    std::string input;
    
    while(!file.eof()){
        getline(file, input, '\n');
        
        for(int i = 0; i < 25; i++){
            int num = input[i];
            
            if(num == 49){
                tempTile.mine = true;
            } else{
                tempTile.mine = false;
            }
            
            tiles.push_back(tempTile);
        }
    }
    
    return tiles;
}

std::vector<BoardTile> GameAction::LoadTestTwo(){
    std::vector<BoardTile> tiles;
    BoardTile tempTile;
    //tempTile.clickable = true;
    std::ifstream file;
    file.open("boards/testboard2.brd");
    
    std::string input;
    
    while(!file.eof()){
        getline(file, input, '\n');
        
        for(int i = 0; i < 25; i++){
            int num = input[i];
            
            if(num == 49){
                tempTile.mine = true;
            } else{
                tempTile.mine = false;
            }
            
            tiles.push_back(tempTile);
        }
    }
    return tiles;
}

std::vector<BoardTile> GameAction::LoadTestThree(){
    std::vector<BoardTile> tiles;
    
    BoardTile tempTile;
    //tempTile.clickable = true;
    std::ifstream file;
    file.open("boards/testboard3.brd");
    
    std::string input;
    
    while(!file.eof()){
        getline(file, input, '\n');
        
        for(int i = 0; i < 25; i++){
            int num = input[i];
            
            if(num == 49){
                tempTile.mine = true;
                //tempTile.clickable = true;
            } else{
                tempTile.mine = false;
            }
            
            tiles.push_back(tempTile);
        }
    }
    
    return tiles;
}


