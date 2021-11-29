#include "Tile.h"

#include "System.h"

Tile::Tile(int x, int y, int tileSize)
{
	X = x;
	Y = y;
	TileSize = tileSize;
	shape = sf::RectangleShape(sf::Vector2f(tileSize, tileSize));
	shape.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawTile(target, states);
}

void Tile::update(sf::Time delta_time)
{
	auto mouseVec = sf::Mouse::getPosition(*System::Window);
	auto xd = sf::RenderStates(sf::Transform().translate(50, 100));
	auto xdd = xd.transform.getInverse().transformPoint(sf::Vector2f(mouseVec.x, mouseVec.y));

	IsMouseOver = shape.getGlobalBounds().contains(xdd);
	IsMouseDown = IsMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Left);

	updateTile(delta_time);
}
