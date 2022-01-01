#include "Tile.h"
#include "System.h"
#include "Textures.h"

Tile::Tile(Entity* parent) : Entity(parent), TileSize(32), waterBackground(this, Textures::get()->WaterTileTexture)
{
	overlay = sf::RectangleShape(sf::Vector2f(TileSize, TileSize));
	overlay.setFillColor(sf::Color(255, 255, 0, 50));
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(waterBackground, states);
}

void Tile::update(sf::Time delta_time)
{
	auto mouseVec = sf::Mouse::getPosition(*System::Window);
	auto localMousePosition = (parent->getTransform() * getTransform()).getInverse().transformPoint(System::Window->mapPixelToCoords(mouseVec));

	IsMouseOver = overlay.getLocalBounds().contains(localMousePosition);
	IsMouseDown = IsMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Left);

	waterBackground.update(delta_time);
}

void Tile::drawOverlay(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(overlay, states);
}

void Tile::updateOverlay(sf::Time delta_time)
{
	overlay.setFillColor(sf::Color(255, 255, 0, (IsMouseDown ? 20 : 0) + (IsMouseOver ? 50 : 0)));
}
