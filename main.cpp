#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "System.h"

int main()
{

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	System::Font = &font;

	auto game = new Game();
	game->Run();
	
	
    return 0;
}
