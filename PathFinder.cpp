#include "PathFinder.h"
#include "Game.h"
#include <iostream>
PathFinder::PathFinder()
{
}

void PathFinder::SetData()
{
	int(*arrMap)[MAP_WIDTH] = Game::getInstance()->getMaze().getMapData();
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{

			m_map[i][j] = arrMap[i][j];
		}
	}
}
bool PathFinder::PathFind(int x, int y)
{
	COORD endPos = Game::getInstance()->getEndPos();
	if (x < 0 || y < 0
		|| x >= MAP_WIDTH || y >= MAP_HEIGHT)
	{
		return false;
	}
	else if (m_map[x][y] != 0)
	{
		return false;
	}
	else if (x == endPos.X && y == endPos.Y)
	{
		m_map[x][y] = 3;
		return true;
	}
	else
	{
		m_map[x][y] = 3;
		if (this->PathFind(x - 1, y) || this->PathFind(x + 1, y) ||
			this->PathFind(x, y - 1) || this->PathFind(x, y + 1))
		{
			return true;
		}
		m_map[x][y] = 2;
		return false;
	}
}