#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Character;
class CharacterManager : public GameNode
{
private:
	vector<Character*> v_Characters;
	vector<Character*>::iterator itHero;

	int index;
	int CharArrPos[4] = { 640,440,240,40 };
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual HRESULT Init(int num);


	vector<Character*> GetCharacters() { return this->v_Characters; }

	void AddCharacter(Character* chr, UnitType type);

	int GetCharPos();
	
	virtual ~CharacterManager() {};

};

