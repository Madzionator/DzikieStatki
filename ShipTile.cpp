#include "ShipTile.h"
#include "Textures.h"

ShipTile::ShipTile(Entity* parent) : Tile(parent), tile(this, Textures::get()->Empty)
{
	TileType = TileType::Ship;
	setState(ShipTileState::Visible);
}

void ShipTile::setState(ShipTileState state)
{
	this->state = state;
	switch(state)
	{
	case ShipTileState::Undiscovered:
		this->tile = Animable(this, Textures::get()->Empty);
		break;
	case ShipTileState::Visible:
		this->tile = Animable(this, Textures::get()->VisibleShipTileTexture);
		break;
	case ShipTileState::Damaged:
		this->tile = Animable(this, Textures::get()->DamagedShipTileTexture);
		break;
	case ShipTileState::Destroyed:
		this->tile = Animable(this, Textures::get()->DestroyedShipTileTexture);
		break;
	case ShipTileState::Blocked:
		this->tile = Animable(this, Textures::get()->WaterBlockedTileTexture);
		break;
	case ShipTileState::BlockedVisible:
		this->tile = Animable(this, Textures::get()->BlockedVisibleShipTileTexture);
	}
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
