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
			float maxHp = 30;
			float hp=maxHp;
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
	string MonArr[15] = { "스켈레톤아처 ","스켈레톤교군 ","스켈레톤캡틴 ","스켈레톤커먼 " };
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
	Image* hpBar;
	Image* hpBarBG;
	int sIconCurrFrame;
	float eltimes;
	float mTime;
	int alpha;
	
	Image* rosterIcon;
	Image* rosterBg;

	//Frame
	int currFrameX;
	int maxFrameX;
	int maxFrameArr[State::NONESTATE] = { 0 };
	float elapsed;
	int walkElapsed;
	int speed = 100;
	int depth;
	int dice;
	//float size;
	
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
	/// 영웅은 커맨드 패턴으로 제작
	/// 몬스터는 그냥 제작.
	virtual void Attack(Character* target);

	Character();
	virtual ~Character() {};
};

