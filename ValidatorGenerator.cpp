#include "ValidatorGenerator.h"

void ValidatorGenerator::makeBoard(Board* board, int* shipLengths, int n, bool isPlayer)
{
	while (true)
	{
		auto shipsP = generateShips(shipLengths, n);

		if (shipsP.size() < n)
		{
			shipsP.clear();
			continue;
		}

		for (auto& shipP : shipsP)
		{
			std::vector<ShipTile*> ship;
			for (int p : shipP)
			{
				auto tile = new ShipTile(board);
				tile->setPosition(p % 10 * 32, p / 10 * 32);
				if (isPlayer)
					tile->setState(ShipTileState::Visible);
				else
					tile->setState(ShipTileState::Undiscovered);
				board->tiles[p] = tile;
				ship.push_back(tile);
			}
			board->ships.push_back(new Ship(ship));
		}
		break;
	}
}

std::vector<std::vector<int>> ValidatorGenerator::generateShips(int* shipLengths, int n)
{
	std::vector<std::vector<int>>ships;
	std::vector<int> tilesLeft;
	for (int i = 0; i < 100; i++)
		tilesLeft.push_back(i);

	int iterarions = 0;

	for (int shipNumber = 0; shipNumber < n; shipNumber++)
	{
		std::vector<int> shipPos;
		std::vector<int> shipsurroundings;

		auto exist = [&](int p)
		{
			for (int i = 0; i < shipsurroundings.size(); i++)
				if (shipsurroundings[i] == p)
					return true;
			return false;
		};

		auto findIndex = [&](int p)
		{
			for (int i = 0; i < tilesLeft.size(); i++)
				if (tilesLeft[i] == p)
					return i;
			return -1;
		};

		auto addSurroundings = [&](int p)
		{
			if (p / 10 > 0 && findIndex(p - 10) >= 0 && !exist(p - 10)) shipsurroundings.push_back(p - 10);
			if (p / 10 < 9 && findIndex(p + 10) >= 0 && !exist(p + 10)) shipsurroundings.push_back(p + 10);
			if (p % 10 > 0 && findIndex(p - 1) >= 0 && !exist(p - 1)) shipsurroundings.push_back(p - 1);
			if (p % 10 < 9 && findIndex(p + 1) >= 0 && !exist(p + 1)) shipsurroundings.push_back(p + 1);
		};

		int size = shipLengths[shipNumber];
		while (size > 0)
		{
			iterarions++;
			if (tilesLeft.size() == 0)
				return std::vector<std::vector<int>>();

			if (shipPos.size() == 0)
			{
				int r = rand() % tilesLeft.size();
				int p = tilesLeft[r];
				shipPos.push_back(p);
				size--;
				tilesLeft.erase(tilesLeft.begin() + r);
				addSurroundings(p);
			}
			else if (shipsurroundings.size() == 0)
			{
				shipsurroundings.clear();
				for (int s = 0; s < shipPos.size(); s++)
					tilesLeft.push_back(shipPos[s]);
				shipPos.clear();
				size = shipLengths[shipNumber];
			}
			else
			{
				int i = -1, p;
				do
				{
					int r = rand() % shipsurroundings.size();
					p = shipsurroundings[r];
					shipsurroundings.erase(shipsurroundings.begin() + r);
					i = findIndex(p);
				} while (i < 0 && shipsurroundings.size() > 0);

				if (i == -1)
					continue;

				p = tilesLeft[i];
				shipPos.push_back(p);
				size--;
				tilesLeft.erase(tilesLeft.begin() + i);
				addSurroundings(p);
			}

			if (iterarions > 255)
				return std::vector<std::vector<int>>();
		}

		for (int s = 0; s < shipPos.size(); s++)
		{
			int p = shipPos[s];

			int i = (p / 10 > 0 && p % 10 > 0) ? findIndex(p - 11) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);

			i = i = (p / 10 > 0) ? findIndex(p - 10) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);

			i = i = (p / 10 > 0 && p % 10 < 9) ? findIndex(p - 9) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);

			i = i = (p % 10 > 0) ? findIndex(p - 1) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);

			i = i = (p % 10 < 9) ? findIndex(p + 1) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);

			i = i = (p / 10 < 9 && p % 10 > 0) ? findIndex(p + 9) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);

			i = i = (p / 10 < 9) ? findIndex(p + 10) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);

			i = (p / 10 < 9 && p % 10 < 9) ? findIndex(p + 11) : -1;
			if (i >= 0) tilesLeft.erase(tilesLeft.begin() + i);
		}

		ships.push_back(shipPos);

		shipPos.clear();
		shipsurroundings.clear();
	}
	return ships;
}

