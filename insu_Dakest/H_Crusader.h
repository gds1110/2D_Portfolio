#pragma once
#include "Character.h"

class Image;
class H_Crusader : public Character
{
private:


public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render2(HDC hdc);



	virtual ~H_Crusader() {};
};

