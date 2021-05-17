#pragma once
#include "GameNode.h"

class Image;
class SkillManager;
class Character : public GameNode
{
public:

protected:
	struct Status
	{
		int hp;
		int atkSpeed;
		int avd; //ȸ����
		int defense;
		POINT damage; //������ x <- low y <- high
		int acc; //���߷�
		int stress;
	};

protected:
	int CharArrPos[4] = { 540,390,240,40 };

	POINT pos;
	State currstate;
	RECT body; 
	UnitType uType;
	
	HCLASS hClass;
	MonsterKinds mkinds;
	SkillManager* S_MGR;
	string classArr[5] = { "ũ�缼�̴� ","�ٿ�Ƽ���� ","��󰭵� ","����ȯ�� ","���� " };

	//SelectCheck
	bool selected;
	bool target;

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

	//selected
	void SetSelected(bool sel) { this->selected = sel; }
	bool GetSelected() { return this->selected; }
	void SetTargeted(bool target) { this->target = target; }
	bool GetTargeted() { return this->target; }


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

	//Dir KeyDown 
	void Move();

	//FrameRender Update : state :: combat or idle..
	void IdleCombatUpdate();

	//skill
	SkillManager* getSkillMgr() { return this->S_MGR; }
	void skillSeting();

	Character();
	virtual ~Character() {};
};

