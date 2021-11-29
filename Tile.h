#pragma once
#include <functional>
#include "Entity.h"

class Tile : public Entity
{
	sf::RectangleShape shape;
protected:
	sf::Transform transform;

	Tile(int x, int y, int tileSize);
	virtual void drawTile(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void updateTile(sf::Time deltaTime) = 0;

public:
	int X;
	int Y;
	int TileSize;

	bool IsMouseOver;
	bool IsMouseDown;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
};

