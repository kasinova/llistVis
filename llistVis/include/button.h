#ifndef BUTTON_H
#define BUTTON_H

#include "SFML\Graphics.hpp"
#include "assetManager.h"
class Button : public sf::RectangleShape
{
public:
	Button(AssetManager* assets, std::string pLabel);
	virtual bool processEvent(sf::Event& e, sf::Vector2f mousePos);
	virtual void draw(sf::RenderWindow& window);
	virtual void action() = 0;
	bool mouseOver(sf::Vector2f mousePos);
	void setPos(sf::Vector2f newPos);
	void setVisible(bool visible);
private:
	sf::Text label;
	bool bVisible;
	bool bActivated;
};
#endif