#include "Game.h"
#include <iostream>
#include "Avatar.h"
using namespace std;

Game* Game::m_instance = NULL;

Game::Game()
{
	m_avatar = new Avatar(m_maze.getStartPos().X,
							m_maze.getStartPos().Y,
							"��");
	int(*arrMap)[MAP_WIDTH] = m_maze.getMapData();

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (arrMap[i][j] == 1)
			{
				Block* block = new Block(i, j, "��");
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
	// ���� �ݺ����� Ȱ���� _kbhit�� getch()�� Ȱ����
	// Ű���� �Է� �޴� Ŭ���� �ۼ�
	m_pathFinder.SetData();

	while (true)
	{
		updateInput();
		checkSum();
		render();
		renderTimer();
		//���� �Ϸ� ����
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
			//�ɸ��͸� ��������  �̵�
			pos.X = -1;
		}
		else if (inputChar == 's' || inputChar == 'S')
		{
			//�ɸ��͸� �Ʒ��� �̵�
			pos.Y = 1;
		}
		else if (inputChar == 'd' || inputChar == 'D')
		{
			//�ɸ��͸� ������ �̵�
			pos.X = 1;
		}
		else if (inputChar == 'w' || inputChar == 'W')
		{
			//�ɸ��͸� ���� �̵�
			pos.Y = -1;
		}
		m_avatar->Move(pos);
		COORD curPos = m_avatar->getPos();

		//curPos �� ��ȿ���� üũ
		//��ȿ���� �ʴٸ� ���� ��ǥ�� �ٽ� ����

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
	//���� �׷��� �ϴ� ��ǥ�� �����ͼ� �� ��ǥ�� �����
	auto iter = m_difPosLst.begin();
	for (iter; iter != m_difPosLst.end(); ++iter)
	{
		COORD pos = (*iter);
		pos.X *= 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		cout << "  ";
	}

	//���� �׷��� �ϴ� ��ǥ�� ������Ʈ�� �ִٸ�
	//���� �׸���
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
	//���� �׷��� �ϴ� ��ǥ�� üũ�ؼ� ��򰡿� �־��
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
				//��ǥ�� ��򰡿� ����Ų��
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