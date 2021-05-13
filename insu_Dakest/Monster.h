#pragma once
#include "GameNode.h"
class Image;

class Monster : public GameNode
{
public:
	enum MonsterKinds
	{
		SKELETON_ARBALISTAR,
		SKELETON_BEARER,
		SKELETON_CAPTAIN,
		SKELETON_COMMON,
		NONEKINDS
	};

protected:

	Image* img;
	POINT pos;
	State currstate;
	RECT body;
	MonsterKinds mkinds;

	int index;

	int currFrameX;
	int maxFrameX;
	int maxFrameArr[State::NONESTATE] = { 0 };

	float elapsed;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);


	void SetIndex(int i) { this->index = i; }
	int GetIndex() { return this->index; }

	virtual void SetPos(int x) { this->pos.x = x; };
	virtual int GetPosx() { return this->pos.x; }

	void IdleCombatUpdate();


	Monster() {
		pos.x = 0;
		pos.y = WINSIZE_Y / 3;
		img = nullptr;
		currstate = NONESTATE;
		mkinds = NONEKINDS;
		index = 0;
		SetRect(&body, pos.x - 50, pos.y - 50, pos.x + 50, pos.y + 50);
	
	};
	virtual ~Monster() {};

};

