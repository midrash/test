#include "Block.h"
#include "Game.h"
#include "global.h"
Block::Block(int x, int y, std::string sym) 
	: BaseEntity(x, y, sym){}

void Block::PreRender()
{
	Game::getInstance()->setNextMap(m_pos.X, m_pos.Y, TAG_BLOCK);
}