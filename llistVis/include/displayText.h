#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include "SFML\Graphics.hpp"
#include "assetManager.h"
class DisplayText : public sf::Text
{
public:
	DisplayText(AssetManager* assets, sf::Vector2f position);
	void update(sf::Time dt);
	void draw(sf::RenderWindow& window);
	void setMessage(std::string newString);
private:
	bool visible;
	float elapsedTime;
	float fadeTime;
	sf::Color color;
	sf::Vector2f pos;
};

#endif