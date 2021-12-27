#include "ShipTile.h"

#include "Textures.h"

ShipTile::ShipTile(Entity* parent)
	: Tile(parent, Textures::VisibleShipTileSprite)
{
	TileType = TileType::Ship;
}

void ShipTile::setState(ShipTileState state)
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

void ShipTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	Tile::draw(target, states);
}

void ShipTile::update(sf::Time delta_time)
{
	Tile::update(delta_time);
}
