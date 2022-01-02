#pragma once
#include "Board.h"
#include "GameMode.h"

class Button;

class EditorGameMode : public GameMode
{
	sf::Sprite background;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	Board* board;
	Button* playButton;
	bool validateBoard();
	void prepareBoard();
	sf::Text message;
public:
	EditorGameMode();
};

