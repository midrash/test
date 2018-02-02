#pragma once
#include <Windows.h>
#include <string>
#include "BaseEntity.h"
class Block : public BaseEntity
{
public:
	Block(int x, int y, std::string sym);
	void PreRender() override;
};
