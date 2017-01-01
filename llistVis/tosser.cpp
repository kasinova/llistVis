#include "tosser.h"

float getLength(sf::Vector2f botPos, sf::Vector2f lampPos)
{
	sf::Vector2f length;
	length.x = (botPos.x - lampPos.x) * (botPos.x - lampPos.x);
	length.y = (botPos.y - lampPos.y) * (botPos.y - lampPos.y);
	return sqrt(length.x + length.y);
}



Entity::Entity()
{
	setColor(sf::Color(255, 0, 0));
}