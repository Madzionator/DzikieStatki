#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "System.h"
#include "Textures.h"

sf::RenderWindow* System::Window = nullptr;
sf::Font* System::Font = nullptr;
Textures* Textures::instance = new Textures();

int main()
{
	srand(time(0));
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	System::Font = &font;
	Textures::get()->LoadTextures();

	auto game = new Game();
	game->Run();

    return 0;
}
