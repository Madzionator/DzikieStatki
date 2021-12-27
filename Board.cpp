#include "Board.h"

#include "ShipTile.h"
#include "WaterTile.h"

Board::Board(Entity* parent) : Entity(parent)
{
	boardBackground = sf::RectangleShape(sf::Vector2f(tileSize * tileCount, tileSize * tileCount));
	boardBackground.setFillColor(sf::Color(100, 100, 100));

	tiles = new Tile* [tileCount * tileCount];
	for (int y = 0; y < tileCount; y++)
		for (int x = 0; x < tileCount; x++) 
		{
			auto tile = new WaterTile(this);
			tiles[y * tileCount + x] = tile;
			tile->setPosition(x * tileSize, y * tileSize);
		}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(boardBackground, states);
	for (int i = 0; i < tileCount*tileCount; i++)
		target.draw(*tiles[i], states);
}

void Board::update(sf::Time delta_time)
{
	for (int i = 0; i < tileCount * tileCount; i++)
		tiles[i]->update(delta_time);

	if(isEditMode)
	for (int x = 0; x < tileCount*tileCount; x++)
		if (tiles[x]->IsMouseDown)
		{
			auto tile = tiles[x];
			if(tile->TileType == TileType::Water)
			{
				tiles[x] = new ShipTile(this);
				tiles[x]->setPosition(tile->getPosition());
			}
			else
			{
				tiles[x] = new WaterTile(this);
				tiles[x]->setPosition(tile->getPosition());
			}
		}
}
