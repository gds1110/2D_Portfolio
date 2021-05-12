#pragma once
#include "GameNode.h"

class Image;
class Character : public GameNode
{
public:
	enum State
	{
		IDLE,
		WALK,
		COMBAT,
		NONESTATE
	};

	enum HCLASS
	{
		CRUSADER,
		BOUNTYHUNTER,
		NONECLASS
	};

protected:

	Image* img;
	POINT pos;
	HCLASS hClass;
	State currstate;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render2(HDC hdc);
	
	virtual void SetPos(int num) {};
	virtual int GetPosx() { return 0; };
	
	virtual HCLASS GetClass() { return this->hClass; }; //{ return HCLASS::NONE; }

	virtual void SetCurrState(State state) { this->currstate = state; }

	virtual void SetState(State state) {};
	
	virtual ~Character() {};
};

