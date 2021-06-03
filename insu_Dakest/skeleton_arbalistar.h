#pragma once
#include "Character.h"
class Image;
class skeleton_arbalistar : public Character
{

private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	skeleton_arbalistar()
	{
		uType = UnitType::MONSTER;


		stat.maxHp = 40;
		//stat.hp = stat.maxHp;
		stat.hp = 40;
		stat.atkSpeed = 2;
		stat.avd = 1; //ȸ����
		stat.defense = 1;
		stat.damage = { 4,6 }; //������ x <- low y <- high
		stat.acc = 5;; //���߷�
		stat.stress = 0;
	}



	~skeleton_arbalistar() {};
};

