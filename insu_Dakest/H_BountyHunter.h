#pragma once
#include "Character.h"

class Image;
class H_BountyHunter : public Character
{
private:
	Image* img;
	POINT pos;
	int currFrameX;
	int maxFrameX;
	float elapsed;
	int walkElapsed;
	State currstate;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SetPos(int x) { this->pos.x = x; }
	virtual int GetPosx() { return this->pos.x; }

	void Move();


	void SetCurrState(State state) { this->currstate = state; }

	virtual ~H_BountyHunter() {};
};
