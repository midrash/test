#include <iostream>
#include "Game.h"
int main()
{
	
	Game::getInstance()->run();

	std::cout << "게임 종료..." << std::endl;
	getchar();

	return 0;
}