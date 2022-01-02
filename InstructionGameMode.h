#pragma once
#include "GameMode.h"
#include "Button.h"

class InstructionGameMode : public GameMode
{
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	Button menuButton;
	sf::RectangleShape header;
	sf::Sprite background;
	sf::Text title;
	sf::Text subtitle1;
	sf::Text subtitle2;
	sf::Text subtitle3;
	sf::Text description1;
	sf::Text description2;
	sf::Text description3;

public:
	InstructionGameMode();
};

