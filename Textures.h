#pragma once
#include <SFML/Graphics.hpp>

class Textures
{
public:
	static sf::Texture* WaterTileTexture;
	static sf::Texture* ExplosionTexture;
	static sf::Texture* VisibleShipTileTexture;
	static sf::Texture* DestroyedShipTileTexture;
	static sf::Texture* HitedShipTileTexture;

	static sf::Sprite* WaterTileSprite;
	static sf::Sprite* ExplosionSprite;
	static sf::Sprite* DestroyedShipTileSprite;
	static sf::Sprite* VisibleShipTileSprite;
	static sf::Sprite* HitedShipTileSprite;

	static void LoadTextures();
};