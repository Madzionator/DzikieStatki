#include "Tile.h"

#include "System.h"

Tile::Tile(Entity* parent, sf::Sprite* sprite)
	: Entity(parent), TileSize(32)
{
	if(sprite)
		animable = new Animable(this, sprite);
	overlay = new sf::RectangleShape(sf::Vector2f(TileSize, TileSize));
	overlay->setFillColor(sf::Color(255, 255, 0, 50));
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(animable) 
		target.draw(*animable, states);
	target.draw(*overlay, states);
}

void Tile::update(sf::Time delta_time)
{
	auto mouseVec = sf::Mouse::getPosition(*System::Window);
	auto localMousePosition = (parent->getTransform() * getTransform()).getInverse().transformPoint(System::Window->mapPixelToCoords(mouseVec));

	IsMouseOver = overlay->getLocalBounds().contains(localMousePosition);
	IsMouseDown = IsMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Left);

	overlay->setFillColor(sf::Color(255, 255, 0, (IsMouseDown ? 20 : 0) + ( IsMouseOver ? 50 : 0)));

	if(animable)
		animable->update(delta_time);
}
