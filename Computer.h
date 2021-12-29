#pragma once
#include <vector>

class Computer
{
	std::vector<int> tilesLeft;
	std::vector<int> currentDamagedShip;
	std::vector<int> shipSurrounding;
	
public:
	Computer();
	int getNextPosition();
	void wasHit(int position);
	void wasDestroyed(int position);
};

