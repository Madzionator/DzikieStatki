#include "PlayGameMode.h"

#include "ShipTile.h"

PlayGameMode::PlayGameMode(Board* playerBoard)
{
	board1 = playerBoard;
	board2 = new Board(this);
	MakeComputerBoard();

	board1->setPosition(50, 100);
	board2->setPosition(400, 100);

}

void PlayGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board1,states);
	target.draw(*board2,states);
}

void PlayGameMode::update(sf::Time deltaTime)
{
	board1->update(deltaTime);
	board2->update(deltaTime);
}

void PlayGameMode::MakeComputerBoard()
{
	auto tile1 = new ShipTile(this);
	auto tile2 = new ShipTile(this);
	auto tile3 = new ShipTile(this);
	auto tile4 = new ShipTile(this);
	tile1->setPosition(4*32, 3*32);
	tile1->setState(ShipTileState::Undiscovered);
	tile2->setPosition(4*32, 4*32);
	tile2->setState(ShipTileState::Undiscovered);
	tile3->setPosition(5*32, 4*32);
	tile3->setState(ShipTileState::Undiscovered);
	tile4->setPosition(8*32, 8*32);
	tile4->setState(ShipTileState::Undiscovered);
	board2->tiles[43] = tile1;
	board2->tiles[44] = tile2;
	board2->tiles[54] = tile3;
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