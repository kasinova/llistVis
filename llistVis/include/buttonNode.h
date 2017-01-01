#ifndef BUTTONNODE_H
#define BUTTONNODE_H
#include "button.h"
#include "llist.h"
class ButtonNode : public Button
{
public:
	ButtonNode(AssetManager* pAssets, std::string name, LList* pList, InsertInfo::insertType pType);
	virtual bool processEvent(sf::Event& e, sf::Vector2f mousePos);
	void action();
private:
	LList* list;
	InsertInfo::insertType type;
	AssetManager* assets;
};
#endif