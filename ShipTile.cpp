#include "ShipTile.h"

ShipTile::ShipTile(int x, int y, int tileSize) : Tile(x, y, tileSize)
{
	shape = sf::RectangleShape(sf::Vector2f(tileSize, tileSize));
	shape.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
	shape.setFillColor(sf::Color(59, 55, 52));
}

void ShipTile::drawTile(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

void ShipTile::updateTile(sf::Time delta_time)
{
	shape.setFillColor(IsMouseOver ? sf::Color::Red : sf::Color::Green);
}
