#pragma once
#include <SFML/Graphics.hpp>

class Textures
{
public:
	static sf::Texture* WaterTileTexture;
	static sf::Texture* ShipTileTexture;
	static sf::Texture* ExplosionTexture;

	static sf::Sprite* WaterTileSprite;
	static sf::Sprite* ShipTileSprite;
	static sf::Sprite* ExplosionSprite;

	static void LoadTextures();
};