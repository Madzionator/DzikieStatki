#pragma once
#include "Tile.h"

class ShipTile : public Tile
{
public:
	ShipTile(Entity* parent);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

