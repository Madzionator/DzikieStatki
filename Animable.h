#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Entity.h"

class Animable : public Entity
{
private:
	sf::Time frameTime; 
	sf::Time currentTime;
	int imageSize;
	int currentFrame;
	int maxFrames;

public:
	void Restart() { currentFrame = 0; }
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
		frameTime = sf::seconds(0.05f); // 1/20th of second
		imageSize = texture->getSize().x;

		auto H = texture->getSize().y;
		maxFrames = H / imageSize;
		shape->setTextureRect(sf::IntRect(0, 0, imageSize, imageSize));
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

				if (currentFrame + 1 < maxFrames)
					currentFrame++;
				else if (IsLooped)
					currentFrame = 0;
				
				shape->setTextureRect(sf::IntRect(0, currentFrame * imageSize, imageSize, imageSize));
			}
		}
	}
};