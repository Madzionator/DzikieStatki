#pragma once
#include "Board.h"
#include "GameMode.h"

class Button;

class GameOverMode : public GameMode
{
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	Board* board;
	Button* menuButton;
	void prepareBoard();

public:
	GameOverMode(bool isWin);
};

