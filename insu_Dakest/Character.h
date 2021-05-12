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
		ATTACK1,
		NONESTATE
	};

	enum HCLASS
	{
		CRUSADER,
		BOUNTYHUNTER,
		NONECLASS
	};

protected:
	string classArr[3] = { "农风技捞歹 ","官款萍清磐 ","00" };
	Image* img;
	POINT pos;
	HCLASS hClass;
	State currstate;
	RECT body; 
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render2(HDC hdc);
	
	virtual void SetPos(int num) {};
	virtual int GetPosx() { return 0; };
	
	virtual HCLASS GetClass() { return this->hClass; }; //{ return HCLASS::NONE; }
	
	string* GetClassArr() { return this->classArr; }
	 
	virtual void SetCurrState(State state) { this->currstate = state; }

	virtual void SetState(State state) {};
	
	virtual RECT GetRect() { return this->body; }

	Character() {
		img = nullptr;
		pos = { 0,0 };
		hClass = NONECLASS;
		currstate = NONESTATE;
		SetRect(&body, pos.x - 50, pos.y - 50, pos.x + 50, pos.y + 50); };
	virtual ~Character() {};
};

