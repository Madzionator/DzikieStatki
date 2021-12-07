#pragma once
#include <vector>

class ShipTile;

enum class ShipTileState { Undiscovered, Discovered, Destroyed };

class Ship
{
	std::vector<ShipTile*> tiles;
public:
	bool IsDestroyed;
	Ship(std::vector<ShipTile*> shiptiles);
};

