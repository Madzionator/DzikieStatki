#include "Ship.h"

#include "ShipTile.h"

Ship::Ship(std::vector<ShipTile*> shiptiles)
{
	tiles = shiptiles;
	for (auto tile : shiptiles)
		tile->ship = this;
}
