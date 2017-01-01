#ifndef NODE_H
#define NODE_H

#include "SFML\Graphics.hpp"
#include "visibleObj.h"
#include "assetManager.h"
enum EState
{
	ES_NEW,
	ES_ADDED,
	ES_INLIST,
	ES_REMOVED

};

class Node : public sf::Sprite, public VisibleObj
{
public:
	Node(AssetManager* assets);
	void update(sf::Time dt);
	void updateDest(sf::Vector2f newPos);
	void draw(sf::RenderWindow& window);
	void setNext(Node* nextNode);
	Node* getNext();

	sf::Vector2f frontAnchor();
	sf::Vector2f rearAnchor();
	void createLine(VisibleObj& nodeAnchor, sf::Color color);
	void setLineColor(sf::Color newColor);
	void setLineVisibility(bool visible);
	void setState(EState newState);

	sf::FloatRect getBoundingRect();
	void markDeleted();
	int placement;
private:
	sf::Texture* tex;
	EState state;
	Node* next;
	sf::Vector2f curPos;
	sf::Vector2f destPos;
	std::string elem;
	sf::Text textElem;
	bool bDrawLine;
	sf::Color lineColor;
	VisibleObj* foreignAnchor;
};

#endif