#include "GameOverMode.h"
#include "Button.h"
#include "Game.h"
#include "MenuGameMode.h"
#include "System.h"

GameOverMode::GameOverMode(bool isWin, Board* playerBoard, Board* computerBoard)
{
	board1 = playerBoard;
	board2 = computerBoard;
	for (int i = 0; i < 100; i++)
	{
		if (board2->tiles[i]->TileType == TileType::Ship)
			if (((ShipTile*)board2->tiles[i])->getState() == ShipTileState::Undiscovered)
				((ShipTile*)board2->tiles[i])->setState(ShipTileState::Visible);
	}

	backGround.setSize(sf::Vector2f(System::Window->getSize()));
	backGround.setFillColor(sf::Color::Color(0, 0, 0, 124));
	header.setSize(sf::Vector2f(System::Window->getSize().x, 50));
	header.setFillColor(sf::Color::Color(179, 46, 40, 255));
	result = sf::Text("", *System::Font);
	result.setFillColor(sf::Color::Color(55, 2, 2,255));
	result.setCharacterSize(24);
	result.setPosition(38, 10);
	if (isWin)
		result.setString(L"Zwycięstwo!");
	else
		result.setString("Przegrana :(");

	menuButton = new Button(this);
	menuButton->onClick = []()
	{
		Game::SetGameMode(new MenuGameMode());
	};
	menuButton->setPosition(0, 50);
	menuButton->setText("Menu");
}

void GameOverMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board1, states);
	target.draw(*board2, states);
	target.draw(backGround, states);
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
