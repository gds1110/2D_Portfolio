#pragma once
#include "Monster.h"
class Image;
class skeleton_arbalistar : public Monster
{

private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	~skeleton_arbalistar() {};
};

