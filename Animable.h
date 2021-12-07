#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Entity.h"

class Animable : public Entity
{
private:
	float timePerFrame = 1.0f / 60; //15fps
	float frameTimeAcc = 0; // accumulator
	int size;
	int frame;
	int frames;

public:
	sf::Sprite* shape;
	sf::Texture* texture;
	bool IsAnimated = true;
	bool IsLooped = true;

	Animable(Entity* parent, sf::Sprite* sprite)
		: Entity(parent), shape(sprite), texture(const_cast<sf::Texture*>(sprite->getTexture()))
	{
		size = texture->getSize().x;

		auto H = texture->getSize().y;
		frames = H / size;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();
		target.draw(*shape, states);
	}

	void update(sf::Time deltaTime) override
	{
		if (texture != nullptr && IsAnimated) {
			frameTimeAcc += deltaTime.asSeconds();

			if (frameTimeAcc > timePerFrame) {
				frame = IsLooped
					? ((frame + 1) % frames)
					: std::min(frame + 1, frames);

				shape->setTextureRect(sf::IntRect(0, frame * size, size, size));
				frameTimeAcc = 0;
			}
		}
	}
};