#pragma once
#include "Board.h"
#include "GameMode.h"

enum class PlayState { PlayerTurn, ComputerTurn };

class PlayGameMode : public GameMode
{
	PlayState playState = PlayState::PlayerTurn;
	Board* board1;
	Board* board2;
	void MakeComputerBoard();
	sf::Text playStateText;
	void setPlayState(PlayState ps);
	bool hitTile(Tile* tile);
public:
	PlayGameMode(Board* board);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

