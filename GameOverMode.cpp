#include "GameOverMode.h"
#include "Button.h"
#include "Game.h"
#include "MenuGameMode.h"

GameOverMode::GameOverMode(bool isWin)
{
	menuButton = new Button(this);
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
}

void GameOverMode::update(sf::Time deltaTime)
{
	menuButton->update(deltaTime);
}
