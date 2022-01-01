#include "GameOverMode.h"
#include "Button.h"
#include "Game.h"
#include "MenuGameMode.h"

GameOverMode::GameOverMode(bool isWin, Board* playerBoard, Board* computerBoard)
{
	menuButton = new Button(this);
	board1 = playerBoard;
	board2 = computerBoard;
	for(int i = 0; i < 100; i++)
	{
		if (board2->tiles[i]->TileType == TileType::Ship)
			if (((ShipTile*)board2->tiles[i])->getState() == ShipTileState::Undiscovered)
				((ShipTile*)board2->tiles[i])->setState(ShipTileState::Visible);
	}
	menuButton->onClick = []()
	{
		Game::SetGameMode(new MenuGameMode());
	};
	menuButton->setPosition(50, 50);
}

void GameOverMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*menuButton, states);
	target.draw(*board1, states);
	target.draw(*board2, states);

}

void GameOverMode::update(sf::Time deltaTime)
{
	menuButton->update(deltaTime);
	board1->update(deltaTime);
	board2->update(deltaTime);
}
