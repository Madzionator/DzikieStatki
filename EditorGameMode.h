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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	bool validateBoard();
	void prepareBoard();


public:
	EditorGameMode();
};