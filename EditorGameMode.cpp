#include "EditorGameMode.h"
#include "Button.h"
#include "Game.h"
#include "MenuGameMode.h"
#include "PlayGameMode.h"
#include "ValidatorGenerator.h"
#include "ShipTile.h"
#include "System.h"
#include "Textures.h"
#include "WaterTile.h"

EditorGameMode::EditorGameMode(bool isClassicGame)
{
	this->isClassicGame = isClassicGame;
	auto size = System::Window->getView().getSize();
	background = sf::Sprite(*Textures::get()->MenuBackgroundTexture, sf::IntRect(0, 0, size.x, size.y));
	background.setColor(sf::Color(255, 255, 255, 100));

	header.setSize(sf::Vector2f(System::Window->getView().getSize().x, 50));
	header.setFillColor(sf::Color(51, 164, 68, 255));

	title = sf::Text("Rozstaw swoje statki", *System::Font);
	title.setFillColor(sf::Color(55, 2, 2, 255));
	title.setCharacterSize(24);
	title.setPosition(38, 10);

	board = new Board(this);
	board->setPosition(80, 140);
	board->isEditMode = true;

	message = sf::Text("", *System::Font);
	message.setFillColor(sf::Color::White);
	message.setPosition(428, 173);
	message.setCharacterSize(18);

	playButton = new Button(this, L"Zagraj", sf::Vector2f(150, 40), false);
	playButton->setPosition(428, 98);

	menuButton = new Button(this, L"Menu", sf::Vector2f(100, 40), false);
	menuButton->setPosition(749, 5);
	menuButton->onClick = [] { Game::SetGameMode(new MenuGameMode()); };

	generateShipsButton = new Button(this, L"Generuj statki", sf::Vector2f(200, 40), false);
	generateShipsButton->setPosition(593, 98);

	playButton->onClick = [this]()
	{
		auto validBoard = validateBoard();
		if (!validBoard)
			return;
		board->isEditMode = false;
		Game::SetGameMode(new PlayGameMode(board));
	};

	generateShipsButton->onClick = [this]()
	{
		for (auto s : board->ships)
			delete s;
		board->ships.clear();
		std::vector<Ship*>().swap(board->ships);

		for (int p = 0; p < 100; p++)
			if (board->tiles[p]->TileType == TileType::Ship)
			{
				delete board->tiles[p];
				auto tile = new WaterTile(board);
				tile->setPosition(p % 10 * 32, p / 10 * 32);
				board->tiles[p] = tile;
			}
		int* lengths = new int[10] {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
		ValidatorGenerator::makeBoard(board, lengths, 10, true);
		delete[] lengths;
	};
}

void EditorGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	target.draw(header, states);
	target.draw(title, states);
	target.draw(*board, states);
	target.draw(*playButton, states);
	target.draw(*menuButton, states);
	if(isClassicGame) target.draw(*generateShipsButton, states);
	target.draw(message, states);
}

void EditorGameMode::update(sf::Time deltaTime)
{
	board->update(deltaTime);
	playButton->update(deltaTime);
	menuButton->update(deltaTime);
	auto validBoard = validateBoard();
	if (validBoard)
		playButton->IsEnabled = true;
	else
		playButton->IsEnabled = false;
	if (isClassicGame) generateShipsButton->update(deltaTime);
}

bool EditorGameMode::validateBoard()
{
	message.setString("");
	board->ships.clear();
	std::vector<Ship*>().swap(board->ships);
	prepareBoard();
	if (isClassicGame)
		return ValidatorGenerator::validateForClassicGame(board, &message);
	return ValidatorGenerator::validateForGame(board, &message);
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

		if (y < board->tileCount - 1)
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

EditorGameMode::~EditorGameMode()
{
	delete playButton;
	delete menuButton;
	delete generateShipsButton;
	delete board;
}