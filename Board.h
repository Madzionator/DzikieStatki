#pragma once
#include "Entity.h"
#include "ShipTile.h"

class Tile;

class Board : public Entity
{
	sf::Sprite boardBackground;
	const int tileSize = 32;
	bool isDrawing = false;
	TileType drawType;
public:
	bool isEditMode;
	const int tileCount = 10;
	Tile** tiles;
	std::vector<Ship*> ships;
	Board(Entity* parent);
	~Board();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};