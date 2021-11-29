#pragma once
#include "Tile.h"

class WaterTile : public Tile
{
	sf::RectangleShape shape;
public:
	WaterTile(int x, int y, int tile_size);
	void drawTile(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateTile(sf::Time deltaTime) override;
};

