#pragma once
#include "Entity.h"

class Tile;

class Board : public Entity
{
	sf::RectangleShape boardBackground;
	int tileSize = 32;
	int tileCount = 10;

	Tile** tiles;

public:
	Board(Entity* parent);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

