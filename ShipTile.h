#pragma once
#include "Ship.h"
#include "Textures.h"
#include "Tile.h"

class ShipTile : public Tile
{
	ShipTileState state = ShipTileState::Visible;
public:
	Ship* ship;
	ShipTile(Entity* parent);
	void setState(ShipTileState state)
	{
		this->state = state;
		if (state == ShipTileState::Undiscovered)
			this->animable = new Animable(this, Textures::WaterTileSprite);
		else if (state == ShipTileState::Visible)
			this->animable = new Animable(this, Textures::VisibleShipTileSprite);
		else if (state == ShipTileState::Damaged)
			this->animable = new Animable(this, Textures::DamagedShipTileSprite);
		else if (state == ShipTileState::Destroyed)
			this->animable = new Animable(this, Textures::DestroyedShipTileSprite);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

