#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Entity.h"

class Animable : public Entity
{
private:
	sf::Time frameTime; //15fps
	sf::Time currentTime; // accumulator
	int size;
	int frame;
	int frames;

public:
	void Restart() { frame = 0; }
	sf::Sprite* shape;
	sf::Texture* texture;
	bool IsAnimated = true;
	bool IsLooped = true;

	Animable(Entity* parent, sf::Texture* texture) :
		Entity(parent),
		currentTime(sf::Time::Zero),
		shape(new sf::Sprite(*texture)),
		texture(texture)
	{
		frameTime = sf::seconds(0.05f);
		size = texture->getSize().x;

		auto H = texture->getSize().y;
		frames = H / size;
		shape->setTextureRect(sf::IntRect(0, 0, size, size));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();
		target.draw(*shape, states);
	}

	void update(sf::Time deltaTime) override
	{
		if (texture != nullptr && IsAnimated) {
			currentTime += deltaTime;
			if (currentTime >= frameTime) {
				currentTime = sf::microseconds(currentTime.asMicroseconds() % frameTime.asMicroseconds());

				if (frame + 1 < frames)
					frame++;
				else if (IsLooped)
					frame = 0;
				shape->setTextureRect(sf::IntRect(0, frame * size, size, size));
			}
		}
	}
};