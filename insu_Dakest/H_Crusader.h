#pragma once
#include "Character.h"

class Image;
class H_Crusader : public Character
{
private:


public:
	H_Crusader()
	{
		uType = UnitType::HERO;

		 stat.maxHp = 50;
		 //stat.hp = stat.maxHp;
		 stat.hp = 50;
		 stat.atkSpeed = 1;
		 stat.avd = 1; //ȸ����
		 stat.defense = 1;
		 stat.damage = { 5,10 }; //������ x <- low y <- high
		 stat.acc = 5;; //���߷�
		 stat.stress = 0;
	}
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);



	virtual ~H_Crusader() {};
};

