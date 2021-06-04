#pragma once
#include "GameNode.h"


class Image;
class Character;
class Skill :public GameNode
{
public:
	
	enum skillstrength
	{
		CANT,
		PLAYERPOS,
		ENEMYPOS,
		HEALORMOVE
	};

	struct  skilltooltips
	{
		bool player;
		bool canskill;
		bool canhit;
		Image* img;
		skillstrength ss=CANT;
		POINT pos;
		skilltooltips()
		{
			img = ImageManager::GetSingleton()->FindImage("스킬위치");
			ss = CANT;
		}

	};

	enum SkillState
	{
		ON,
		OFF,
		SkillNONE
	};


protected:


	Image* iconImg;
	Image* tooltip;
	RECT iconRC;
	POINT pos;
	SkillState skillstate;
	Character* owner;
	SKILLTYPE type;

	HCLASS hClass;
	MonsterKinds mkinds;
	int skillNum;
	int slotNum;
	int index;
	skillInfo s_info;
	skilltooltips tipsinfo[8];
	bool isMouseOver;
	char szText[128] = "";



public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SkillInit();

	void SetMouseOver(bool isover) { isMouseOver = isover; }
	bool GetMouseOver() { return this->isMouseOver; }

	void SkillPosState();

	void SetHClass(HCLASS hclass) { this->hClass = hclass; }
	
	void SetOwner(Character* owner) { this->owner = owner; }

	void SetskillNum(int num) { skillNum = num; }
	int GetskillNum() { return skillNum; }

	void SetSkillType(SKILLTYPE type) { this->type = type; }
	SKILLTYPE GetSkillType() { return this->type; }


	SkillState GetSkillState() { return this->skillstate; }
	void SetSkillState(SkillState state) { this->skillstate = state; }

	RECT GetRect() { return this->iconRC; }
	
	void SetPos(int x) { this->pos.x = x; }
	POINT GetPos() { return this->pos; }

	skillInfo GetSkillInfo() { return this->s_info; }

	void SetIndex(int index) { this->index = index; }
	virtual void run(int x, Character* target);
	virtual void MotionRun();
	virtual void justRun() {};

	Skill();
	Skill(Character* owner);
	virtual ~Skill() {};
};

class CombatAttack : public  Skill {
private:

public:

	CombatAttack();
	CombatAttack(Character* owner);
	void run();
	
	
	virtual void run(int x, Character* target);

};

class ArangeAttack : public  Skill {
private:

public:
	ArangeAttack(Character* owner);

	void run(int x, Character* target);

};

class ChargeAttack : public  Skill {
private:

public:
	ChargeAttack(Character* owner);
	

	void run(int x, Character* target);

};
class StunSkill :public Skill
{
private:

public:
	StunSkill(Character* owner);

	virtual void run(int x, Character* target);

};
class SwapSkill : public Skill {
private:

public:
	SwapSkill(Character* owner);
	virtual void run(int x, Character* target);
	virtual void justRun()
	{
		return;
	}
};
class HealSkill :public Skill {
private:

public:
	HealSkill(Character* owner);

	virtual void run(int x, Character* target);

};

class NoTurn : public Skill {
private:

public:
	virtual void justRun()
	{
		return;
	}

};