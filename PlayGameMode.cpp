#include "PlayGameMode.h"

PlayGameMode::PlayGameMode(Board* playerBoard)
{
	board1 = playerBoard;
	board2 = new Board(this);

	board1->setPosition(50, 100);
	board2->setPosition(400, 100);

}

void PlayGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*board1,states);
	target.draw(*board2,states);
}

void PlayGameMode::update(sf::Time deltaTime)
{
	board1->update(deltaTime);
	board2->update(deltaTime);
}
