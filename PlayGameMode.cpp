#include "PlayGameMode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

PlayGameMode::PlayGameMode()
{
	board1 = new Board(this);
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
