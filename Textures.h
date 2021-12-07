#pragma once
#include <SFML/Graphics.hpp>

class Textures
{
public:
	static sf::Texture* WaterTileTexture;
	static sf::Texture* ExplosionTexture;
	static sf::Texture* DiscoveredShipTileTexture;
	static sf::Texture* DestroyedShipTileTexture;

	static sf::Sprite* WaterTileSprite;
	static sf::Sprite* ExplosionSprite;
	static sf::Sprite* DestroyedShipTileSprite;
	static sf::Sprite* DiscoveredShipTileSprite;

	static void LoadTextures();
};