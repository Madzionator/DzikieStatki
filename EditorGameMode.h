#pragma once
#include "GameMode.h"

class EditorGameMode : public GameMode
{
	void Render() override;
	void Update(sf::Time deltaTime) override;
};

