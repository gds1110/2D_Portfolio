#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Character;
class CharacterManager : public GameNode
{
private:
	vector<Character*> v_Heros;
	vector<Character*>::iterator itHero;
	int index;
	int CharArrPos[4] = { 640,440,240,40 };
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual HRESULT Init(int num);

	vector<Character*> GetVHeros() { return this->v_Heros; }

	void AddHero(Character* chr);
	int GetHeroPos();

	virtual ~CharacterManager() {};

};

