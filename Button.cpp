#include "Button.h"
#include "System.h"

Button::Button(Entity* parent) : Entity(parent)
{
	shape = sf::RectangleShape(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Green);

	text.setFont(*System::Font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape, states);
	target.draw(text, states);
}

void Button::update(sf::Time delta_time)
{
	auto mouse = sf::Mouse::getPosition(*System::Window);
	auto mouseVec = (parent->getTransform() * getTransform()).getInverse() * (System::Window->mapPixelToCoords(mouse));
	if (shape.getLocalBounds().contains(mouseVec.x, mouseVec.y))
	{

		if (!isEnabled)
			shape.setFillColor(sf::Color::Color(60, 60, 60));
		else
			shape.setFillColor(sf::Color::Color(199, 58, 58));
		if (isEnabled && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			shape.setFillColor(sf::Color::Blue);
			if(onClick)
				onClick();
		}
	}
	else
	{
		if (!isEnabled)
			shape.setFillColor(sf::Color::Color(100, 100, 100));
		else
			shape.setFillColor(sf::Color::Color(60, 200, 80));
	}
}
