#ifndef BUTTONANIM_H
#define BUTTONANIM_H

#include "button.h"
#include "llist.h"
#include "displayText.h"
class ButtonAnim : public Button
{
public:
	ButtonAnim(AssetManager* pAssets, LList* pList, DisplayText* display);
	virtual bool processEvent(sf::Event& e, sf::Vector2f mousePos);
	void action();
private:
	LList* list;
	DisplayText* displayText;

};

#endif