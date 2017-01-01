#include "../include/AssetManager.h"

AssetManager::AssetManager()
{
	if (!font.loadFromFile("../assets/arial.ttf"))
	{
		return;
	}
}

bool AssetManager::addTex(std::string name, std::string fileName)
{
	//checks if there is a texture by that key
	//if there isn't, make one
	//if there is, then getTexture will still return a texture
	if (getTexture(name) == NULL)
	{
		sf::Texture temp;
		temp.loadFromFile(fileName);
		textures.insert(std::pair<std::string, sf::Texture>(name, temp));
	}
	return true;
}

sf::Texture* AssetManager::getTexture(std::string name)
{
	std::map<std::string, sf::Texture>::iterator results = textures.find(name);
	if (textures.end() == results)
	{
		return NULL;
	}
	sf::Texture texp = results->second;
	return &results->second;
}
sf::Font* AssetManager::getFont()
{
	return &font;
}