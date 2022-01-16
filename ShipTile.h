#pragma once
#include "Ship.h"
#include "Tile.h"

enum class ShipTileState { Undiscovered, Visible, Damaged, Destroyed, Blocked, BlockedVisible };

class ShipTile : public Tile
{
	ShipTileState state = ShipTileState::Undiscovered;
	sf::Sprite tile;
public:
	Ship* ship;
	ShipTile(Entity* parent);
	~ShipTile() { delete ship; }
	void setState(ShipTileState state);
	ShipTileState getState() { return state; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};