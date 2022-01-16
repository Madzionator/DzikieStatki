#pragma once
#include <functional>
#include "Entity.h"

class Button : public Entity
{
	sf::RectangleShape shape;
	sf::Text text;
	void updatePosition();
	sf::Color buttonEnableColor;

public:
	std::function<void()> onClick;
	Button(Entity* parent, std::wstring txt, sf::Vector2f size, bool centered = false, sf::Color buttonEnableColor = sf::Color(60, 200, 80));
	bool IsEnabled = true;
	bool IsMouseOver = false;
	bool IsMouseDown = false;
	bool IsMouseClicked = false;
	bool IsCentered = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time deltaTime) override;
	void setText(std::wstring txt) { text.setString(txt); updatePosition(); }
	void setTextColor(sf::Color color) { text.setFillColor(color); }
	void setSize(sf::Vector2f vec) { shape.setSize(vec); updatePosition(); }
	void setCentered(bool centered) { IsCentered = centered; updatePosition(); }
};