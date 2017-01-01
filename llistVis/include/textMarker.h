#ifndef TEXTMARKER_H
#define TEXTMARKER_H

#include "SFML/Graphics.hpp"
#include "assetManager.h"
#include "visibleObj.h"

enum ELineAnchor
{
	LA_CENTER,
	LA_TOPLEFT,
	LA_TOPRIGHT,
	LA_CENTERLEFT,
	LA_CENTERRIGHT,
	LA_CENTERTOP
};

class TextMarker : public sf::Text, public VisibleObj
{
public:
	TextMarker(AssetManager* assets, bool drawLine = false);
	void update(sf::Time dt);
	void addConstraint(VisibleObj& pParent, sf::Vector2f pOffset = sf::Vector2f(0.0f,0.0f), ELineAnchor pLineAnchor = LA_CENTER);
	void removeConstraint();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBoundingRect();
	void setVisible(bool visible);
private:
	bool bVisible;
	ELineAnchor lineAnchor;
	sf::Vector2f lineOffset;
	bool bDrawLine;
	VisibleObj* parent;
	sf::Vector2f offset;
};
#endif