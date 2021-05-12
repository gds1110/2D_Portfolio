#pragma once
#include "UI.h"

//class Image;
class OverUi:public UI
{
private:
	Image* selecetedIcon;
	int sIconCurrFrame;
	float eltimes;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~OverUi() {};
};

