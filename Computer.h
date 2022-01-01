#pragma once
#include <vector>

class Computer
{
	std::vector<int> tilesLeft;
	std::vector<int> currentDamagedShip;
	std::vector<int> shipSurrounding;
	std::vector<int> shipLengths;
	
public:
	Computer(std::vector<int> shipLengths);
	int getNextPosition();
	void wasHit(int position);
	void wasDestroyed(int position);
};

