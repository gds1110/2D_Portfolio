#pragma once
#include "Character.h"

class Image;
class H_Vestel : public Character
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~H_Vestel() {};
};

