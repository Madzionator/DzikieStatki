#include "ShipTile.h"

#include "Textures.h"

ShipTile::ShipTile(Entity* parent)
	: Tile(parent, Textures::VisibleShipTileSprite)
{
	TileType = TileType::Ship;
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
