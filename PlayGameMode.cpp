#include "PlayGameMode.h" 
#include "Game.h"
#include "GameOverMode.h"
#include "ShipTile.h"
#include "System.h"
#include "Textures.h"
#include "WaterTile.h"
#include <functional>

PlayGameMode::PlayGameMode(Board* playerBoard) :
	explosionAnimation(this, Textures::get()->ExplosionTexture),
	splashAnimation(this, Textures::get()->SplashTexture)
{
	auto size = System::Window->getView().getSize();
	background = sf::Sprite(*Textures::get()->MenuBackgroundTexture, sf::IntRect(0, 0, size.x, size.y));
	background.setColor(sf::Color(255, 255, 255, 100));

	board1 = playerBoard;
	board2 = new Board(this);
	board1->setPosition(80, 140);
	board2->setPosition(480, 140);

	playStateText = sf::Text("", *System::Font);
	playStateText.setFillColor(sf::Color::White);
	playStateText.setCharacterSize(24);
	playStateText.setPosition(38, 10);
	boardDesc1 = sf::Text("", *System::Font);
	boardDesc2 = sf::Text("", *System::Font);
	boardDesc1.setCharacterSize(18);
	boardDesc2.setCharacterSize(18);
	boardDesc1.setFillColor(sf::Color::White);
	boardDesc2.setFillColor(sf::Color::White);
	boardDesc1.setPosition(38, 65);
	boardDesc2.setPosition(438, 65);

	header.setSize(sf::Vector2f(System::Window->getView().getSize().x, 50));
	header.setFillColor(sf::Color::Color(21, 137, 181, 255));

	MakeComputerBoard();

	auto shipLengths = std::vector<int>();
	for (auto s : board1->ships)
		shipLengths.push_back(s->getTiles()->size());
	std::sort(shipLengths.begin(), shipLengths.end());

	computer = new Computer(shipLengths);

	playerShipsLeft = board1->ships.size();
	computerShipsLeft = board2->ships.size();
	setPlayState(PlayState::PlayerTurn);

	explosionAnimation.IsLooped = false;
	explosionAnimation.IsAnimated = false;
	splashAnimation.IsLooped = false;
	splashAnimation.IsAnimated = false;
	splashAnimation.shape->setPosition(0, -5); //center splash to water hole
}

void PlayGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	target.draw(*board1, states);
	target.draw(*board2, states);
	target.draw(header, states);
	target.draw(boardDesc1, states);
	target.draw(boardDesc2, states);
	target.draw(playStateText);
	target.draw(explosionAnimation, states);
	target.draw(splashAnimation, states);
}

void PlayGameMode::setPlayState(PlayState ps)
{
	playState = ps;
	if (playState == PlayState::ComputerTurn) {
		playStateText.setString("Komputer oddaje ruch");
		timer = 400;
	}
	else if (playState == PlayState::ComputerThink) {
		playStateText.setString(L"Komputer myśli nad ruchem");
		timer = 700;
	}
	else if (playState == PlayState::PlayerTurn)
		playStateText.setString(L"Twój ruch");
}

void PlayGameMode::update(sf::Time deltaTime)
{
	if (timer > 0) timer -= deltaTime.asMilliseconds();

	board1->update(deltaTime);
	board2->update(deltaTime);
	explosionAnimation.update(deltaTime);
	splashAnimation.update(deltaTime);

	if (isDrawingBlock && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) isDrawingBlock = false;

	for (int x = 0; x < board2->tileCount * board2->tileCount; x++)
		if (board2->tiles[x]->IsRightMouseDown)
		{
			if (board2->tiles[x]->TileType == TileType::Water)
			{
				auto tile = (WaterTile*)board2->tiles[x];
				if (!isDrawingBlock)
				{
					isDrawingBlock = true;
					shouldDrawBlocks = tile->getState() != WaterTileState::Blocked;
				}
				if (shouldDrawBlocks && tile->getState() == WaterTileState::Default)
					tile->setState(WaterTileState::Blocked);
				else if (!shouldDrawBlocks && tile->getState() == WaterTileState::Blocked)
					tile->setState(WaterTileState::Default);

			}
			else if (board2->tiles[x]->TileType == TileType::Ship)
			{
				auto tile = (ShipTile*)board2->tiles[x];
				if (!isDrawingBlock)
				{
					isDrawingBlock = true;
					shouldDrawBlocks = tile->getState() != ShipTileState::Blocked;
				}
				if (shouldDrawBlocks && tile->getState() == ShipTileState::Undiscovered)
					tile->setState(ShipTileState::Blocked);
				else if (!shouldDrawBlocks && tile->getState() == ShipTileState::Blocked)
					tile->setState(ShipTileState::Undiscovered);
			}
		}

	if (playState == PlayState::PlayerTurn)
	{
		for (int x = 0; x < board2->tileCount * board2->tileCount; x++)
			if (board2->tiles[x]->IsLeftMouseClicked)
			{
				auto turnResult = hitTile(board2->tiles[x]);
				if (turnResult == TurnResult::Water) {
					PlayAnimation(&splashAnimation, board2, board2->tiles[x]);
					setPlayState(PlayState::ComputerThink);
				}
				else if (turnResult == TurnResult::Error)
					playStateText.setString("Wybierz poprawne pole!");
				else
				{
					PlayAnimation(&explosionAnimation, board2, board2->tiles[x]);
					playStateText.setString("Trafiono! Wybierz kolejne pole");
					if (turnResult == TurnResult::Destroyed)
						if (--computerShipsLeft == 0)
							Game::SetGameMode(new GameOverMode(true, board1, board2));
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
			if (--playerShipsLeft == 0)
				Game::SetGameMode(new GameOverMode(false, board1, board2));
		}

		if (turnResult == TurnResult::Hit || turnResult == TurnResult::Destroyed) {
			setPlayState(PlayState::ComputerThink);
			PlayAnimation(&explosionAnimation, board1, board1->tiles[p]);
		}

		if (turnResult == TurnResult::Water) {
			PlayAnimation(&splashAnimation, board1, board1->tiles[p]);
			setPlayState(PlayState::PlayerTurn);
		}
	}
	else if (playState == PlayState::ComputerThink)
	{
		if (timer <= 0) setPlayState(PlayState::ComputerTurn);
	}

	boardDesc1.setString(L"Moja plansza (pozostałe statki: " + std::to_wstring(playerShipsLeft) + L")");
	boardDesc2.setString(L"Plansza przeciwnika (pozostałe statki: " + std::to_wstring(computerShipsLeft) + L")");
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
	int n = board1->ships.size();
	int* lengths = new int[n];
	for (int i = 0; i < n; i++)
		lengths[i] = board1->ships[i]->getTiles()->size();

	std::sort(lengths, lengths + n, std::greater<>());

	while (true)
	{
		auto shipsP = GenerateShips(lengths, n);

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
				auto tile = new ShipTile(board2);
				tile->setPosition(p % 10 * 32, p / 10 * 32);
				tile->setState(ShipTileState::Undiscovered);
				board2->tiles[p] = tile;
				ship.push_back(tile);
			}
			board2->ships.push_back(new Ship(ship));
		}
		break;
	}
}

std::vector<std::vector<int>> PlayGameMode::GenerateShips(int* lengths, int n)
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

		int size = lengths[shipNumber];
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
				size = lengths[shipNumber];
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

void PlayGameMode::PlayAnimation(Animable* animation, Board* board, Tile* tile)
{
	animation->Restart();
	animation->setPosition(board->getTransform() * tile->getPosition());
	animation->IsAnimated = true;
}