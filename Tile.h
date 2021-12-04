#pragma once
#include "Animable.h"
#include "Entity.h"

class Tile : public Entity
{
	sf::RectangleShape* overlay;
protected:
	Tile(Entity* parent, sf::Sprite* sprite);
	Animable* animable;

public:
	int TileSize;

	bool IsMouseOver;
	bool IsMouseDown;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::Time deltaTime) override;
};


