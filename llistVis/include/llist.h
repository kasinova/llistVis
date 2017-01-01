#ifndef LLIST_H
#define LLIST_H

#include "SFML\Graphics.hpp"
#include "assetManager.h"
#include "node.h"
#include "textMarker.h"
#include "visibleObj.h"
#include "animation.h"
#include "displayText.h"
struct InsertInfo
{
	enum insertType
	{
		ADD_FRONT,
		ADD_REAR,
		ADD_ITH,
		REM_FRONT,
		REM_REAR,
		REM_ITH
	};
	insertType type;
	int ith;
};

class LList : public VisibleObj
{
public:
	LList(AssetManager& pAssets);
	void update(sf::Time dt);
	void draw(sf::RenderWindow& window);
	void addNode(Node* newNode, InsertInfo info);
	sf::FloatRect getBoundingRect();
	bool isAnimPlaying();
	std::string stepAnim();
private:
	bool isEmpty();
	void updatePlacement(int amount);
	void updateNodeDest(int projectedCount);
	void addBeforeIth();
	void addFront();
	void addRear();
	void deleteFront();
	void deleteRear();
	void deleteIth();

	sf::Vector2f pos;
	//use for the width of the list
	sf::Vector2f dimensions;


	AssetManager* assets;
	TextMarker textLabel;
	TextMarker textFront;
	TextMarker textRear;
	TextMarker textNull;
	TextMarker textIter;

	Node* front;
	Node* rear;
	Node* limbo;

	InsertInfo info;

	//for ith insertion 
	Node* nodeBefore;
	Node* nodeAfter;

	int count;

	Animation anim;
};

#endif