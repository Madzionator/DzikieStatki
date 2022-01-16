#include "Computer.h"
#include "Tile.h"
#include <functional>

Computer::Computer(std::vector<int> shipLengths)
{
	for (int i = 0; i < 100; i++)
		tilesLeft.push_back(i);
	this->shipLengths = shipLengths;
}

int Computer::getNextPosition()
{
	if (currentDamagedShip.size() == 0)
	{
		int p, i = -1;
		while (true)
		{
			i = rand() % tilesLeft.size();
			p = tilesLeft[i];
			p = validatePosition(p);
			if (p != -1)
				break;
		}
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
	auto canAdd = [&](int p)
	{
		for (auto pos : shipSurrounding)
			if (pos == p)
				return false;

		for (auto pos : tilesLeft)
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

	if (x > 0 && canAdd(position - 1))
		add(position - 1);
	if (y > 0 && canAdd(position - 10))
		add(position - 10);
	if (x < 9 && canAdd(position + 1))
		add(position + 1);
	if (y < 9 && canAdd(position + 10))
		add(position + 10);
}

void Computer::wasDestroyed(int position)
{
	auto tryRemove = [&](int y, int x)
	{
		if (y < 0 || y > 9 || x < 0 || x > 9)
			return;
		tilesLeft.erase(std::remove(tilesLeft.begin(), tilesLeft.end(), (y * 10 + x)), tilesLeft.end());
	};

	currentDamagedShip.push_back(position);

	auto first = std::find(shipLengths.begin(), shipLengths.end(), currentDamagedShip.size());
	if (first != shipLengths.end()) shipLengths.erase(first);

	shipSurrounding.clear();
	for (auto pos : currentDamagedShip)
	{
		int y = pos / 10, x = pos % 10;

		tryRemove(y - 1, x - 1);
		tryRemove(y - 1, x);
		tryRemove(y - 1, x + 1);
		tryRemove(y, x - 1);
		tryRemove(y, x + 1);
		tryRemove(y + 1, x - 1);
		tryRemove(y + 1, x);
		tryRemove(y + 1, x + 1);
	}
	currentDamagedShip.clear();
}

int Computer::validatePosition(int p)
{
	auto positions = std::vector<int>();

	std::function<void(int)> findNeighbours = [&](int p)
	{
		if (std::find(tilesLeft.begin(), tilesLeft.end(), p) == tilesLeft.end())
			return;

		if (std::find(positions.begin(), positions.end(), p) != positions.end())
			return;

		positions.push_back(p);
		if (p / 10 > 0) findNeighbours(p - 10);
		if (p / 10 < 9) findNeighbours(p + 10);
		if (p % 10 > 0) findNeighbours(p - 1);
		if (p % 10 < 9) findNeighbours(p + 1);
	};

	findNeighbours(p);

	if (positions.size() < shipLengths[0])
	{
		for (auto position : positions)
			tilesLeft.erase(std::remove(tilesLeft.begin(), tilesLeft.end(), position), tilesLeft.end());
		return -1;
	}

	if (positions.size() > 10) {
		tilesLeft.erase(std::remove(tilesLeft.begin(), tilesLeft.end(), p), tilesLeft.end());
		return p;
	}

	int bestPosIdx, bestDist = 2137;
	for (int posIdx = 0; posIdx < positions.size(); posIdx++)
	{
		int dist = 0;
		for (int i = 0; i < positions.size(); i++)
		{
			if (posIdx == i)
				continue;

			dist += abs(positions[posIdx] / 10 - positions[i] / 10);
			dist += abs(positions[posIdx] % 10 - positions[i] % 10);
		}
		if (dist < bestDist)
		{
			bestDist = dist;
			bestPosIdx = posIdx;
		}
	}

	tilesLeft.erase(std::remove(tilesLeft.begin(), tilesLeft.end(), positions[bestPosIdx]), tilesLeft.end());
	return positions[bestPosIdx];
}

Computer::~Computer()
{
	tilesLeft.clear();
	std::vector<int>().swap(tilesLeft);
	currentDamagedShip.clear();
	std::vector<int>().swap(currentDamagedShip);
	shipSurrounding.clear();
	std::vector<int>().swap(shipSurrounding);
	shipLengths.clear();
	std::vector<int>().swap(shipLengths);
}