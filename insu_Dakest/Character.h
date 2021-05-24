#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class SkillManager;
class Character : public GameNode
{
public:

protected:
	struct Status
	{
		int maxHp;
		int hp;
		int atkSpeed;
		int avd; //회피율
		int defense;
		POINT damage; //데미지 x <- low y <- high
		int acc; //명중률
		int stress;

		Status()
		{
			int maxHp = 30;
			int hp=maxHp;
			int atkSpeed = 5;
			int avd=1; //회피율
			int defense=1;
			POINT damage = {5,10}; //데미지 x <- low y <- high
			int acc = 5;; //명중률
			int stress=0;
		}
	};

protected:
	int CharArrPos[4] = { 540,390,240,90 };
	int MonArrPos[4] = { 740,890,1040,1190 };
	Status stat;


	POINT pos;
	State currstate;
	RECT body; 
	UnitType uType;
	
	HCLASS hClass;
	MonsterKinds mkinds;
	SkillManager* S_MGR;
	string classArr[15] = { "크루세이더 ","바운티헌터 ","노상강도 ","나병환자 ","성녀 " };
	string MonArr[15] = { "스켈레톤아처 " };
	//SelectCheck
	bool selected;
	bool target;
	bool fixedTarget;

	//skill
	bool AbilOn;
	float AbilTime;

	//UI
	Image* img;
	Image* targetIcon;
	Image* selecetedIcon;
	int sIconCurrFrame;
	float eltimes;
	int alpha;
	
	//Frame
	int currFrameX;
	int maxFrameX;
	int maxFrameArr[State::NONESTATE] = { 0 };
	float elapsed;
	int walkElapsed;
	int speed = 100;
	int depth;

	float size;
	
	//INDEX
	int index;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render2(HDC hdc);

	//Render
	void ShareRender(HDC hdc);
	void SetAlpha(int alpha) { this->alpha = alpha; }
	int GetAlpha() { return this->alpha; }


	//selected
	void SetSelected(bool sel) { this->selected = sel; }
	bool GetSelected() { return this->selected; }
	void SetTargeted(bool target) { this->target = target; }
	bool GetTargeted() { return this->target; }
	void SetFixed(bool fix) { this->fixedTarget = fix; }
	bool GetFixed() { return this->fixedTarget; }


	//HeroUpdate
	void HUpdate();
	//MonsterUpdate
	void MUpdate();

	//type
	void SetType(UnitType uType) { this->uType = uType; }
	

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

	void SharedUpdate();

	//Index
	void SetIndex(int i) { this->index = i; }
	int GetIndex() { return this->index; }

	//Switch Sprite
	void switchSprite();
	void MswitchSprite();
	//Dir KeyDown 
	void Move();

	//FrameRender Update : state :: combat or idle..
	void IdleCombatUpdate();

	//skill
	SkillManager* getSkillMgr() { return this->S_MGR; }
	void skillSeting();
	void abliiltyUpdate();

	Character();
	virtual ~Character() {};
};

