#include "..\include\textMarker.h"
#include "..\include\util.h"

float lerpMul = 0.05f;
TextMarker::TextMarker(AssetManager* assets, bool drawLine)
{
	bDrawLine = drawLine;
	setFont(*assets->getFont());
	bVisible = true;
}

void TextMarker::addConstraint(VisibleObj& pParent, sf::Vector2f pOffset, ELineAnchor pLineAnchor)
{
	
	offset = pOffset;
	parent = &pParent;
	lineAnchor = pLineAnchor;
	
	switch (lineAnchor)
	{
	case LA_CENTER:
		//do nothing, center has 0,0 offset
		break;
	case LA_CENTERLEFT:
		lineOffset.x = -parent->getBoundingRect().width / 2.0f;
		break;
	case LA_CENTERRIGHT:
		lineOffset.x = parent->getBoundingRect().width / 2.0f;
		break;
	case LA_CENTERTOP:
		lineOffset.y = -parent->getBoundingRect().height/ 2.0f;
		break;
	case LA_TOPRIGHT:
		lineOffset.x = parent->getBoundingRect().width / 2.0f;
		lineOffset.y = -parent->getBoundingRect().height / 2.0f;
		break;
	case LA_TOPLEFT:
		lineOffset.x = -parent->getBoundingRect().width / 2.0f;
		lineOffset.y = -parent->getBoundingRect().height / 2.0f;
		break;
	}
}
void TextMarker::removeConstraint()
{
	parent = NULL;
}
void TextMarker::update(sf::Time dt)
{
	if (parent)
	{
		sf::FloatRect parentRect = parent->getBoundingRect();
		sf::Vector2f dest;
		dest.x = Lerp(getPosition().x, parentRect.left + (parentRect.width / 2.0f) + offset.x, 5 * dt.asSeconds());
		dest.y = Lerp(getPosition().y, parentRect.top + (parentRect.height / 2.0f) + offset.y, 5 * dt.asSeconds());
		setPosition(dest);
	
	}
}

void TextMarker::draw(sf::RenderWindow& window)
{
	if (bVisible)
	{
		window.draw(*this);
		if (parent && bDrawLine)
		{
			sf::FloatRect parentRect = parent->getBoundingRect();
			sf::Vertex line[] =
			{
				sf::Vertex(getPosition(), getColor()),
				sf::Vertex(sf::Vector2f(parentRect.left + (parentRect.width / 2.0f) + lineOffset.x, parentRect.top + (parentRect.height / 2.0f) + lineOffset.y), getColor())
			};

			window.draw(line, 2, sf::Lines);
		}
	}
}

sf::FloatRect TextMarker::getBoundingRect()
{
	return getGlobalBounds();
}

void TextMarker::setVisible(bool visible)
{
	bVisible = visible;
}