#pragma once
#include "Character.h"

class Image;
class H_Crusader : public Character
{
private:
	int currFrameX;
	int maxFrameX;
	float elapsed;
	int walkElapsed;
	State currstate;
	//HCLASS hClass;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render2(HDC hdc);
	virtual void SetPos(int x) { this->pos.x = x; }
	virtual int GetPosx() { return this->pos.x; }
	virtual void SetState(State state) { this->currstate = state; }
	//virtual HCLASS GetClass() { return this->hClass; };
	void Move();


	//virtual void SetCurrState(State state) { this->currstate = state; }

	virtual ~H_Crusader() {};
};

