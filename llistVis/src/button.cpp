#include "button.h"
Button::Button(AssetManager* assets, std::string pLabel)
{
	label.setFont(*assets->getFont());
	label.setString(pLabel);
	label.setCharacterSize(12);
	label.setOrigin(label.getGlobalBounds().width / 2.0f, label.getGlobalBounds().height / 2.0f);
	setSize(sf::Vector2f(128, 32));
	setOutlineThickness(-1.0f);
	setOutlineColor(sf::Color(64, 64, 64, 255));
	setFillColor(sf::Color(96, 96, 96, 255));
	setPos(sf::Vector2f(0.0f, 0.0f));
	bVisible = true;
	bActivated = false;
}
bool Button::processEvent(sf::Event& e, sf::Vector2f mousePos)
{
	if (mouseOver(mousePos))
	{
		if (e.type == sf::Event::MouseButtonPressed)
		{
			bActivated = true;
			setOutlineColor(sf::Color::Blue);
		}
		if (bActivated && e.type == sf::Event::MouseButtonReleased)
		{
			action();
			return true;
		}

	}
	return false;
}
void Button::draw(sf::RenderWindow& window)
{
	if (bVisible)
	{
		window.draw(*this);
		window.draw(label);
	}
}

bool Button::mouseOver(sf::Vector2f mousePos)
{
	if (bVisible)
	{
		if (getGlobalBounds().contains(mousePos))
		{
			return true;
		}
		else
		{
			setOutlineColor(sf::Color(64, 64, 64, 255));
			bActivated = false;
		}
	}

	return false;
}

void Button::setPos(sf::Vector2f newPos)
{
	setPosition(newPos);
	label.setPosition(getGlobalBounds().left + (getGlobalBounds().width / 2.0f), getGlobalBounds().top + (getGlobalBounds().height / 2.0f));
}

void Button::setVisible(bool visible)
{
	bVisible = visible;
}