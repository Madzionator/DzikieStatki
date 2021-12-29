#include "Computer.h"

Computer::Computer()
{
	for (int i = 0; i < 100; i++)
		tilesLeft.push_back(i);
}

int Computer::getNextPosition()
{
	if (currentDamagedShip.size() == 0)
	{
		int i = rand() % tilesLeft.size();
		int p = tilesLeft[i];
		tilesLeft.erase(tilesLeft.begin() + i);
		return p;
	}
	else
	{
		int i = rand() % shipSurrounding.size();
		int p = shipSurrounding[i];
		shipSurrounding.erase(shipSurrounding.begin() + i);
		return p;
	}
}

void Computer::wasHit(int position)
{
	auto exist = [&](int p)
	{
		for (auto pos : shipSurrounding)
			if (pos == p)
				return true;
		return false;
	};

	auto add = [&](int p)
	{
		shipSurrounding.push_back(p);
		tilesLeft.erase(std::remove(tilesLeft.begin(), tilesLeft.end(), p), tilesLeft.end());
	};

	currentDamagedShip.push_back(position);
	int y = position / 10, x = position % 10;

	if (x > 0 && !exist(position - 1))
		add(position - 1);
	if (y > 0 && !exist(position - 10))
		add(position - 10);
	if (x < 9 && !exist(position + 1))
		add(position + 1);
	if (y < 9 && !exist(position + 10))
		add(position + 10);
}

void Computer::wasDestroyed(int position)
{
	auto tryRemove = [&](int y, int x)
	{
		if (y < 0 || y > 9 || x < 0 || x > 9)
			return;
		tilesLeft.erase(std::remove(tilesLeft.begin(), tilesLeft.end(), (y*10 + x)), tilesLeft.end());
	};

	currentDamagedShip.push_back(position);
	shipSurrounding.clear();
	for (auto pos : currentDamagedShip)
	{
		int y = pos / 10, x = pos % 10;
		tryRemove(y - 1, x - 1);
		tryRemove(y - 1, x );
		tryRemove(y - 1, x + 1);
		tryRemove(y, x - 1);
		tryRemove(y, x + 1);
		tryRemove(y + 1, x - 1);
		tryRemove(y + 1, x);
		tryRemove(y + 1, x + 1);
	}
	currentDamagedShip.clear();
}
