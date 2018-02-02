#include "BaseEntity.h"
#include <conio.h>
#include <iostream>
#include "Game.h"
using namespace std;
BaseEntity::BaseEntity(int x, int y, std::string sym)
{
	m_pos.X = x;
	m_pos.Y = y;
	m_sym = sym;
}

void BaseEntity::PreRender()
{
	// 게임 인스턴스의 curMap에 자신이 그려진다고 체크
	Game::getInstance()->setNextMap(m_pos.X, m_pos.Y, TAG_NONE);
}

void BaseEntity::Render()
{
	COORD pos = m_pos;
	pos.X *= 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << m_sym;
}