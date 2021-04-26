#include "TextureManager.h"
#include <stdio.h>

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const char* filename){
    string filePath = "images/";
    filePath += filename;
    filePath += ".png";
    
    textures[filename].loadFromFile(filePath);
}

sf::Texture& TextureManager::GetTexture(const char* textureKey){
    if(textures.find(textureKey) == textures.end()){
        LoadTexture(textureKey);
    }
    return textures[textureKey];
}

void TextureManager::Cear(){
    textures.clear();
}

