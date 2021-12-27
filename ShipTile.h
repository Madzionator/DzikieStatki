#pragma once
#include "Ship.h"
#include "Textures.h"
#include "Tile.h"

enum class ShipTileState { Undiscovered, Visible, Damaged, Destroyed };

class ShipTile : public Tile
{
	ShipTileState state = ShipTileState::Visible;
public:
	Ship* ship;
	ShipTile(Entity* parent);
	void setState(ShipTileState state);
	ShipTileState getState() { return state; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

