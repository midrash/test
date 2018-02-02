#pragma once
#include <Windows.h>
#include "global.h"
class PathFinder
{
public:
	PathFinder();
	void SetData();
	bool PathFind(int x, int y);
private:
	int m_map[MAP_WIDTH][MAP_HEIGHT];
};