#include "Button.h"
#include "System.h"

Button::Button(Entity* parent, std::wstring txt, sf::Vector2f size, bool centered) : Entity(parent),
IsCentered(centered)
{
	shape = sf::RectangleShape(sf::Vector2f(50, 50));
	shape.setOutlineColor(sf::Color::Magenta);
	shape.setFillColor(sf::Color::Green);
	shape.setSize(size);

	text.setFont(*System::Font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setString(txt);

	updateSize();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape, states);
	target.draw(text, states);
}

void Button::updateSize()
{
	auto textSize = text.getLocalBounds();
	auto shapeSize = shape.getLocalBounds();
	if (IsCentered) // (0,0) is center of button and text
	{
		shape.setPosition(-shapeSize.width / 2, -shapeSize.height / 2);
		text.setPosition((int)(-textSize.width / 2 - textSize.left), (int)(-textSize.height / 2 - textSize.top * 0.9f));
	}
	else // (0,0) is left corner of button, text is centered
	{
		shape.setPosition(0, 0);
		text.setPosition((int)(textSize.left + shapeSize.width / 2 - textSize.width / 2), (int)(textSize.top * 0.8f));
	}
}

void Button::update(sf::Time delta_time)
{
	auto mouse = sf::Mouse::getPosition(*System::Window);
	auto mouseVec = (parent->getTransform() * getTransform()).getInverse() * (System::Window->mapPixelToCoords(mouse));

	IsMouseOver = shape.getGlobalBounds().contains(mouseVec.x, mouseVec.y);
	IsMouseClicked = IsMouseDown && IsMouseOver && !sf::Mouse::isButtonPressed(sf::Mouse::Left);
	IsMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if (IsMouseOver)
	{
		if (!IsEnabled) {
			shape.setFillColor(sf::Color(60, 60, 60));
		}
		else
			shape.setFillColor(sf::Color(199, 58, 58));
		if (IsEnabled && IsMouseClicked) {
			shape.setFillColor(sf::Color::Blue);
			if (onClick)
				onClick();
		}
	}
	else
	{
		if (!IsEnabled)
			shape.setFillColor(sf::Color(100, 100, 100));
		else
			shape.setFillColor(sf::Color(60, 200, 80));
	}
}