#include "..\include\buttonAnim.h"

ButtonAnim::ButtonAnim(AssetManager* pAssets, LList* pList, DisplayText* dispay) : Button(pAssets, "NEXT STEP"), list(pList), displayText(dispay)
{
	setVisible(list->isAnimPlaying());
	setFillColor(sf::Color::Green);
	
}
bool ButtonAnim::processEvent(sf::Event& e, sf::Vector2f mousePos)
{
	bool result = false;
	setVisible(list->isAnimPlaying());
	if (list->isAnimPlaying())
	{
		result = Button::processEvent(e, mousePos);
	}
	return result;
}
void ButtonAnim::action()
{
	displayText->setMessage(list->stepAnim());
}