#pragma once
#include "GameNode.h"

class Image;
class FXmanager : public GameNode
{
private:
	float fxTime;
	Image* fxImage;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool fxdone();
};

