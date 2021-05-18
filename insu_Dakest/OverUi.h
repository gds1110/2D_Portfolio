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

	int sIconCurrFrame;
	float eltimes;



	//tets
	int ePos;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~OverUi() {};
};

