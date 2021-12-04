#pragma once
#include "Tile.h"

class WaterTile : public Tile
{
public:
	WaterTile(Entity* parent);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

