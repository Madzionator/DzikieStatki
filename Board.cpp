#include "Board.h"

#include "ShipTile.h"
#include "WaterTile.h"

Board::Board(Entity* parent) : Entity(parent)
{
	boardBackground = sf::RectangleShape(sf::Vector2f(tileSize * tileCount, tileSize * tileCount));
	boardBackground.setFillColor(sf::Color(100, 100, 100));

	tiles = new Tile* [tileCount * tileCount];
	for (int x = 0; x < tileCount; x++)
		for (int y = 0; y < tileCount; y++) {
			auto tile = new WaterTile(this);
			tiles[x * tileCount + y] = tile;
			tile->setPosition(x * tileSize, y * tileSize);
		}

	tiles[11] = new ShipTile(this);
	tiles[21] = new ShipTile(this);
	tiles[31] = new ShipTile(this);
	tiles[12] = new ShipTile(this);
	tiles[13] = new ShipTile(this);

	tiles[33] = new ShipTile(this);
	tiles[43] = new ShipTile(this);
	tiles[53] = new ShipTile(this);

	tiles[27] = new ShipTile(this);

	tiles[11]->setPosition(1 * tileSize, 1 * tileSize);
	tiles[21]->setPosition(2 * tileSize, 1 * tileSize);
	tiles[31]->setPosition(3 * tileSize, 1 * tileSize);
	tiles[12]->setPosition(1 * tileSize, 2 * tileSize);
	tiles[13]->setPosition(1 * tileSize, 3 * tileSize);
	tiles[33]->setPosition(3 * tileSize, 3 * tileSize);
	tiles[43]->setPosition(4 * tileSize, 3 * tileSize);
	tiles[53]->setPosition(5 * tileSize, 3 * tileSize);
	tiles[27]->setPosition(2 * tileSize, 7 * tileSize);

	std::vector<ShipTile*> shiptiles1;
	shiptiles1.push_back(dynamic_cast<ShipTile* const>(tiles[11]));
	shiptiles1.push_back(dynamic_cast<ShipTile* const>(tiles[21]));
	shiptiles1.push_back(dynamic_cast<ShipTile* const>(tiles[31]));
	shiptiles1.push_back(dynamic_cast<ShipTile* const>(tiles[12]));
	shiptiles1.push_back(dynamic_cast<ShipTile* const>(tiles[13]));

	std::vector<ShipTile*> shiptiles2;
	shiptiles2.push_back(dynamic_cast<ShipTile* const>(tiles[33]));
	shiptiles2.push_back(dynamic_cast<ShipTile* const>(tiles[43]));
	shiptiles2.push_back(dynamic_cast<ShipTile* const>(tiles[53]));

	std::vector<ShipTile*> shiptiles3;
	shiptiles3.push_back(dynamic_cast<ShipTile* const>(tiles[27]));

	auto ship1 = new Ship(shiptiles1);
	auto ship2 = new Ship(shiptiles2);
	auto ship3 = new Ship(shiptiles3);

	shiptiles1[1]->setState(ShipTileState::Discovered);
	shiptiles1[3]->setState(ShipTileState::Discovered);
	shiptiles2[1]->setState(ShipTileState::Discovered);
	shiptiles3[0]->setState(ShipTileState::Destroyed);

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
