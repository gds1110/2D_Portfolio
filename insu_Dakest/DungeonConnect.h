#pragma once
#include "GameNode.h"
class DungeonConnect :public GameNode
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

