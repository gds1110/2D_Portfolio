#pragma once
#include "Character.h"

class Image;
class H_BountyHunter : public Character
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SetPos(int x) { this->pos.x = x; }


	virtual ~H_BountyHunter() {};
};
