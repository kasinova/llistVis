#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include "SFML\Graphics.hpp"

class AssetManager
{
public:
	AssetManager();
	bool addTex(std::string name, std::string fileName);
	sf::Texture* getTexture(std::string name);
	sf::Font* getFont();

private:
	std::map<std::string, sf::Texture>textures;
	sf::Font font;
};

#endif