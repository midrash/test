#include <iostream>
#include "Game.h"
int main()
{
	
	Game::getInstance()->run();

	std::cout << "���� ����..." << std::endl;
	getchar();

	return 0;
}