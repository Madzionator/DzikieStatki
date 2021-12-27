#include "WaterTile.h"

#include "Textures.h"

WaterTile::WaterTile(Entity* parent)
	: Tile(parent, Textures::WaterTileSprite)
{
	TileType = TileType::Water;
}

void WaterTile::setState(WaterTileState state)
{
	tileState = state;
	if (tileState == WaterTileState::Hit)
		this->animable = new Animable(this, Textures::WaterHitTileSprite);
	else
		this->animable = new Animable(this, Textures::WaterTileSprite);
}

void WaterTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	Tile::draw(target, states);
}

void WaterTile::update(sf::Time delta_time)
{
	Tile::update(delta_time);
}

