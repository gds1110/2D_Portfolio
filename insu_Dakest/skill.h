#pragma once
#include "GameNode.h"


class Image;
class Character;
class Skill :public GameNode
{
public:
	
	enum SkillState
	{
		ON,
		OFF,
		SkillNONE
	};


protected:


	Image* iconImg;
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



public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SkillInit();

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
	//CombatAttack() {
	//	s_info.skillRank = { 0,1 };
	//	s_info.targetRank = { 0,1 };
	//	s_info.range = 1;
	//}
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
	//{
	//	//if(hClass==)
	//	//for (int i = 0; i < UiDataManager::GetSingleton()->GetTarGet().size(); i++) {
	//	//	//UiDataManager::GetSingleton()->GetTarGet()[i].setHp(gethp - 1);
	//	//}
	//	//
	//}

};

class ChargeAttack : public  Skill {
private:

public:
	ChargeAttack() {
		s_info.skillRank = { 2,3 };
		s_info.targetRank = { 2,3 };
		s_info.range = 2;
	}

	void run(int x, Character* target) {
		//if(hClass==)
		//for (int i = 0; i < UiDataManager::GetSingleton()->GetTarGet().size(); i++) {
		//	//UiDataManager::GetSingleton()->GetTarGet()[i].setHp(gethp - 1);
		//}
		//
	}

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