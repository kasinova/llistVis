#ifndef GUI_H
#define GUI_H
#include "displayText.h"
#include "buttonNode.h"
#include "buttonAnim.h"
#include "llist.h"
#include "assetManager.h"
#include <vector>
class GUI
{
public:
	GUI(AssetManager* assets, LList* pList);
	void update(sf::Time dt);
	bool processEvent(sf::Event& e, sf::Vector2f mousePos);
	void draw(sf::RenderWindow& window);
	void updateButtonPositions(sf::Vector2f newPos);
private:
	LList* list;
	DisplayText displayText;
	std::vector<Button*>buttons;
};

#endif