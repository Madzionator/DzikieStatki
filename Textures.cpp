#include "Textures.h"

sf::Texture* Textures::WaterTileTexture = new sf::Texture();
sf::Texture* Textures::ExplosionTexture = new sf::Texture();
sf::Texture* Textures::DiscoveredShipTileTexture = new sf::Texture();
sf::Texture* Textures::DestroyedShipTileTexture = new sf::Texture();
sf::Sprite* Textures::WaterTileSprite = nullptr;
sf::Sprite* Textures::ExplosionSprite = nullptr;
sf::Sprite* Textures::DiscoveredShipTileSprite = nullptr;
sf::Sprite* Textures::DestroyedShipTileSprite = nullptr;

void Textures::LoadTextures()
{
	WaterTileTexture->loadFromFile("water.png");
	ExplosionTexture->loadFromFile("explosion.png");
	DiscoveredShipTileTexture->loadFromFile("DiscoveredShip.png");
	DestroyedShipTileTexture->loadFromFile("DestroyedShip.png");

	WaterTileSprite = new sf::Sprite(*WaterTileTexture, sf::IntRect(0, 32, 32, 32));
	ExplosionSprite = new sf::Sprite(*ExplosionTexture, sf::IntRect(0, 32, 32, 32));
	DiscoveredShipTileSprite = new sf::Sprite(*DiscoveredShipTileTexture, sf::IntRect(0, 32, 32, 32));
	DestroyedShipTileSprite = new sf::Sprite(*DestroyedShipTileTexture, sf::IntRect(0, 32, 32, 32));
}
