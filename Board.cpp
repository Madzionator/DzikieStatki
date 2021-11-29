#include "Board.h"

#include "ShipTile.h"
#include "WaterTile.h"

Board::Board()
{
	boardBackground = sf::RectangleShape(sf::Vector2f(tileSize * tileCount, tileSize * tileCount));
	boardBackground.setFillColor(sf::Color(100, 100, 100));

	tiles = new Tile * [tileCount * tileCount];
	for (int x = 0; x < tileCount; x++)
		for(int y = 0; y < tileCount; y++)
			tiles[x*tileCount + y] = new WaterTile(x, y, tileSize);

	tiles[69] = new ShipTile(6, 9, tileSize);
	tiles[21] = new ShipTile(2, 1, tileSize);
	tiles[37] = new ShipTile(3, 7, tileSize);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(boardBackground, states);
	for (int i = 0; i < tileCount*tileCount; i++)
		target.draw(*tiles[i], states);
}

void Board::update(sf::Time delta_time)
{
	for (int i = 0; i < tileCount * tileCount; i++)
		tiles[i]->update(delta_time);
}
