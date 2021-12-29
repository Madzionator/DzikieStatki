#include "EditorGameMode.h"

#include <iostream>

#include "Button.h"
#include "Game.h"
#include "PlayGameMode.h"
#include "ShipTile.h"

void EditorGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board, states);
	target.draw(*playButton, states);
}

void EditorGameMode::update(sf::Time deltaTime)
{
	board->update(deltaTime);
	playButton->update(deltaTime);
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



EditorGameMode::EditorGameMode()
{
	board = new Board(this);
	board->setPosition(200, 50);
	board->isEditMode = true;

	playButton = new Button(this);
	playButton->setText("GRAJ");

	playButton->onClick = [this]()
	{
		board->isEditMode = false;
		prepareBoard();
		Game::SetGameMode(new PlayGameMode(board));
	};
}
