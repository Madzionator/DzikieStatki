#include "Button.h"
#include "System.h"

Button::Button()
{
	shape = sf::RectangleShape(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);

	text.setFont(*System::Font);
	text.setString(":3");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(100, 100);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
	target.draw(text);
}

void Button::update(sf::Time delta_time)
{
	auto mouseVec = sf::Mouse::getPosition(*System::Window);
	if (shape.getGlobalBounds().contains(mouseVec.x, mouseVec.y))
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
