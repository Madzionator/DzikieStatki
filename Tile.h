#pragma once
#include "Animable.h"
#include "Entity.h"

enum class TileType { Water, Ship };

class Tile : public Entity
{
	sf::RectangleShape overlay;
	Animable waterBackground;
protected:
	Tile(Entity* parent);

public:
	int TileSize;
	TileType TileType = TileType::Water;

	bool IsMouseOver;
	bool IsLeftMouseDown;
	bool IsRightMouseDown;
	bool IsLeftMouseClicked;
	bool IsRightMouseClicked;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;

	void drawOverlay(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateOverlay(sf::Time deltaTime);
};


