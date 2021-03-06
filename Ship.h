#pragma once
#include <vector>

class ShipTile;

class Ship
{
	std::vector<ShipTile*> tiles;
public:
	bool checkDestroyed();
	Ship(std::vector<ShipTile*> shiptiles);
	~Ship();
	auto getTiles() const { return &tiles; }
};