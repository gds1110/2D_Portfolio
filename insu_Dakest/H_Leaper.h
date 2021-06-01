#pragma once
#include "Character.h"

class Image;

class H_Leaper : public Character
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	H_Leaper()
	{

		stat.maxHp = 40;
		//stat.hp = stat.maxHp;
		stat.hp = 40;
		stat.atkSpeed = 2;
		stat.avd = 1; //회피율
		stat.defense = 1;
		stat.damage = { 5,10 }; //데미지 x <- low y <- high
		stat.acc = 5;; //명중률
		stat.stress = 0;
	}

	virtual ~H_Leaper() {};
};

