#pragma once
#include "Character.h"

class Image;

class H_Leaper : public Character
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~H_Leaper() {};
};

