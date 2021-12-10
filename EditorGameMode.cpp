#include "EditorGameMode.h"
#include "Button.h"
#include "Game.h"
#include "PlayGameMode.h"

void EditorGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board, states);
	target.draw(*playButton, states);
}

void EditorGameMode::update(sf::Time deltaTime)
{
	board->update(deltaTime);
	playButton->update(deltaTime);
}

EditorGameMode::EditorGameMode()
{
	board = new Board(this);
	board->setPosition(200, 50);
	board->isEditMode = true;

	playButton = new Button(this);
	playButton->setText("GRAJ");

	playButton->onClick = [this]()
	{
		board->isEditMode = false;
		Game::SetGameMode(new PlayGameMode(board));
	};
}
