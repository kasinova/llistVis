#include "..\include\GUI.h"
#include "..\include\util.h"

GUI::GUI(AssetManager* assets, LList* pList) : displayText(assets, sf::Vector2f(0.0f, -150.0f))
{
	list = pList;
	sf::Vector2f bPos = sf::Vector2f(-(SCREEN_WIDTH / 2) + 10, (SCREEN_HEIGHT / 2) - 10 - 32);
	ButtonNode* bAddFront = new ButtonNode(assets, "ADD FRONT", list, InsertInfo::insertType::ADD_FRONT);
	bAddFront->setPos(bPos);
	buttons.push_back(bAddFront);

	bPos.x += 138;
	ButtonNode* bAddRear = new ButtonNode(assets, "ADD REAR", list, InsertInfo::insertType::ADD_REAR);
	bAddRear->setPos(bPos);
	buttons.push_back(bAddRear);
	bPos.x += 138;
	ButtonNode* bAddIth = new ButtonNode(assets, "ADD BEFORE ITH", list, InsertInfo::insertType::ADD_ITH);
	bAddIth->setPos(bPos);
	buttons.push_back(bAddIth);
	bPos.x += 138;
	ButtonNode* bRemFront = new ButtonNode(assets, "REMOVE FRONT", list, InsertInfo::insertType::REM_FRONT);
	bRemFront->setPos(bPos);
	buttons.push_back(bRemFront);
	bPos.x += 138;
	ButtonNode* bRemRear = new ButtonNode(assets, "REMOVE REAR", list, InsertInfo::insertType::REM_REAR);
	bRemRear->setPos(bPos);
	buttons.push_back(bRemRear);
	bPos.x += 138;
	ButtonNode* bRemIth = new ButtonNode(assets, "REMOVE ITH", list, InsertInfo::insertType::REM_ITH);
	bRemIth->setPos(bPos);
	buttons.push_back(bRemIth);
	bPos.x += 138;
	ButtonAnim* bAnim = new ButtonAnim(assets, list, &displayText);
	bAnim->setPos(bPos);
	buttons.push_back(bAnim);
}

void GUI::update(sf::Time dt)
{
	displayText.update(dt);
}

bool GUI::processEvent(sf::Event& e, sf::Vector2f mousePos)
{
	bool result = false;
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->processEvent(e, mousePos))
		{
			result = true;
		}
	}
	return result;
}

void GUI::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw(window);
	}
	
	displayText.draw(window);
}

void GUI::updateButtonPositions(sf::Vector2f newPos)
{
	SCREEN_WIDTH = newPos.x;
	SCREEN_HEIGHT = newPos.y;
	sf::Vector2f bPos = sf::Vector2f(-(SCREEN_WIDTH / 2) + 10, (SCREEN_HEIGHT / 2) - 10 - 32);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->setPos(bPos);
		bPos.x += 138;
	}
}