#pragma once
#include <vector>

class ShipTile;

class Ship
{
	std::vector<ShipTile*> tiles;
public:
	bool checkDestroyed();
	Ship(std::vector<ShipTile*> shiptiles);
	~Ship() { tiles.clear(); std::vector<ShipTile*>().swap(tiles); }
	auto getTiles() const { return &tiles; }
};