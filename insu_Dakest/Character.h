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
		int avd; //ȸ����
		int defense;
		POINT damage; //������ x <- low y <- high
		int acc; //���߷�
		int stress;

		Status()
		{
			float maxHp = 30;
			float hp=maxHp;
			int atkSpeed = 5;
			int avd=1; //ȸ����
			int defense=1;
			POINT damage = {5,10}; //������ x <- low y <- high
			int acc = 5;; //���߷�
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
	string classArr[15] = { "ũ�缼�̴� ","�ٿ�Ƽ���� ","��󰭵� ","����ȯ�� ","���� " };
	string MonArr[15] = { "���̷����ó ","���̷��汳�� ","���̷���ĸƾ ","���̷���Ŀ�� " };
	//SelectCheck
	bool selected;

	bool target;
	bool fixedTarget;

	bool htarget;
	bool hfixedTarget;

	//skill
	bool AbilOn;
	float AbilTime;

	float size;

	//UI
	Image* img;
	Image* targetIcon;
	Image* htargetIcon;
	Image* selecetedIcon;
	Image* hpBar;
	Image* hpBarBG;
	int sIconCurrFrame;
	float eltimes;
	float mTime;
	int alpha;
	
	Image* rosterIcon;
	Image* rosterBg;
	Image* haveturnimg;
	Image* stunImage;
	Image* markImage;
	//Frame
	int currFrameX;
	int maxFrameX;
	int maxFrameArr[State::NONESTATE] = { 0 };
	float elapsed;
	float Mtime=0.0f;

	int walkElapsed;
	int speed = 100;
	int depth;
	int dice;
	//float size;
	
	bool stun;
	bool mark;
	//INDEX
	bool battleState = false;
	bool haveTurn;

	int index;
	bool iconIsSeleceted;
	bool iconMouseOver;
	RECT iconRC;
	POINT iconPos;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render2(HDC hdc);

	virtual HRESULT RosterInit();
	virtual void RosterRelease();
	virtual void RosterUpdate();
	virtual void RosterRender(HDC hdc);

	virtual HRESULT PartyInit();
	virtual void PartyRelease();
	virtual void PartyUpdate();
	virtual void PartyRender(HDC hdc);

	void SetHp(int x) { this->stat.hp = x; }

	void setStun(bool stun) { this->stun = stun; }
	bool GetStun() { return this->stun; }
	void setMark(bool mark) { this->mark = mark; }
	bool GetMark() { return this->mark; }

	virtual Character* GetThis() { return this; }

	bool GetHaveTurn() { return this->haveTurn; }
	void SetHaveTurn(bool turn) { this->haveTurn = turn; }


	UnitType GetUnitType() { return this->uType; }

	bool GetBattleState() { return this->battleState; }
	void SetBattleState(bool bat) { this->battleState = bat; }

	void SetIconIsSelecetd(bool issel)	{this->iconIsSeleceted = issel;}
	bool GetIconIsSelecetd(){return this->iconIsSeleceted;}
	Image* GetIconImage(){return this->rosterIcon;}

	void SetIconMouseOver(bool over){this->iconMouseOver = over;}
	bool GetIconMouseOver(){return this->iconMouseOver;}
	
	POINT GetIconPOS() { return this->iconPos; }
	void SetIconPos(POINT pos) { this->iconPos = pos; }

	RECT GetIconRC() { return this->iconRC; }
	//void SetIconRc(RECT RC) { this->iconRC = RC; }

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

	void SetHTargeted(bool target) { this->htarget = target; }
	bool GetHTargeted() { return this->htarget; }
	void SetHFixed(bool fix) { this->hfixedTarget = fix; }
	bool GetHFixed() { return this->hfixedTarget; }


	//HeroUpdate
	void HUpdate();
	//MonsterUpdate
	void MUpdate();

	//type
	void SetType(UnitType uType) { this->uType = uType; }
	

	//Set pos
	virtual void SetPos(int x) { this->pos.x = x; };
	virtual int GetPosx() { return this->pos.x; }

	virtual void SetPosY(int y) { this->pos.y = y; };
	virtual int GetPosY() { return this->pos.y; }


	//H_Class
	virtual HCLASS GetClass() { return this->hClass; }; //{ return HCLASS::NONE; }
	string* GetClassArr() { return this->classArr; }
	
	//State
	virtual void SetCurrState(State state) { this->currstate = state; }
	State GetCurrState() { return this->currstate; }

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

	Status GetStat() { return this->stat; }

	//skill
	SkillManager* getSkillMgr() { return this->S_MGR; }
	void skillSeting();
	void abliiltyUpdate();

	void Hurt();
	void Hurt(int x);


	virtual int Dice();
	/// ������ Ŀ�ǵ� �������� ����
	/// ���ʹ� �׳� ����.
	virtual void Attack(Character* target);

	Character();
	virtual ~Character() {};
};

