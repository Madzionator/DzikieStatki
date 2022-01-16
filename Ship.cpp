#include "Ship.h"
#include "ShipTile.h"

bool Ship::checkDestroyed()
{
	for (int i = 0; i < tiles.size(); i++)
		if (tiles[i]->getState() != ShipTileState::Damaged)
			return false;
	for (int i = 0; i < tiles.size(); i++)
		tiles[i]->setState(ShipTileState::Destroyed);
	return true;
}

Ship::Ship(std::vector<ShipTile*> shiptiles)
{
	tiles = shiptiles;
	for (auto tile : shiptiles)
		tile->ship = this;
}

Ship::~Ship()
{
	int i = tiles.size() - 1;
	/*for (i; i >= 0; i--)
		delete tiles[i];*/
	tiles.clear();
	std::vector<ShipTile*>().swap(tiles);
}
