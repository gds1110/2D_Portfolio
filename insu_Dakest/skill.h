#pragma once
#include "GameNode.h"

class Image;
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
	struct skillInfo
	{

		POINT skillRank;
		POINT targetRank;
		int range;
	};

	Image* iconImg;
	RECT iconRC;
	POINT pos;
	SkillState skillstate;



	HCLASS hClass;
	int skillNum;
	int slotNum;
	int index;
	skillInfo s_info;



public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetHClass(HCLASS hclass) { this->hClass = hclass; }
	

	void SetskillNum(int num) { skillNum = num; }
	int GetskillNum() { return skillNum; }

	SkillState GetSkillState() { return this->skillstate; }
	void SetSkillState(SkillState state) { this->skillstate = state; }

	RECT GetRect() { return this->iconRC; }
	
	void SetPos(int x) { this->pos.x = x; }
	POINT GetPos() { return this->pos; }

	skillInfo GetSkillInfo() { return this->s_info; }

	void SetIndex(int index) { this->index = index; }
	virtual void run(int x, Character* target) {};
	void Run() {};

	Skill()
	{
		skillstate = SkillState::ON;
		slotNum = 0;
		skillNum = 0;
		index = 0;
		pos.y = 530;
	}
	virtual ~Skill() {};
};

class CombatAttack : public  Skill {
private:

public:
	CombatAttack() {
		s_info.skillRank = { 0,1 };
		s_info.targetRank = { 0,1 };
		s_info.range = 1;
	}

	void run(int x, Character* target) {
		//for (int i = 0; i < UiDataManager::GetSingleton()->GetTarGet().size(); i++) {
		//	//UiDataManager::GetSingleton()->GetTarGet()[i].setHp(gethp - 1);
		//}
		//
	}

};

class ArangeAttack : public  Skill {
private:

public:
	ArangeAttack() {
		s_info.skillRank = { 0,1 };
		s_info.targetRank = { 1,3 };
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