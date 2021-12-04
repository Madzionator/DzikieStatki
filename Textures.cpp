#include "Textures.h"

sf::Texture* Textures::WaterTileTexture = new sf::Texture();
sf::Texture* Textures::ShipTileTexture = new sf::Texture();
sf::Texture* Textures::ExplosionTexture = new sf::Texture();
sf::Sprite* Textures::ShipTileSprite = nullptr;
sf::Sprite* Textures::WaterTileSprite = nullptr;
sf::Sprite* Textures::ExplosionSprite = nullptr;

void Textures::LoadTextures()
{
	WaterTileTexture->loadFromFile("water.png");
	ShipTileTexture->loadFromFile("ship.png");
	ExplosionTexture->loadFromFile("explosion.png");

	ShipTileSprite = new sf::Sprite(*ShipTileTexture, sf::IntRect(0, 32, 32, 32));
	WaterTileSprite = new sf::Sprite(*WaterTileTexture, sf::IntRect(0, 32, 32, 32));
	ExplosionSprite = new sf::Sprite(*ExplosionTexture, sf::IntRect(0, 32, 32, 32));
}
