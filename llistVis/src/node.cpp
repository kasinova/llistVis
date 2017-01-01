#include "..\include\node.h"
#include "..\include\util.h"
#include <iostream>

Node::Node(AssetManager* assets)
{
	tex = assets->getTexture("node");
	setTexture(*tex);
	setOrigin(sf::Vector2f(getLocalBounds().width / 2, getLocalBounds().height / 2));

	std::cout << "Type a word for element of new Node: ";
	std::cin >> elem;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	

	textElem.setFont(*assets->getFont());
	textElem.setCharacterSize(16);
	textElem.setString(elem);
	textElem.setColor(sf::Color::Black);

	curPos = sf::Vector2f(0.0f, 100.0f);
	setPosition(curPos);
	destPos = sf::Vector2f(0.0f, -128.0f);
	state = ES_NEW;
	next = NULL;
	placement = 0;
}
void Node::setState(EState newState)
{
	state = newState;
	
	switch (state)
	{
	case EState::ES_NEW:
		destPos.y = 100.0f;
		break;
	case EState::ES_ADDED: case EState::ES_REMOVED:
		destPos.y = 100.0f;
		break;
	case EState::ES_INLIST:
		destPos.y = 0.0f;
		break;
	}
	
}
void Node::update(sf::Time dt)
{
	setPosition(Lerp(curPos.x, destPos.x,5 * dt.asSeconds()), Lerp(curPos.y, destPos.y, 5 * dt.asSeconds()));
	curPos = getPosition();

	//update the text
	sf::Vector2f texPos;
	texPos.x = getPosition().x - (0.25f * getGlobalBounds().width);
	texPos.y = getPosition().y - (0.25f * getGlobalBounds().height);
	textElem.setPosition(texPos);

}

void Node::updateDest(sf::Vector2f newPos)
{
	destPos.x = newPos.x;
}
void Node::draw(sf::RenderWindow& window)
{
	window.draw(*this);
	window.draw(textElem);
	if (bDrawLine)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(rearAnchor(), lineColor),
			sf::Vertex(sf::Vector2f(foreignAnchor->getBoundingRect().left, foreignAnchor->getBoundingRect().top + (foreignAnchor->getBoundingRect().height/2.0f)), lineColor)
		};

		window.draw(line, 2, sf::Lines);
	}
}
void Node::setNext(Node* nextNode)
{
	next = nextNode;
}
Node* Node::getNext()
{
	return next;
}

sf::Vector2f Node::frontAnchor()
{
	sf::Vector2f anchor;
	anchor.x = curPos.x - (getGlobalBounds().width / 2.0f);
	anchor.y = curPos.y;
	return anchor;
}
sf::Vector2f Node::rearAnchor()
{
	sf::Vector2f anchor;
	anchor.x = curPos.x + (getGlobalBounds().width / 2.0f) - (getGlobalBounds().width / 8.0f);
	anchor.y = curPos.y;
	return anchor;
}
void Node::createLine(VisibleObj& nodeAnchor, sf::Color color)
{
	foreignAnchor = &nodeAnchor;
	lineColor = color;
}
void Node::setLineColor(sf::Color newColor)
{
	lineColor = newColor;
}
void Node::setLineVisibility(bool visible)
{
	bDrawLine = visible;
}

sf::FloatRect Node::getBoundingRect()
{
	return getGlobalBounds();
}

void Node::markDeleted()
{
	setColor(sf::Color::Red);
}