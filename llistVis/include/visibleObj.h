#ifndef VISIBLEOBJ_H
#define VISIBLEOBJ_H
#include "SFML\Graphics.hpp"
class VisibleObj
{
public:
	virtual sf::FloatRect getBoundingRect() = 0;
private:
	
};

#endif