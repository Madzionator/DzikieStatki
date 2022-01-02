#pragma once
#include "Button.h"
#include "GameMode.h"

class MenuGameMode : public GameMode
{
	Button playButton;
	Button exitButton;

	sf::Sprite background;
	sf::Sprite logo;

	float backgroundMove = 0;
	float backgroundSpeed = 5;
	float backgroundSize;

public:
	MenuGameMode();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};