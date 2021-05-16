#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Monster;
class Character;
class MonsterManager : public GameNode
{
private:
	/*vector<Monster*> v_Monsetr;
	vector<Monster*>::iterator itMonster;*/
	vector<Character*> v_Monsetr;
	vector<Character*>::iterator itMonster;
	int index;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	//vector<Monster*> GetVMonsters() { return this->v_Monsetr; }
	vector<Character*> GetVMonsters() { return this->v_Monsetr; }

	void AddMonster(Character* mon);
	//void AddMonster(Monster* mon);

};

