#pragma once
#include "GameNode.h"

class Image;
class skill;
class Character : public GameNode
{
public:
	enum HCLASS
	{
		CRUSADER,
		BOUNTYHUNTER,
		HIGHWAYMAN,
		LEAPER,
		VESTEL,
		NONEHCLASS
	};

protected:
	struct Status
	{
		int hp;
		int atkSpeed;
		int avd; //회피율
		int defense;
		POINT damage; //데미지 x <- low y <- high
		int acc; //명중률
		int stress;
	};

protected:
	int CharArrPos[4] = { 540,390,240,40 };
	string classArr[5] = { "크루세이더 ","바운티헌터 ","노상강도 ","나병환자 ","성녀 " };
	Image* img;
	POINT pos;
	HCLASS hClass;
	State currstate;
	RECT body; 

	vector<skill*>skillslot;

	int currFrameX;
	int maxFrameX;
	int maxFrameArr[State::NONESTATE] = { 0 };

	float elapsed;
	int walkElapsed;
	
	int speed = 100;
	int index;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render2(HDC hdc);
	
	//Set pos
	virtual void SetPos(int x) { this->pos.x = x; };
	virtual int GetPosx() { return this->pos.x; }

	//H_Class
	virtual HCLASS GetClass() { return this->hClass; }; //{ return HCLASS::NONE; }
	string* GetClassArr() { return this->classArr; }
	
	//State
	virtual void SetCurrState(State state) { this->currstate = state; }

	//Rect
	virtual RECT GetRect() { return this->body; }

	//Index
	void SetIndex(int i) { this->index = i; }
	int GetIndex() { return this->index; }

	//Switch Sprite
	void switchSprite();

	//Dir KeyDown 
	void Move();

	//FrameRender Update : state :: combat or idle..
	void IdleCombatUpdate();

	//skillslot
	vector<skill*> GetSkillslot() {
		return this->skillslot;
	}

	Character();
	virtual ~Character() {};
};

