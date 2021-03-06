#pragma once
#include "Character.h"

class skeleton_captain : public Character
{

private:

public:
	skeleton_captain()
	{
		uType = UnitType::MONSTER;

		stat.maxHp = 40;
		//stat.hp = stat.maxHp;
		stat.hp = 40;
		stat.atkSpeed = 1;
		stat.avd = 1; //회피율
		stat.defense = 1;
		stat.damage = { 3,7 }; //데미지 x <- low y <- high
		stat.acc = 5;; //명중률
		stat.stress = 0;
	};
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	~skeleton_captain() {};
};

