#pragma once
#include "GameNode.h"

class Character;
class CharacterManager;
class DataManager;
class MapGenManager;
class DungeonConnect :public GameNode
{
private:

public:
	virtual HRESULT Init();
	virtual HRESULT Init(DUNGEONINFO info);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

