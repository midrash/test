#pragma once
#include "Maze.h"
#include <vector>
#include "Block.h"
#include "InputController.h"
#include <time.h>
#include "PathFinder.h"
class Avatar;

class Game
{
public:
	static Game* getInstance();
	~Game();
	void run();
	void setNextMap(int x, int y, int tag)
	{
		m_nextMap[x][y] = tag;
	}
	std::vector<Block*>& getBlockLst()
	{
		return m_blockLst;
	}
	COORD getEndPos()
	{
		return m_maze.getEndPos();
	}
	Maze getMaze()
	{
		return m_maze;
	}
private:
	static Game* m_instance;
	Game();
	void render();
	void checkSum();
	void updateInput();
	bool checkEnd();
	void renderTimer();
	Maze m_maze;
	std::vector<Block*> m_blockLst;
	Avatar* m_avatar;

	std::vector<COORD> m_difPosLst;
	int m_curMap[MAP_WIDTH][MAP_HEIGHT];
	int m_nextMap[MAP_WIDTH][MAP_HEIGHT];
	InputController m_inputController;
	time_t m_startTime;
	float m_renderTime;

	PathFinder m_pathFinder;
};