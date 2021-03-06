#pragma once
#include "Board.h"
#include "Button.h"
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
	int playerShipsLeft;
	int computerShipsLeft;
	int timer;
	Button* menuButton;
	sf::Text playStateText;
	sf::Text boardDesc1;
	sf::Text boardDesc2;
	sf::Sprite background;
	sf::RectangleShape header;
	Animable explosionAnimation;
	Animable splashAnimation;

	bool isDrawingBlock;
	bool shouldDrawBlocks;
	bool prepareNextMode = false;

	void MakeComputerBoard();
	void setPlayState(PlayState ps);
	void PlayAnimation(Animable* animation, Board* board, Tile* tile);
	TurnResult hitTile(Tile* tile);

public:
	PlayGameMode(Board* board);
	~PlayGameMode();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};