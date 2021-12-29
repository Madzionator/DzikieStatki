#pragma once
#include "Board.h"
#include "Computer.h"
#include "GameMode.h"

enum class PlayState { PlayerTurn, ComputerThink, ComputerTurn };
enum class TurnResult { Error, Water, Hit, Destroyed };

class PlayGameMode : public GameMode
{
	PlayState playState = PlayState::PlayerTurn;
	Board* board1;
	Board* board2;
	Computer* computer;
	int pl1ShipLeft;
	int pl2ShipLeft;

	void MakeComputerBoard();
	sf::Text playStateText;
	void setPlayState(PlayState ps);
	TurnResult hitTile(Tile* tile);
	int timer;
public:
	PlayGameMode(Board* board);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

