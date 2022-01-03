#pragma once
#include "Board.h"

class ValidatorGenerator
{
	static std::vector<std::vector<int>> generateShips(int* shipLengths, int n);
public:
	static void makeBoard(Board* board, int* shipLengths, int n, bool isPlayer);
	static bool validateForGame(Board* board, sf::Text* message);
	static bool validateForClassicGame(Board* board, sf::Text* message);
};