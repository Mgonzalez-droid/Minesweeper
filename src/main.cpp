#include <SFML/Graphics.hpp>
#include "Random.h"
#include "TextureManager.h"
#include <vector>
#include "BoardTile.h"
#include "MineCounter.h"
#include "GameAction.h"
#include <iostream>

using namespace std;

//prototypes
void revealedVictory(vector<BoardTile>& tiles, vector<sf::Sprite> &backgroundTiles, sf::Sprite& face, MineCounter& myCounter);

int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "Minesweeper");
    
    vector<BoardTile> tiles;
    vector<sf::Sprite> backgroundTiles;
    bool debugModeOn = false;
    
    float x = 0, y = 0;
    
        
       
       for(int i = 0; i < 400; i++){
           sf::Sprite newBackgroundTile;
           BoardTile newTile;
           if(i>0)
               x += 32.0f;
           
           if(i%25 == 0 && i != 0){
               y += 32.0f;
               x = 0;
           }
           
           newTile.tile.setPosition(x, y);
           newTile.x = x;
           newTile.y = y;
           
           newBackgroundTile.setPosition(x, y);
           newBackgroundTile.setTexture(TextureManager::GetTexture("tile_revealed"));
           
           backgroundTiles.push_back(newBackgroundTile);
           tiles.push_back(newTile);
       }
    
    MineCounter myCounter;
    
    sf::Sprite face, debug, test_1, test_2, test_3;
    face.setTexture(TextureManager::GetTexture("face_happy"));
    face.setPosition(368.0f, 512.0f);
    
    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition(496.0f, 512.0f);
    test_1.setTexture(TextureManager::GetTexture("test_1"));
    test_1.setPosition(560.0f, 512.0f);
    test_2.setTexture(TextureManager::GetTexture("test_2"));
    test_2.setPosition(624.0f, 512.0f);
    test_3.setTexture(TextureManager::GetTexture("test_3"));
    test_3.setPosition(688.0f, 512.0f);
    
    vector<BoardTile> tilesTestOne, tilesTestTwo, tilesTestThree;
    
    GameAction::StartNewGame(tiles, myCounter, face);
    
    for(int i = 0; i < tiles.size(); i++)
    tiles[i].AssignNeighbors(tiles);
    
    while(window.isOpen()){
        sf::Event event;
        
        //handle all events
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    auto pos = sf::Mouse::getPosition(window);
                    
                    //cout<<"LEFT: "<<"x: " << pos.x << " y: " << pos.y << endl;
                    
                    for(unsigned long int i = 0; i < tiles.size(); i++){
                        if(tiles[i].tile.getGlobalBounds().contains(sf::Vector2f(pos.x,pos.y)) && tiles[i].clickable){
                            tiles[i].Clicked(backgroundTiles[i],"LEFT", false);
                            if(tiles[i].mine && !tiles[i].rightLocked){
                                GameAction::EndGame(tiles, backgroundTiles, face,myCounter);
                            }
                        }
                    }
                    
                    if(test_1.getGlobalBounds().contains(sf::Vector2f(pos.x,pos.y))){
                        tilesTestOne = GameAction::LoadTestOne();
                        
                        GameAction::StartNewGame(tiles,myCounter, face, true, 1);
                    }
                    
                    if(test_2.getGlobalBounds().contains(sf::Vector2f(pos.x,pos.y))){
                        tilesTestTwo = GameAction::LoadTestTwo();
                        
                        GameAction::StartNewGame(tiles,myCounter, face, true, 2);
                    }
                    
                    if(test_3.getGlobalBounds().contains(sf::Vector2f(pos.x,pos.y))){
                        tilesTestThree = GameAction::LoadTestThree();
                        
                        GameAction::StartNewGame(tiles,myCounter, face, true, 3);
                    }
                    
                    if(debug.getGlobalBounds().contains(sf::Vector2f(pos.x,pos.y))){
                        if(!debugModeOn){
                            debugModeOn = true;
                        } else{
                            debugModeOn = false;
                        }
                    }
                    
                    if(face.getGlobalBounds().contains(sf::Vector2f(pos.x,pos.y))){
                        
                        /* CHECK THIS FUNTIONALITY!!!!!
                        //RESET GAME RevealTiles
                        GameAction::RevealTiles(tiles, true);
                         */
                        
                        GameAction::StartNewGame(tiles, myCounter, face);
                    }
                    
                } else if(event.mouseButton.button == sf::Mouse::Right){
                    auto pos = sf::Mouse::getPosition(window);
                    
                    //cout<<"RIGHT: "<<"x: " << pos.x << " y: " << pos.y << endl;
                    
                    for(unsigned long int i = 0; i < tiles.size(); i++){
                        if(tiles[i].tile.getGlobalBounds().contains(sf::Vector2f(pos.x,pos.y)) && tiles[i].clickable){
                            
                            if(tiles[i].flagged && !tiles[i].leftLocked){
                                tiles[i].Clicked(backgroundTiles[i],"RIGHT",true,true);
                                myCounter.IncrementCounter(tiles[i].mine);
                            } else{
                                
                                if(!tiles[i].leftLocked){
                                    tiles[i].Clicked(backgroundTiles[i],"RIGHT",true);
                                    myCounter.DecrementCounter(tiles[i].mine);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //update the game here, draw object etc...
        revealedVictory(tiles,backgroundTiles, face, myCounter);
        
        
        window.clear(sf::Color::White);
        
        for(unsigned long int i = 0; i < backgroundTiles.size(); i++)
            window.draw(backgroundTiles[i]);
            
        for(unsigned long int i = 0; i < tiles.size();i++)
            window.draw(tiles[i].tile);
        
        GameAction::DebugMode(tiles,window,debugModeOn);
                
        window.draw(face);
        
        myCounter.PrintCounter(window);
        window.draw(debug);
        window.draw(test_1);
        window.draw(test_2);
        window.draw(test_3);
        window.display();
    }
    return 0;
}
/*
 *
 *  Fix THIs we need to be able to win if all tiles are revealed with no flagged mines
 *
 */
void revealedVictory(vector<BoardTile>& tiles, vector<sf::Sprite> &backgroundTiles, sf::Sprite& face, MineCounter& myCounter){
    for(unsigned long int i = 0; i < tiles.size(); i++){
        if(!tiles[i].isClicked && !tiles[i].mine)
            return;
            //cancel victory if a tile is unclicked
        
        
        if(tiles[i].flagged && !tiles[i].mine)
            return;
            //cancel victory if find not flagged
    }
    GameAction::EndGame(tiles, backgroundTiles, face, myCounter, true);
}
