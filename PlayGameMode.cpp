#include "PlayGameMode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

PlayGameMode::PlayGameMode()
{
	board = Board();
}

void PlayGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(50, 100);
	target.draw(board,states);
}

void PlayGameMode::update(sf::Time deltaTime)
{
	board.update(deltaTime);
}
