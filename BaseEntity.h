#pragma once
#include <Windows.h>
#include <string>

class BaseEntity
{
public:
	BaseEntity(int x, int y, std::string sym);
	virtual ~BaseEntity() {}
	virtual void PreRender();
	virtual void Render();
	COORD getPos() { return m_pos; }
	void setPos(COORD pos) { m_pos = pos; }
protected:
	COORD m_pos;
	std::string m_sym;
};
