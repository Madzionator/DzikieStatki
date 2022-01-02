#include "ShipTile.h"
#include "Textures.h"

ShipTile::ShipTile(Entity* parent) : Tile(parent)
{
	TileType = TileType::Ship;
	setState(ShipTileState::Visible);
}

void ShipTile::setState(ShipTileState state)
{
	this->state = state;
	if (state == ShipTileState::Undiscovered)
		this->tile = sf::Sprite(*Textures::get()->Empty);
	else if (state == ShipTileState::Visible)
		this->tile = sf::Sprite(*Textures::get()->VisibleShipTileTexture);
	else if (state == ShipTileState::Damaged)
		this->tile = sf::Sprite(*Textures::get()->DamagedShipTileTexture);
	else if (state == ShipTileState::Destroyed)
		this->tile = sf::Sprite(*Textures::get()->DestroyedShipTileTexture);
	else if (state == ShipTileState::Blocked)
		this->tile = sf::Sprite(*Textures::get()->WaterBlockedTileTexture);
	else if (state == ShipTileState::BlockedVisible)
		this->tile = sf::Sprite(*Textures::get()->BlockedVisibleShipTileTexture);
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
	updateOverlay(deltaTime);
}