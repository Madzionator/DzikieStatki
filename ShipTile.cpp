#include "ShipTile.h"
#include "Textures.h"

ShipTile::ShipTile(Entity* parent) : Tile(parent), tile(this, Textures::get()->VisibleShipTileTexture)
{
	TileType = TileType::Ship;
}

void ShipTile::setState(ShipTileState state)
{
	this->state = state;
	if (state == ShipTileState::Undiscovered)
		this->tile = Animable(this, Textures::get()->WaterTileTexture);
	else if (state == ShipTileState::Visible)
		this->tile = Animable(this, Textures::get()->VisibleShipTileTexture);
	else if (state == ShipTileState::Damaged)
		this->tile = Animable(this, Textures::get()->DamagedShipTileTexture);
	else if (state == ShipTileState::Destroyed)
		this->tile = Animable(this, Textures::get()->DestroyedShipTileTexture);
	else if (state == ShipTileState::Blocked)
		this->tile = Animable(this, Textures::get()->WaterBlockedTileTexture);
	else if (state == ShipTileState::BlockedVisible)
		this->tile = Animable(this, Textures::get()->BlockedVisibleShipTileTexture);
}

void ShipTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	Tile::draw(target, states);
	target.draw(tile, states);
	drawOverlay(target, states);
}

void ShipTile::update(sf::Time deltaTime)
{
	Tile::update(deltaTime);
	tile.update(deltaTime);
	updateOverlay(deltaTime);
}
