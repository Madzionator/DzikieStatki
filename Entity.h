#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	virtual void update(sf::Time deltaTime) {}
};
