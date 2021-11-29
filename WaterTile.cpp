#include "WaterTile.h"

WaterTile::WaterTile(int x, int y, int tileSize) : Tile(x, y, tileSize)
{
	shape = sf::RectangleShape(sf::Vector2f(tileSize, tileSize));
	shape.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
	shape.setFillColor(sf::Color(13, 94, 181));
}

void WaterTile::drawTile(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

void WaterTile::updateTile(sf::Time delta_time)
{
	shape.setFillColor(IsMouseOver
		? sf::Color(25, 120, 191)
		: sf::Color(13, 94, 181));
}
