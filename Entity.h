#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
protected:
	Entity* parent;
	Entity(Entity* parent) : parent(parent)
	{
	}

public:
	virtual void update(sf::Time deltaTime) {}
};
