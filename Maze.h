#pragma once
#include "global.h"
#include <Windows.h>
//typedef int(*Temp)[MAP_HEIGHT];
class Maze
{
public:
	Maze();
	inline COORD getEndPos()	{ return m_endPos; };
	inline COORD getStartPos()	{ return m_startPos; };
	//Temp getMapData() { return m_map; };
	int (*getMapData())[MAP_HEIGHT] { return m_map; };
private:
	static int m_map[MAP_WIDTH][MAP_HEIGHT];
	COORD m_startPos, m_endPos;
};