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
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual HRESULT Init(int num);

	void AddHero(Character* chr);

	virtual ~CharacterManager() {};

};

