#pragma once
#include "Board.h"
#include "GameMode.h"

class PlayGameMode : public GameMode
{
	Board* board1;
	Board* board2;
	void MakeComputerBoard();
public:
	PlayGameMode(Board* board);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

