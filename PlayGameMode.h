#pragma once
#include "GameMode.h"

class PlayGameMode : public GameMode
{
	void Render() override;
	void Update(sf::Time deltaTime) override;
};

