#include "PlayGameMode.h"

#include "ShipTile.h"
#include "System.h"
#include "WaterTile.h"

void PlayGameMode::setPlayState(PlayState ps)
{
	playState = ps;
	if (playState == PlayState::ComputerTurn)
		playStateText.setString("Komputer oddaje ruch");
	else if (playState == PlayState::PlayerTurn)
		playStateText.setString("Twój ruch");
}

PlayGameMode::PlayGameMode(Board* playerBoard)
{
	playStateText = sf::Text("", *System::Font);
	playStateText.setFillColor(sf::Color::White);
	board1 = playerBoard;
	board2 = new Board(this);
	MakeComputerBoard();
	setPlayState(PlayState::PlayerTurn);


	board1->setPosition(50, 100);
	board2->setPosition(400, 100);

}

void PlayGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board1,states);
	target.draw(*board2,states);
	target.draw(playStateText);
}

void PlayGameMode::update(sf::Time deltaTime)
{
	board1->update(deltaTime);
	board2->update(deltaTime);
	if(playState == PlayState::PlayerTurn)
	{
		for (int x = 0; x < board2->tileCount * board2->tileCount; x++)
			if (board2->tiles[x]->IsMouseDown)
			{
				auto tile = board2->tiles[x];
				if(tile->TileType == TileType::Water)
				{
					auto watertile = (WaterTile*)tile;
					if (watertile->getState() == WaterTileState::Default)
					{
						watertile->setState(WaterTileState::Hit);
						setPlayState(PlayState::ComputerTurn);
					}
				}
				else
				{
					auto shiptile = (ShipTile*)tile;
					if(shiptile->getState() == ShipTileState::Undiscovered)
					{
						shiptile->setState(ShipTileState::Damaged);
						auto temp = shiptile->ship->checkDestroyed();
						setPlayState(PlayState::ComputerTurn);
					}
				}
			}
	}
}

void PlayGameMode::MakeComputerBoard()
{
	auto tile1 = new ShipTile(board2);
	auto tile2 = new ShipTile(board2);
	auto tile3 = new ShipTile(board2);
	auto tile4 = new ShipTile(board2);
	tile1->setPosition(4*32, 3*32);
	tile1->setState(ShipTileState::Undiscovered);
	tile2->setPosition(4*32, 4*32);
	tile2->setState(ShipTileState::Undiscovered);
	tile3->setPosition(5*32, 4*32);
	tile3->setState(ShipTileState::Undiscovered);
	tile4->setPosition(8*32, 8*32);
	tile4->setState(ShipTileState::Undiscovered);
	board2->tiles[34] = tile1;
	board2->tiles[44] = tile2;
	board2->tiles[45] = tile3;
	board2->tiles[88] = tile4;
	std::vector<ShipTile*> statek1;
	std::vector<ShipTile*> statek2;
	statek1.push_back(tile1);
	statek1.push_back(tile2);
	statek1.push_back(tile3);
	statek2.push_back(tile4);
	new Ship(statek1);
	new Ship(statek2);
}