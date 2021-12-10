#include "MenuGameMode.h"

#include "Button.h"
#include "EditorGameMode.h"
#include "Game.h"

MenuGameMode::MenuGameMode()
{
	button = new Button(this);
	button->onClick = []()
	{
		Game::SetGameMode(new EditorGameMode());
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
