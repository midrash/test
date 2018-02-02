#include "Game.h"
#include <iostream>
#include "Avatar.h"
using namespace std;

Game* Game::m_instance = NULL;

Game::Game()
{
	m_avatar = new Avatar(m_maze.getStartPos().X,
							m_maze.getStartPos().Y,
							"⊙");
	int(*arrMap)[MAP_WIDTH] = m_maze.getMapData();

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (arrMap[i][j] == 1)
			{
				Block* block = new Block(i, j, "▦");
				m_blockLst.push_back(block);
			}
		}
	}
	m_startTime = clock();
	m_renderTime = 60.f;
}

Game::~Game()
{
	delete m_blockLst.back();
	m_blockLst.pop_back();
}

Game* Game::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new Game();
	}
	return m_instance;
}

void Game::run()
{
	// 무한 반복문을 활용해 _kbhit과 getch()를 활용해
	// 키보드 입력 받는 클래스 작성
	m_pathFinder.SetData();

	while (true)
	{
		updateInput();
		checkSum();
		render();
		renderTimer();
		//게임 완료 로직
		if (checkEnd())
		{
			break;
		}
	}
}

bool Game::checkEnd()
{
	bool ret = false;
	COORD pos = m_avatar->getPos();
	if (pos.X == m_maze.getEndPos().X
		&&pos.Y == m_maze.getEndPos().Y)
	{
		ret = true;
	}
	if (m_renderTime <= 0)
	{
		m_pathFinder.PathFind(m_avatar->getPos().X, m_avatar->getPos().Y);
		ret = true;
	}
	return ret;
}

void Game::updateInput()
{
	if (m_inputController.CheckKbHit())
	{
		char inputChar = m_inputController.GetInputChar();
		COORD pos = { 0,0 };
		COORD prePos = m_avatar->getPos();
		if (inputChar == 'a' || inputChar == 'A')
		{
			//케릭터를 왼쪽으로  이동
			pos.X = -1;
		}
		else if (inputChar == 's' || inputChar == 'S')
		{
			//케릭터를 아래로 이동
			pos.Y = 1;
		}
		else if (inputChar == 'd' || inputChar == 'D')
		{
			//케릭터를 오른쪽 이동
			pos.X = 1;
		}
		else if (inputChar == 'w' || inputChar == 'W')
		{
			//케릭터를 위로 이동
			pos.Y = -1;
		}
		m_avatar->Move(pos);
		COORD curPos = m_avatar->getPos();

		//curPos 가 유효한지 체크
		//유효하지 않다면 이전 좌표를 다시 대입

		bool isValidPos = false;
		if (curPos.X >= 0 && curPos.X < 15
			&& curPos.Y >= 0 && curPos.Y < 15)
		{
			isValidPos = true;
		}

		auto iter = m_blockLst.begin();
		for (iter; iter != m_blockLst.end(); iter++)
		{
			if ((*iter)->getPos().X == curPos.X
				&& (*iter)->getPos().Y == curPos.Y)
			{
				isValidPos = false;
				break;
			}
		}

		if (!isValidPos)
		{
			m_avatar->setPos(prePos);
		}
	}
}

void Game::render()
{
	//새로 그려야 하는 좌표를 가져와서 그 좌표를 지운다
	auto iter = m_difPosLst.begin();
	for (iter; iter != m_difPosLst.end(); ++iter)
	{
		COORD pos = (*iter);
		pos.X *= 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		cout << "  ";
	}

	//새로 그려야 하는 좌표에 오브젝트가 있다면
	//새로 그린다
	auto iter2 = m_blockLst.begin();
	for (iter2; iter2 != m_blockLst.end(); ++iter2)
	{
		iter = m_difPosLst.begin();
		for (iter; iter != m_difPosLst.end(); ++iter)
		{
			COORD pos = (*iter);
			COORD objPos = (*iter2)->getPos();
			if (pos.X == objPos.X && pos.Y == objPos.Y)
			{
				(*iter2)->Render();
			}
		}
	}

	iter = m_difPosLst.begin();
	for (iter; iter != m_difPosLst.end(); ++iter)
	{
		COORD pos = (*iter);
		COORD objPos = m_avatar->getPos();
		if (pos.X == objPos.X && pos.Y == objPos.Y)
		{
			m_avatar->Render();
		}
	}
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			m_curMap[i][j] = m_nextMap[i][j];
		}
	}
}

void Game::checkSum()
{
	//새로 그려야 하는 좌표들 체크해서 어딘가에 넣어다
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			m_nextMap[i][j] = TAG_NONE;
		}
	}

	auto iter = m_blockLst.begin();
	for (iter; iter != m_blockLst.end(); ++iter)
	{
		(*iter)->PreRender();
	}
	m_avatar->PreRender();

	m_difPosLst.clear();
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (m_curMap[i][j] != m_nextMap[i][j])
			{
				//좌표를 어딘가에 기억시킨다
				COORD pos = { i,j };
				m_difPosLst.push_back(pos);
			}
		}
	}
}

void Game::renderTimer()
{
	time_t curTime = clock();
	float flowTime = (float)(curTime - m_startTime) / (CLOCKS_PER_SEC);
	m_renderTime = 5 - flowTime;
	COORD pos = { 20, 15 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << m_renderTime;
}