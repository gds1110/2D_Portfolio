#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Character;
class CharacterManager : public GameNode
{
private:
	vector<Character*> v_Characters;
	vector<Character*>::iterator itChr;
	
	int index;
	int CharArrPos[4] = { 640,440,240,40 };
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual HRESULT Init(int num);


	vector<Character*> GetCharacters() { return this->v_Characters; }

	void AddCharacter(Character* chr, UnitType type= UnitType::HERO);
	void AddCharacter2(Character* chr, int indexx, bool isroster = false, UnitType type = UnitType::HERO);
	//void AddCharacter(UnitType type,int CharIndex);
	void AddMonster(int charIndex);
	int GetCharPos();
	
	virtual ~CharacterManager() {};

};

