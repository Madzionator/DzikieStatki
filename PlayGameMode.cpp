#include "PlayGameMode.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

void PlayGameMode::Render()
{
	//Narysuj pole gry
	sf::RectangleShape miner(sf::Vector2f(10, 10));
	window.draw(miner);
}

void PlayGameMode::Update(sf::Time deltaTime)
{

}