bool ValidatorGenerator::validateForGame(Board* board, sf::Text* message)
{
	bool validBoard = true;

	auto isOtherShip = [&](int currentP, int nearP)
	{
		if (board->tiles[nearP]->TileType == TileType::Ship)
		{
			auto currShip = ((ShipTile*)board->tiles[currentP])->ship;
			auto nearShip = ((ShipTile*)board->tiles[nearP])->ship;
			if (currShip != nearShip)
				validBoard = false;
		}
	};

	for (int p = 0; p < 100; p++)
	{
		if (board->tiles[p]->TileType == TileType::Ship)
		{
			if (p / 10 > 0 && p % 10 > 0) isOtherShip(p, p - 11);
			if (p / 10 > 0) isOtherShip(p, p - 10);
			if (p / 10 > 0 && p % 10 < 9) isOtherShip(p, p - 9);
			if (p % 10 > 0) isOtherShip(p, p - 1);
			if (p % 10 < 9) isOtherShip(p, p + 1);
			if (p / 10 < 9 && p % 10 > 0) isOtherShip(p, p + 9);
			if (p / 10 < 9) isOtherShip(p, p + 10);
			if (p / 10 < 9 && p % 10 < 9) isOtherShip(p, p + 11);

			if (!validBoard)
			{
				message->setString(L"Statki nie mogą się stykać, nawet rogami.\n");
				break;
			}
		}
	}

	if (board->ships.size() > 10)
	{
		message->setString(message->getString() + L"Maksymalna liczba statków to 10, stworzyłeś " + std::to_string(board->ships.size()) + ".\n");
		validBoard = false;
	}

	int tilesCounter = 0;
	bool overSizeShip = false;
	for (auto ship : board->ships)
	{
		if (ship->getTiles()->size() > 8) overSizeShip = true;
		tilesCounter += ship->getTiles()->size();
	}
	if (overSizeShip)
	{
		message->setString(message->getString() + L"Maksymakny rozmiar statku to 8.\n");
		validBoard = false;
	}

	if (tilesCounter > 40)
	{
		message->setString(message->getString() + L"Dozwolonych 40 pól statków, użyłeś " + std::to_string(tilesCounter) + ".\n");
		validBoard = false;
	}

	if (tilesCounter < 1)
	{
		message->setString(message->getString() + L"Brak statków.\n");
		validBoard = false;
	}

	return validBoard;
}

bool ValidatorGenerator::validateForClassicGame(Board* board, sf::Text* message)
{
	bool validBoard = true;

	auto isOtherShip = [&](int currentP, int nearP)
	{
		if (board->tiles[nearP]->TileType == TileType::Ship)
		{
			auto currShip = ((ShipTile*)board->tiles[currentP])->ship;
			auto nearShip = ((ShipTile*)board->tiles[nearP])->ship;
			if (currShip != nearShip)
				validBoard = false;
		}
	};

	for (int p = 0; p < 100; p++)
	{
		if (board->tiles[p]->TileType == TileType::Ship)
		{
			if (p / 10 > 0 && p % 10 > 0) isOtherShip(p, p - 11);
			if (p / 10 > 0) isOtherShip(p, p - 10);
			if (p / 10 > 0 && p % 10 < 9) isOtherShip(p, p - 9);
			if (p % 10 > 0) isOtherShip(p, p - 1);
			if (p % 10 < 9) isOtherShip(p, p + 1);
			if (p / 10 < 9 && p % 10 > 0) isOtherShip(p, p + 9);
			if (p / 10 < 9) isOtherShip(p, p + 10);
			if (p / 10 < 9 && p % 10 < 9) isOtherShip(p, p + 11);

			if (!validBoard)
			{
				message->setString(L"Statki nie mogą się stykać, nawet rogami.\n");
				break;
			}
		}
	}

	for (auto ship : board->ships)
		if (ship->getTiles()->size() > 4)
		{
			message->setString(message->getString() + L"Maksymakny rozmiar statku to 4.\n");
			validBoard = false;
		}

	int size[4] = {0, 0, 0, 0};
	for (auto ship : board->ships)
	{
		if (ship->getTiles()->size() > 4)
			continue;
		size[ship->getTiles()->size() - 1]++;
	}

	if (size[0] != 4)
	{
		message->setString(message->getString() + L"Powinny być 4 jednomasztowce, stworzyłeś " + std::to_wstring(size[0])+"\n");
		validBoard = false;
	}

	if (size[1] != 3)
	{
		message->setString(message->getString() + L"Powinny być 3 dwumasztowce, stworzyłeś " + std::to_wstring(size[1]) + "\n");
		validBoard = false;
	}

	if (size[2] != 2)
	{
		message->setString(message->getString() + L"Powinny być 2 trójmasztowce, stworzyłeś " + std::to_wstring(size[2]) + "\n");
		validBoard = false;
	}

	if (size[3] != 1)
	{
		message->setString(message->getString() + L"Powinnien być 1 czteromasztowiec, stworzyłeś " + std::to_wstring(size[3]) + "\n");
		validBoard = false;
	}

	if (board->ships.size() != 10)
	{
		message->setString(message->getString() + L"W sumie należy stworzyć 10 statków, masz " + std::to_string(board->ships.size()) + ".\n");
		validBoard = false;
	}

	return validBoard;
}
