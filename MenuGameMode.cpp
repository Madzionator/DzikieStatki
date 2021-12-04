#include "MenuGameMode.h"

#include "Button.h"
#include "Game.h"
#include "PlayGameMode.h"
#include "System.h"

MenuGameMode::MenuGameMode()
{
	button = new Button(this);
	button->onClick = []()
	{
		Game::SetGameMode(new PlayGameMode());
	};
	button->setPosition(50, 50);
}

void MenuGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*button, states);
}

void MenuGameMode::update(sf::Time deltaTime)
{
	button->update(deltaTime);
}
