#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "MineCounter.h"
#include <stdio.h>
#include <vector>

MineCounter::MineCounter(){
    mines = 50;
    counterNumber = mines;
    MineCounter::SetCounter();
}

void MineCounter::ModifyMines(int difference){
    mines += difference;
}
std::vector<sf::Sprite> MineCounter::GetCounter(){
    MineCounter::SetCounter();
    return counter;
}

void MineCounter::SetCounter(){
    counter.clear();
    
    sf::Sprite singleDigit;
    singleDigit.setTexture(TextureManager::GetTexture("digits"));
    string strCounter;
    
    strCounter = std::to_string(counterNumber);
    //char tempStrPos[4], tempStrNeg[5];
    bool neg = false;
    char posCharArr[4], negCharArr[5];
    int comparisonNumber = 0;
    
    if(strCounter[0] == '-'){
        neg = true;
        comparisonNumber = counterNumber * -1;
    } else{
        comparisonNumber = counterNumber;
    }
    
    if(comparisonNumber <= 400 && comparisonNumber >= 100){
        
        if(!neg){
            posCharArr[0] = strCounter[0];
            posCharArr[1] = strCounter[1];
            posCharArr[2] = strCounter[2];
            posCharArr[3] = '\0';
            
            strCounter = posCharArr;
        } else{
            negCharArr[0] = '-';
            negCharArr[1] = strCounter[1];
            negCharArr[2] = strCounter[2];
            negCharArr[3] = strCounter[3];
            negCharArr[4] = '\0';
            
            strCounter = negCharArr;
        }
        
    } else{
        if(comparisonNumber <= 99 && comparisonNumber >= 10){
            
            if(!neg){
                posCharArr[0] = '0';
                posCharArr[1] = strCounter[0];
                posCharArr[2] = strCounter[1];
                posCharArr[3] = '\0';
                
                strCounter = posCharArr;
            } else{
                negCharArr[0] = '-';
                negCharArr[1] = '0';
                negCharArr[2] = strCounter[1];
                negCharArr[3] = strCounter[2];
                negCharArr[4] = '\0';
                
                strCounter = negCharArr;
            }
        } else{
            if(comparisonNumber >= 0 && comparisonNumber < 10){
                
                if(!neg){
                    posCharArr[0] = '0';
                    posCharArr[1] = '0';
                    posCharArr[2] = strCounter[0];
                    posCharArr[3] = '\0';
                    
                    strCounter = posCharArr;
                }else{
                    negCharArr[0] = '-';
                    negCharArr[1] = '0';
                    negCharArr[2] = '0';
                    negCharArr[3] = strCounter[1];
                    negCharArr[4] = '\0';
                    
                    strCounter = negCharArr;
                }
            }
        }
    }
    
    for(int i = 0; i < strCounter.size(); i++){
        switch(strCounter[i]){
            case '0':{
                
                singleDigit.setTextureRect(sf::IntRect(0, 0, 21, 32));
            }
                break;
            case '1':{
                singleDigit.setTextureRect(sf::IntRect(21, 0, 21, 32));
            }
                break;
            case '2':{
                singleDigit.setTextureRect(sf::IntRect(42, 0, 21, 32));
            }
                break;
            case '3':{
                singleDigit.setTextureRect(sf::IntRect(63, 0, 21, 32));
            }
                break;
            case '4':{
                singleDigit.setTextureRect(sf::IntRect(84, 0, 21, 32));
            }
                break;
            case '5':{
                singleDigit.setTextureRect(sf::IntRect(105, 0, 21, 32));
            }
                break;
            case '6':{
                singleDigit.setTextureRect(sf::IntRect(126, 0, 21, 32));
            }
                break;
            case '7':{
                singleDigit.setTextureRect(sf::IntRect(147, 0, 21, 32));
            }
                break;
            case '8':{
                singleDigit.setTextureRect(sf::IntRect(168, 0, 21, 32));
            }
                break;
            case '9':{
                singleDigit.setTextureRect(sf::IntRect(189, 0, 21, 32));
            }
                break;
            case '-':{
                singleDigit.setTextureRect(sf::IntRect(210, 0, 21, 32));
            }
                break;
        }

        counter.push_back(singleDigit);
    }
}

void MineCounter::SetMines(int mines){
    this -> mines = mines;
    SetCounter();
}

void MineCounter::SetCounterNumber(int counterNumber){
    this -> counterNumber = counterNumber;
    SetCounter();
}

void MineCounter::PrintCounter(sf::RenderWindow &window){
    for(unsigned long int i = 0; i < this ->counter.size(); i++){
        this->counter[i].setPosition(0 + (21 *  i), 512);
        window.draw(counter[i]);
    }
}

void MineCounter::DecrementCounter(bool aMine){
    if(aMine){
        SetMines(this-> mines - 1);
        SetCounterNumber(this -> counterNumber - 1);
    } else{
        SetCounterNumber(this -> counterNumber - 1);
    }
}

void MineCounter::IncrementCounter(bool aMine){
    if(aMine){
        SetMines(this-> mines + 1);
        SetCounterNumber(this -> counterNumber + 1);
    } else{
        SetCounterNumber(this -> counterNumber + 1);
    }
}
