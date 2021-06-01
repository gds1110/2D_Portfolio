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

		stat.maxHp = 40;
		//stat.hp = stat.maxHp;
		stat.hp = 40;
		stat.atkSpeed = 2;
		stat.avd = 1; //ȸ����
		stat.defense = 1;
		stat.damage = { 5,10 }; //������ x <- low y <- high
		stat.acc = 5;; //���߷�
		stat.stress = 0;
	}

	~skeleton_common() {};
};

