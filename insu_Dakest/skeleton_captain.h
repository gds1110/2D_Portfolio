#pragma once
#include "Character.h"

class skeleton_captain : public Character
{

private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	~skeleton_captain() {};
};

