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
	auto mouseVec = (parent->getTransform() * getTransform()).getInverse() * sf::Vector2f(mouse.x, mouse.y);
	if (shape.getLocalBounds().contains(mouseVec.x, mouseVec.y))
	{
		shape.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			shape.setFillColor(sf::Color::Blue);
			if(onClick)
				onClick();
		}
	}
	else
		shape.setFillColor(sf::Color::Green);
}
