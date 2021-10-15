#pragma once
#include "GameMode.h"

class MenuGameMode : public GameMode
{
	void Render() override;
	void Update(sf::Time deltaTime) override;
};

