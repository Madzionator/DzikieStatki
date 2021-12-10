#pragma once
#include <vector>

class ShipTile;

enum class ShipTileState { Undiscovered, Visible, Damaged, Destroyed };

class Ship
{
	std::vector<ShipTile*> tiles;
public:
	bool IsDestroyed;
	Ship(std::vector<ShipTile*> shiptiles);
};

