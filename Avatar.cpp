#include "Avatar.h"//
#include "Game.h"

Avatar::Avatar(int x, int y, string sym)
	: BaseEntity(x, y, sym) {}

void Avatar::PreRender()
{
	Game::getInstance()->setNextMap(m_pos.X, m_pos.Y, TAG_AVATAR);
}

void Avatar::Move(COORD pos)
{
	m_pos.X += pos.X;
	m_pos.Y += pos.Y;
}