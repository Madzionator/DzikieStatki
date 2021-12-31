#include "EditorGameMode.h"
#include "Button.h"
#include "Game.h"
#include "PlayGameMode.h"
#include "ShipTile.h"
#include "System.h"

EditorGameMode::EditorGameMode()
{
	board = new Board(this);
	board->setPosition(50, 50);
	board->isEditMode = true;

	message = sf::Text("", *System::Font);
	message.setFillColor(sf::Color::White);
	message.setPosition(400, 125);
	message.setCharacterSize(18);

	playButton = new Button(this);
	playButton->setText("GRAJ");
	playButton->setPosition(400, 50);

	playButton->onClick = [this]()
	{
		auto validBoard = validateBoard();
		if (!validBoard)
			return;
		board->isEditMode = false;
		Game::SetGameMode(new PlayGameMode(board));
	};
}

void EditorGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board, states);
	target.draw(*playButton, states);
	target.draw(message, states);
}

void EditorGameMode::update(sf::Time deltaTime)
{
	board->update(deltaTime);
	playButton->update(deltaTime);
	auto validBoard = validateBoard();
	if (validBoard)
		playButton->isEnabled = true;
	else
		playButton->isEnabled = false;
}

bool EditorGameMode::validateBoard()
{
	message.setString("");
	board->ships.clear();
	prepareBoard();
	bool validBoard = true;

	std::vector<ShipTile*> tiles;

	auto isOtherShip = [&](int currentP, int nearP)
	{
		if (board->tiles[nearP]->TileType == TileType::Ship)
		{
			auto currShip = ((ShipTile*)board->tiles[currentP])->ship;
			auto nearShip = ((ShipTile*)board->tiles[nearP])->ship;
			if(currShip != nearShip)
				validBoard = false;
		}
	};

	for(int p = 0; p< 100; p++)
	{
		if(board->tiles[p]->TileType == TileType::Ship)
		{
			if(p/10 > 0 && p%10 > 0) isOtherShip(p, p - 11);
			if(p/10 > 0) isOtherShip(p, p - 10);
			if(p/10 > 0 && p%10 < 9) isOtherShip(p, p - 9);
			if(p%10 > 0) isOtherShip(p, p - 1);
			if(p%10 < 9) isOtherShip(p, p + 1);
			if(p/10 < 9 && p%10 > 0) isOtherShip(p, p + 9);
			if(p/10 < 9) isOtherShip(p, p + 10);
			if(p/10 < 9 && p%10 < 9) isOtherShip(p, p + 11);

			if(!validBoard)
			{
				message.setString("Statki nie moga sie stykac, nawet rogami.\n");
				break;
			}
		}
	}

	if(board->ships.size() > 10)
	{
		message.setString(message.getString() + "Maksymakna liczba statkow to 10, zrobiles "+ std::to_string(board->ships.size())  +".\n");
		validBoard = false;
	}

	int tilesCounter = 0;
	bool overSizeShip = false;
	for (auto ship : board->ships)
	{
		if (ship->getTiles()->size() > 8) overSizeShip = true;
		tilesCounter += ship->getTiles()->size();
	}
	if(overSizeShip)
	{
		message.setString(message.getString() + "Maksymakny rozmiar statku to 8.\n");
		validBoard = false;
	}

	if (tilesCounter > 40)
	{
		message.setString(message.getString() + "Dozwolonych 40 pol statkow, uzyles " + std::to_string(tilesCounter) + ".\n");
		validBoard = false;
	}

	if (tilesCounter < 1)
	{
		message.setString(message.getString() + "Brak statkow.\n");
		validBoard = false;
	}

	return validBoard;
}

void EditorGameMode::prepareBoard()
{
	using namespace std;
	auto shipList = vector<vector<ShipTile*>>();
	auto isAssigned = [&](ShipTile* currentTile)
	{
		for (auto ship : shipList)
			for (auto tile : ship)
				if (tile == currentTile)
					return true;
		return false;
	};

	std::function<void(int, int)> buildShip = [&](int y, int x)
	{
		auto tile = board->tiles[10 * y + x];
		if (tile->TileType != TileType::Ship)
			return;

		if (isAssigned((ShipTile*)tile))
			return;

		shipList.back().push_back((ShipTile*)tile);

		if(y < board->tileCount - 1)
			buildShip(y + 1, x);
		if (y > 0)
			buildShip(y - 1, x);
		if (x > 0)
			buildShip(y, x - 1);
		if (x < board->tileCount - 1)
			buildShip(y, x + 1);
	};

	for (int y = 0; y < board->tileCount; y++)
		for (int x = 0; x < board->tileCount; x++)
		{
			if (board->tiles[10 * y + x]->TileType != TileType::Ship)
				continue;

			if (isAssigned((ShipTile*)board->tiles[10 * y + x]))
				continue;

			auto vec = vector<ShipTile*>();
			shipList.push_back(vec);
			buildShip(y, x);
		}

	for (auto shipTiles : shipList)
	{
		auto ship = new Ship(shipTiles);
		board->ships.push_back(ship);
	}
}
