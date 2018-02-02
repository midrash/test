#pragma once
#include "BaseEntity.h"
#include <string>
using namespace std;
class Avatar : public BaseEntity
{
public:
	Avatar(int x, int y, string sym);
	~Avatar() {}
	void PreRender() override;
	void Move(COORD pos);
private:
};