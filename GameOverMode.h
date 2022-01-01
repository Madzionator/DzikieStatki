#pragma once
#include "Board.h"
#include "GameMode.h"

class Button;

class GameOverMode : public GameMode
{
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	Button* menuButton;
	Board* board1;
	Board* board2;
	void prepareBoard();

public:
	GameOverMode(bool isWin, Board* board1, Board* board2);
};

