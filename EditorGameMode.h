#pragma once
#include "Board.h"
#include "GameMode.h"

class Button;

class EditorGameMode : public GameMode
{
	sf::Sprite background;
	sf::RectangleShape header;
	sf::Text message;
	sf::Text title;
	Board* board;
	Button* playButton;
	Button* generateShipsButton;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	bool validateBoard();
	void prepareBoard();
	bool isClassicGame;

public:
	EditorGameMode(bool isClassicGame);
};