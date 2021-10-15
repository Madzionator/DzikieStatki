#pragma once
#include <SFML/System/Time.hpp>

class GameMode
{
public:
	virtual void Update(sf::Time deltaTime);
	virtual void Render();
};

