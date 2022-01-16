#pragma once
#include <SFML/Graphics.hpp>

class GameMode;

class Game
{
public:
	Game();
	void Run();
	static void SetGameMode(GameMode* gameMode);

private:
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();
	sf::RenderWindow mWindow;
	static const sf::Time TimePerFrame;

	static GameMode* currentGameMode;
	static GameMode* nextGameMode;
};