#pragma once
#include "Ship.h"
#include "Textures.h"
#include "Tile.h"

class ShipTile : public Tile
{
	ShipTileState state = ShipTileState::Undiscovered;
public:
	Ship* ship;
	ShipTile(Entity* parent);
	void setState(ShipTileState state)
	{
		this->state = state;
		if (state == ShipTileState::Discovered)
			this->animable = new Animable(this, Textures::DiscoveredShipTileSprite);
		else if (state == ShipTileState::Destroyed)
			this->animable = new Animable(this, Textures::DestroyedShipTileSprite);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

