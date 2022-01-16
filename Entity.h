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
	Entity* getParent() const { return parent; }
	void setParent(Entity* p) { parent = p; }
	sf::Transform getTotalTransform()
	{
		auto trans = getTransform();
		if (parent != nullptr)
			trans = parent->getTotalTransform() * trans;
		return trans;
	}
};
