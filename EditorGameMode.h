#pragma once
#include "GameMode.h"

class EditorGameMode : public GameMode
{
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

