#pragma once
#include <functional>
#include "Entity.h"

class Button : public Entity
{
	sf::RectangleShape shape;
	sf::Text text;
	void updateSize();

public:
	std::function<void()> onClick;
	Button(Entity* parent, std::wstring txt, sf::Vector2f size, bool centered = false);
	bool IsEnabled = true;
	bool IsMouseOver = false;
	bool IsMouseDown = false;
	bool IsCentered = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	void setText(std::wstring txt) { text.setString(txt); updateSize(); }
	void setSize(sf::Vector2f vec) { shape.setSize(vec); updateSize(); }
	void setCentered(bool centered) { IsCentered = centered; updateSize(); }
};