#pragma once
#include "Tile.h"

class ShipTile : public Tile
{
	sf::RectangleShape shape;
public:
	ShipTile(int x, int y, int tileSize);
	void drawTile(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateTile(sf::Time deltaTime) override;
};

