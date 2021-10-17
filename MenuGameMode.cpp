#include "MenuGameMode.h"

#include "Button.h"
#include "Game.h"
#include "PlayGameMode.h"
#include "System.h"

MenuGameMode::MenuGameMode()
{
	//[](){}
	//[] - zmienne lokalne
	//() - zmienne z funkcji lambda
	//{} - ciało funkcji lambda
	button = Button();
	button.onClick = []()
	{
		Game::SetGameMode(new PlayGameMode());
	};
}

void MenuGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(button);
}

void MenuGameMode::update(sf::Time deltaTime)
{
	button.update(deltaTime);
}
