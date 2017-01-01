#include "..\include\displayText.h"
#include "..\include\util.h"

DisplayText::DisplayText(AssetManager* assets, sf::Vector2f position)
{
	pos = position;
	setFont(*assets->getFont());
	elapsedTime = 0.0f;
	fadeTime = 5.0f;
	color = sf::Color::Black;
	setMessage("");
}
void DisplayText::update(sf::Time dt)
{
	elapsedTime += dt.asSeconds();
	if (elapsedTime < fadeTime)
	{
		setColor(sf::Color(color.r, color.g, color.b, Lerp(255.0f, 0.0f, elapsedTime / fadeTime)));
	}
	else
	{
		visible = false;
	}
}
void DisplayText::draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*this);
	}
}
void DisplayText::setMessage(std::string newString)
{
	visible = true;
	elapsedTime = 0.0f;
	setString(newString);
	setColor(color);

	setOrigin(sf::Vector2f((getGlobalBounds().width / 2.0f),(getGlobalBounds().height / 2.0f)));
	setPosition(pos);
}