#include "WaterTile.h"
#include "Textures.h"

WaterTile::WaterTile(Entity* parent) : Tile(parent)
{
	TileType = TileType::Water;
	setState(WaterTileState::Default);
}

void WaterTile::setState(WaterTileState state)
{
	tileState = state;
	if (tileState == WaterTileState::Hit)
		this->tile = sf::Sprite(*Textures::get()->WaterHitTileTexture);
	else if (tileState == WaterTileState::Default)
		this->tile = sf::Sprite(*Textures::get()->Empty);
	else if (tileState == WaterTileState::Blocked)
		this->tile = sf::Sprite(*Textures::get()->WaterBlockedTileTexture);
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
	updateOverlay(deltaTime);
}