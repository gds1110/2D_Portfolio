#pragma once
#include "UI.h"

//class Image;
class OverUi:public UI
{
private:
	Image* selecetedIcon;
	Image* targetIcon;
	Image* torchFireUI;
	Image* flame;
	Image* BattleStart;

	bool battle = false;

	int sIconCurrFrame;
	float eltimes;

	int combatCurrFrame;
	float combattimer;

	//tets
	int ePos;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetBattle(bool battle) { this->battle = battle; }
	bool GetBattle() { return this->battle; }

	virtual ~OverUi() {};
};

