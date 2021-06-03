#pragma once
#include "Character.h"

class Image;
class H_BountyHunter : public Character
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SetPos(int x) { this->pos.x = x; }

	H_BountyHunter()
	{
		uType = UnitType::HERO;

		stat.maxHp = 40;
		//stat.hp = stat.maxHp;
		stat.hp = 40;
		stat.atkSpeed = 100;
		stat.avd = 1; //회피율
		stat.defense = 1;
		stat.damage = { 8,16 }; //데미지 x <- low y <- high
		stat.acc = 5;; //명중률
		stat.stress = 0;
	}

	virtual ~H_BountyHunter() {};
};
