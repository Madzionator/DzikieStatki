#pragma once
#include "Button.h"
#include "GameMode.h"

class MenuGameMode : public GameMode
{
	Button* button;

public:
	MenuGameMode();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

