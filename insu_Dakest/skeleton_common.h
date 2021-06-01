#pragma once
#include "Character.h"

class skeleton_common : public Character
{

private:


public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	

	skeleton_common()
	{
		uType = UnitType::MONSTER;

		stat.maxHp = 30;
		//stat.hp = stat.maxHp;
		stat.hp = 30;
		stat.atkSpeed = 2;
		stat.avd = 1; //ȸ����
		stat.defense = 1;
		stat.damage = { 2,5 }; //������ x <- low y <- high
		stat.acc = 5;; //���߷�
		stat.stress = 0;
	}

	~skeleton_common() {};
};

