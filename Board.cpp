#include "Board.h"

#include "ShipTile.h"
#include "WaterTile.h"

Board::Board(Entity* parent) : Entity(parent)
{
	boardBackground = sf::RectangleShape(sf::Vector2f(tileSize * tileCount, tileSize * tileCount));
	boardBackground.setFillColor(sf::Color(100, 100, 100));

	tiles = new Tile * [tileCount * tileCount];
	for (int x = 0; x < tileCount; x++)
		for (int y = 0; y < tileCount; y++) {
			auto tile = new WaterTile(this);
			tiles[x * tileCount + y] = tile;
			tile->setPosition(x * tileSize, y * tileSize);
		}

	tiles[69] = new ShipTile(this);
	tiles[69]->setPosition(6 * tileSize, 9 * tileSize);
	tiles[21] = new ShipTile(this);
	tiles[37] = new ShipTile(this);
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
}
