#include "MenuGameMode.h"

#include "Button.h"
#include "EditorGameMode.h"
#include "Game.h"
#include "System.h"
#include "Textures.h"

MenuGameMode::MenuGameMode() :
	playButton(this, L"Zagraj", sf::Vector2f(150, 40), true),
	exitButton(this, L"Wyjdź", sf::Vector2f(150, 40), true),
	background(*Textures::get()->MenuBackgroundTexture),
	logo(*Textures::get()->LogoTexture)
{
	auto windowSize = System::Window->getView().getSize();
	backgroundSize = background.getTexture()->getSize().x;
	background.setTextureRect(sf::IntRect(0, 0, windowSize.x + backgroundSize, windowSize.y + backgroundSize));
	background.setColor(sf::Color(255, 255, 255, 100));

	playButton.onClick = [] { Game::SetGameMode(new EditorGameMode()); };
	playButton.setPosition(windowSize.x / 2, 300);

	exitButton.onClick = [] { exit(0); };
	exitButton.setPosition(windowSize.x / 2, 400);

	auto logoWidth = logo.getLocalBounds().width;
	logo.setPosition(windowSize.x / 2 - logoWidth / 2, 50);
}

void MenuGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	target.draw(playButton, states);
	target.draw(exitButton, states);
	target.draw(logo, states);
}

void MenuGameMode::update(sf::Time deltaTime)
{
	playButton.update(deltaTime);
	exitButton.update(deltaTime);

	backgroundMove += backgroundSpeed * deltaTime.asSeconds();
	if (backgroundMove > backgroundSize) backgroundMove -= backgroundSize;
	background.setPosition(-backgroundMove, -backgroundMove);
}