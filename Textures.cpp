#include "Textures.h"

sf::Texture* Textures::WaterTileTexture = new sf::Texture();
sf::Texture* Textures::ExplosionTexture = new sf::Texture();
sf::Texture* Textures::VisibleShipTileTexture = new sf::Texture();
sf::Texture* Textures::DestroyedShipTileTexture = new sf::Texture();
sf::Texture* Textures::HitedShipTileTexture = new sf::Texture();
sf::Sprite* Textures::WaterTileSprite = nullptr;
sf::Sprite* Textures::ExplosionSprite = nullptr;
sf::Sprite* Textures::VisibleShipTileSprite = nullptr;
sf::Sprite* Textures::DestroyedShipTileSprite = nullptr;
sf::Sprite* Textures::HitedShipTileSprite = nullptr;

void Textures::LoadTextures()
{
	WaterTileTexture->loadFromFile("water.png");
	ExplosionTexture->loadFromFile("explosion.png");
	VisibleShipTileTexture->loadFromFile("DiscoveredShip.png");
	DestroyedShipTileTexture->loadFromFile("DestroyedShip.png");
	HitedShipTileTexture->loadFromFile("HitedShip.png");

	WaterTileSprite = new sf::Sprite(*WaterTileTexture, sf::IntRect(0, 32, 32, 32));
	ExplosionSprite = new sf::Sprite(*ExplosionTexture, sf::IntRect(0, 32, 32, 32));
	VisibleShipTileSprite = new sf::Sprite(*VisibleShipTileTexture, sf::IntRect(0, 32, 32, 32));
	DestroyedShipTileSprite = new sf::Sprite(*DestroyedShipTileTexture, sf::IntRect(0, 32, 32, 32));
	HitedShipTileSprite = new sf::Sprite(*HitedShipTileTexture, sf::IntRect(0, 32, 32, 32));
}
