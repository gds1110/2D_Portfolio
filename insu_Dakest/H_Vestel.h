#pragma once
#include "Character.h"

class Image;
class H_Vestel : public Character
{
private:

public:
	H_Vestel()
	{
		uType = UnitType::HERO;

		stat.maxHp = 30;
		//stat.hp = stat.maxHp;
		stat.hp = 30;
		stat.atkSpeed = 4;
		stat.avd = 1; //회피율
		stat.defense = 1;
		stat.damage = { 3,10 }; //데미지 x <- low y <- high
		stat.acc = 5;; //명중률
		stat.stress = 0;
	};
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~H_Vestel() {};
};

