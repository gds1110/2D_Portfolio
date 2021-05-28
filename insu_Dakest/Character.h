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
		int avd; //È¸ÇÇÀ²
		int defense;
		POINT damage; //µ¥¹ÌÁö x <- low y <- high
		int acc; //¸íÁß·ü
		int stress;

		Status()
		{
			int maxHp = 30;
			int hp=maxHp;
			int atkSpeed = 5;
			int avd=1; //È¸ÇÇÀ²
			int defense=1;
			POINT damage = {5,10}; //µ¥¹ÌÁö x <- low y <- high
			int acc = 5;; //¸íÁß·ü
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
	string classArr[15] = { "Å©·ç¼¼ÀÌ´õ ","¹Ù¿îÆ¼ÇåÅÍ ","³ë»ó°­µµ ","³ªº´È¯ÀÚ ","¼º³à " };
	string MonArr[15] = { "½ºÄÌ·¹Åæ¾ÆÃ³ ","½ºÄÌ·¹Åæ±³±º ","½ºÄÌ·¹ÅæÄ¸Æ¾ ","½ºÄÌ·¹ÅæÄ¿¸Õ " };
	//SelectCheck
	bool selected;
	bool target;
	bool fixedTarget;

	//skill
	bool AbilOn;
	float AbilTime;

	float size;

	//UI
	Image* img;
	Image* targetIcon;
	Image* selecetedIcon;
	int sIconCurrFrame;
	float eltimes;
	float mTime;
	int alpha;
	
	//Frame
	int currFrameX;
	int maxFrameX;
	int maxFrameArr[State::NONESTATE] = { 0 };
	float elapsed;
	int walkElapsed;
	int speed = 100;
	int depth;

	//float size;
	
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
	void SetDepth(int d) { this->depth = d; }
	int GetDepth() { return this->depth; }

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

	void Hurt();

	Character();
	virtual ~Character() {};
};

