#pragma once
#include "Animable.h"
#include "Entity.h"

enum class TileType { Water, Ship };

class Tile : public Entity
{
	sf::RectangleShape* overlay;
protected:
	Tile(Entity* parent, sf::Sprite* sprite);
	Animable* animable;

public:
	int TileSize;
	TileType TileType = TileType::Water;

	bool IsMouseOver;
	bool IsMouseDown;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::Time deltaTime) override;
};


