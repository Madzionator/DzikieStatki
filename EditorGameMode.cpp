#include "EditorGameMode.h"

void EditorGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
}

void EditorGameMode::update(sf::Time deltaTime)
{

}
