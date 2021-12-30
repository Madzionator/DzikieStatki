#pragma once
#include <functional>

#include "Entity.h"

class Button : public Entity
{
	sf::RectangleShape shape;
	sf::Text text;
 
public:
	std::function<void()> onClick;
	Button(Entity* parent);
	bool isEnabled = true;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	void setText(std::string txt) { text.setString(txt); }
};


