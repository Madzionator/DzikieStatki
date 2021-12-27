#pragma once
#include "Tile.h"

enum class WaterTileState { Default, Hit };

class WaterTile : public Tile
{
	WaterTileState tileState = WaterTileState::Default;
public:
	WaterTile(Entity* parent);
	void setState(WaterTileState state);
	WaterTileState getState() { return tileState; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

