#pragma once
#include "GameNode.h"
#include <vector>

class Skill;
class Character;
class SkillManager : public GameNode
{
private:
	vector<Skill*>skillSlot;

	int skillPos[6];
	int index;
	HCLASS hclass;
	MonsterKinds mkinds;
	Character* owner;
public:
	virtual HRESULT Init();
	virtual HRESULT Init(Character* owner);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);


	void AddSkill(Skill* skill);
	void AddSkill2(Skill* skill, int skillNum=0, int index=0);
	void AddSkill3(SKILLTYPE type, int skillNum=0, int index=0);
	vector<Skill*> GetSkillSlot() { return this->skillSlot; }
	
	void SetHClass(HCLASS hclass) { this->hclass = hclass; }
	HCLASS GetHClass() { return this->hclass; }

	void SetKinds(MonsterKinds kinds) { this->mkinds = kinds; }
	MonsterKinds GetMkinds() { return this->mkinds; }
};

