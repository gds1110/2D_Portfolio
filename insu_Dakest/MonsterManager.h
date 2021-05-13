#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Monster;
class MonsterManager : public GameNode
{
private:
	vector<Monster*> v_Monsetr;
	vector<Monster*>::iterator itMonster;
	int index;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	vector<Monster*> GetVMonsters() { return this->v_Monsetr; }

	void AddMonster(Monster* mon);

};

