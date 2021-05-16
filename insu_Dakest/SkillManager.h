#pragma once
#include "GameNode.h"
#include <vector>

class Skill;
class SkillManager : public GameNode
{
private:
	vector<Skill*>skillSlot;

	int index;
	HCLASS hclass;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void AddSkill(Skill* skill);
	void AddSkill(HCLASS hclass, int skillNum, int index);
	vector<Skill*> GetSkillSlot() { return this->skillSlot; }
	
	void SetHClass(HCLASS hclass) { this->hclass = hclass; }
	HCLASS GetHClass() { return this->hclass; }
};

