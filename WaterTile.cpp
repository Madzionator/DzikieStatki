#include "WaterTile.h"
#include "Textures.h"

WaterTile::WaterTile(Entity* parent) : Tile(parent), tile(this, Textures::get()->WaterTileTexture)
{
	TileType = TileType::Water;
}

void WaterTile::setState(WaterTileState state)
{
	tileState = state;
	if (tileState == WaterTileState::Hit)
		this->tile = Animable(this, Textures::get()->WaterHitTileTexture);
	else
		this->tile = Animable(this, Textures::get()->WaterTileTexture);
}

void WaterTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	Tile::draw(target, states);
	target.draw(tile, states);
	drawOverlay(target, states);
}

void WaterTile::update(sf::Time deltaTime)
{
	Tile::update(deltaTime);
	tile.update(deltaTime);
	updateOverlay(deltaTime);
}