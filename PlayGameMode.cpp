#include "PlayGameMode.h"

#include "Game.h"
#include "GameOverMode.h"
#include "ShipTile.h"
#include "System.h"
#include "WaterTile.h"

PlayGameMode::PlayGameMode(Board* playerBoard)
{
	playStateText = sf::Text("", *System::Font);
	playStateText.setFillColor(sf::Color::White);
	board1 = playerBoard;
	board2 = new Board(this);
	computer = new Computer();
	MakeComputerBoard();
	pl1ShipLeft = board1->ships.size();
	pl2ShipLeft = board2->ships.size();
	setPlayState(PlayState::PlayerTurn);

	board1->setPosition(50, 100);
	board2->setPosition(400, 100);
}

void PlayGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board1, states);
	target.draw(*board2, states);
	target.draw(playStateText);
}

void PlayGameMode::setPlayState(PlayState ps)
{
	playState = ps;
	if (playState == PlayState::ComputerTurn) {
		playStateText.setString("Komputer oddaje ruch");
		timer = 400;
	}
	else if (playState == PlayState::ComputerThink) {
		playStateText.setString("Komputer mysli nad ruchem");
		timer = 700;
	}
	else if (playState == PlayState::PlayerTurn)
		playStateText.setString("Twoj ruch");
}


void PlayGameMode::update(sf::Time deltaTime)
{
	if (timer > 0) timer -= deltaTime.asMilliseconds();

	board1->update(deltaTime);
	board2->update(deltaTime);
	if (playState == PlayState::PlayerTurn)
	{
		for (int x = 0; x < board2->tileCount * board2->tileCount; x++)
			if (board2->tiles[x]->IsMouseDown)
			{
				auto turnResult = hitTile(board2->tiles[x]);
				if (turnResult == TurnResult::Water)
					setPlayState(PlayState::ComputerThink);
				else if (turnResult == TurnResult::Error)
					playStateText.setString("Wybierz poprawne pole!");
				else
				{
					playStateText.setString("Trafiono! Wybierz kolejne pole");
					if(turnResult == TurnResult::Destroyed)
						if(--pl2ShipLeft == 0)
							Game::SetGameMode(new GameOverMode(true));
				}
			}
	}
	else if (playState == PlayState::ComputerTurn)
	{
		if (timer > 0) return;

		int p = computer->getNextPosition();
		auto turnResult = hitTile(board1->tiles[p]);
		if (turnResult == TurnResult::Hit)
			computer->wasHit(p);
		else if (turnResult == TurnResult::Destroyed)
		{
			computer->wasDestroyed(p);
			if(--pl1ShipLeft == 0)
				Game::SetGameMode(new GameOverMode(false));
		}

		if(turnResult == TurnResult::Water)
			setPlayState(PlayState::PlayerTurn);
	}
	else if(playState == PlayState::ComputerThink)
	{
		if (timer <= 0) setPlayState(PlayState::ComputerTurn);
	}
}

TurnResult PlayGameMode::hitTile(Tile* tile)
{
	if (tile->TileType == TileType::Water)
	{
		auto watertile = (WaterTile*)tile;
		if (watertile->getState() == WaterTileState::Default)
		{
			watertile->setState(WaterTileState::Hit);
			return TurnResult::Water;
		}
	}
	else
	{
		auto shiptile = (ShipTile*)tile;
		if (shiptile->getState() == ShipTileState::Undiscovered || shiptile->getState() == ShipTileState::Visible)
		{
			shiptile->setState(ShipTileState::Damaged);
			auto destroyed = shiptile->ship->checkDestroyed();
			return destroyed ? TurnResult::Destroyed : TurnResult::Hit;
		}
	}
	return TurnResult::Error;
}

void PlayGameMode::MakeComputerBoard()
{
	auto tile1 = new ShipTile(board2);
	auto tile2 = new ShipTile(board2);
	auto tile3 = new ShipTile(board2);
	auto tile4 = new ShipTile(board2);
	tile1->setPosition(4 * 32, 3 * 32);
	tile1->setState(ShipTileState::Undiscovered);
	tile2->setPosition(4 * 32, 4 * 32);
	tile2->setState(ShipTileState::Undiscovered);
	tile3->setPosition(5 * 32, 4 * 32);
	tile3->setState(ShipTileState::Undiscovered);
	tile4->setPosition(8 * 32, 8 * 32);
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
	board2->ships.push_back(new Ship(statek1));
	board2->ships.push_back(new Ship(statek2));
}