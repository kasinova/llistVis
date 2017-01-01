#include "..\include\buttonNode.h"
#include <iostream>
ButtonNode::ButtonNode(AssetManager* pAssets, std::string name, LList* pList, InsertInfo::insertType pType) : Button(pAssets, name), list(pList), type(pType)
{
	assets = pAssets;
}

bool ButtonNode::processEvent(sf::Event& e, sf::Vector2f mousePos)
{
	bool result = false;
	if (!list->isAnimPlaying())
	{
		result = Button::processEvent(e, mousePos);
	}
	else
	{
	}
	return result;
}

void ButtonNode::action()
{
	Node* newNode;
	InsertInfo info;
	info.type = type;
	switch (type)
	{
	case InsertInfo::insertType::ADD_REAR:
		newNode = new Node(assets);
		list->addNode(newNode, info);
		break;
	case InsertInfo::insertType::ADD_FRONT:
		newNode = new Node(assets);
		list->addNode(newNode, info);
		break;
	case InsertInfo::insertType::REM_REAR:
		list->addNode(NULL, info);
		break;
	case InsertInfo::insertType::REM_FRONT:
		list->addNode(NULL, info);
		break;
	case InsertInfo::insertType::REM_ITH:
		std::cout << "Index of node to delete: ";
		std::cin >> info.ith;
		list->addNode(NULL, info);
		break;
	case InsertInfo::insertType::ADD_ITH:
		std::cout << "Index of node to add before: ";
		std::cin >> info.ith;
		newNode = new Node(assets);
		list->addNode(newNode, info);
	}
}