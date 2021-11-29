#pragma once
#include "Board.h"
#include "GameMode.h"

class PlayGameMode : public GameMode
{
	Board board;

public:
	PlayGameMode();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;

};

