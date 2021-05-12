#pragma once
#include "UI.h"

class Image;
class UnderUi :public UI
{
private:
	Image* underUi;
	Image* underIcon;

	
	string iconKey;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~UnderUi() {};

};

