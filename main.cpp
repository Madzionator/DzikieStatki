#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "System.h"
#include "Textures.h"

int main()
{
	srand(time(0));
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	System::Font = &font;
	Textures::LoadTextures();

	auto game = new Game();
	game->Run();
	
	
    return 0;
}
