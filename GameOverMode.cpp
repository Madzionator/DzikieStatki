#include "GameOverMode.h"
#include "Button.h"
#include "Game.h"
#include "MenuGameMode.h"
#include "System.h"
#include "Textures.h"

GameOverMode::GameOverMode(bool isWin, Board* playerBoard, Board* computerBoard)
{
	auto size = System::Window->getSize();
	background = sf::Sprite(*Textures::get()->MenuBackgroundTexture, sf::IntRect(0, 0, size.x, size.y));
	background.setColor(sf::Color(255, 255, 255, 100));

	menuButton = new Button(this, L"Powrót do menu", sf::Vector2f(200, 40), true);
	menuButton->onClick = [](){ Game::SetGameMode(new MenuGameMode()); };
	menuButton->setPosition(size.x / 2, 50);

	board1 = playerBoard;
	board2 = computerBoard;
	for (int i = 0; i < 100; i++)
	{
		if (board2->tiles[i]->TileType == TileType::Ship)
		{
			if (((ShipTile*)board2->tiles[i])->getState() == ShipTileState::Undiscovered)
				((ShipTile*)board2->tiles[i])->setState(ShipTileState::Visible);
			else if (((ShipTile*)board2->tiles[i])->getState() == ShipTileState::Blocked)
				((ShipTile*)board2->tiles[i])->setState(ShipTileState::BlockedVisible);
		}
	}

	shadow = sf::RectangleShape(sf::Vector2f(size));
	shadow.setFillColor(sf::Color(0, 0, 0, 150));

	header.setSize(sf::Vector2f(System::Window->getSize().x, 50));
	header.setFillColor(sf::Color(179, 46, 40, 255));
	result = sf::Text("", *System::Font);
	result.setFillColor(sf::Color(55, 2, 2,255));
	result.setCharacterSize(24);
	result.setPosition(38, 10);
	if (isWin)
		result.setString(L"Zwycięstwo!");
	else
		result.setString(L"Przegrana :(");
}

void GameOverMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	target.draw(*board1, states);
	target.draw(*board2, states);
	target.draw(shadow, states);
	target.draw(header, states);
	target.draw(result, states);
	target.draw(*menuButton, states);
}

void GameOverMode::update(sf::Time deltaTime)
{
	menuButton->update(deltaTime);
	board1->update(deltaTime);
	board2->update(deltaTime);
}
