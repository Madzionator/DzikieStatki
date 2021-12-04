#include "Tile.h"

#include "System.h"

Tile::Tile(Entity* parent, sf::Sprite* sprite)
	: Entity(parent), TileSize(32)
{
	animable = new Animable(this, sprite);
	overlay = new sf::RectangleShape(sf::Vector2f(TileSize, TileSize));
	overlay->setFillColor(sf::Color(255, 255, 0, 50));
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*animable, states);
	target.draw(*overlay, states);
}

void Tile::update(sf::Time delta_time)
{
	auto mouseVec = sf::Mouse::getPosition(*System::Window);
	auto localMousePosition = (parent->getTransform() * getTransform()).getInverse().transformPoint(sf::Vector2f(mouseVec.x, mouseVec.y));

	IsMouseOver = animable->shape->getLocalBounds().contains(localMousePosition);
	IsMouseDown = IsMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Left);

	overlay->setFillColor(sf::Color(255, 255, 0, IsMouseOver ? 50 : 0));
	animable->update(delta_time);
}
