#ifndef TextureManager_h
#define TextureManager_h
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
using std::unordered_map;
using std::string;

class TextureManager{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(const char* filename);
public:
    static sf::Texture& GetTexture(const char* filename);
    static void Cear();
};

#endif /* TextureManager_h */
