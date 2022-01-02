#pragma once
#include <SFML/Graphics.hpp>

class Textures
{
	Textures() {}
	static Textures* instance;
public:
	static Textures* get()
	{
		return instance;
	}
	sf::Texture* Empty = new sf::Texture();

	sf::Texture* LogoTexture = new sf::Texture();
	sf::Texture* BoardBackgroundTexture = new sf::Texture();
	sf::Texture* MenuBackgroundTexture = new sf::Texture();

	sf::Texture* WaterTileTexture = new sf::Texture();
	sf::Texture* WaterHitTileTexture = new sf::Texture();
	sf::Texture* WaterBlockedTileTexture = new sf::Texture();
	sf::Texture* ExplosionTexture = new sf::Texture();
	sf::Texture* SplashTexture = new sf::Texture();
	sf::Texture* VisibleShipTileTexture = new sf::Texture();
	sf::Texture* DestroyedShipTileTexture = new sf::Texture();
	sf::Texture* DamagedShipTileTexture = new sf::Texture();
	sf::Texture* BlockedVisibleShipTileTexture = new sf::Texture();

	void LoadTextures()
	{
		Empty->create(32, 32);

		LogoTexture->loadFromFile("logo.png");
		BoardBackgroundTexture->loadFromFile("board-bg.png");
		MenuBackgroundTexture->loadFromFile("menu-bg.png");
		MenuBackgroundTexture->setRepeated(true);
		MenuBackgroundTexture->setSmooth(true);

		WaterTileTexture->loadFromFile("water.png");
		WaterHitTileTexture->loadFromFile("waterHit.png");
		WaterBlockedTileTexture->loadFromFile("waterBlocked.png");
		ExplosionTexture->loadFromFile("explosion.png");
		SplashTexture->loadFromFile("splash.png");
		VisibleShipTileTexture->loadFromFile("DiscoveredShip.png");
		DestroyedShipTileTexture->loadFromFile("DestroyedShip.png");
		DamagedShipTileTexture->loadFromFile("DamagedShip.png");
		BlockedVisibleShipTileTexture->loadFromFile("blockedVisibleShip.png");
	}
};