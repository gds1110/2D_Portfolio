#pragma once
#include "GameNode.h"
#include <vector>

class Skill;
class SkillManager : public GameNode
{
private:
	vector<Skill*>skillSlot;

	int index;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void AddSkill(Skill* skill);
	vector<Skill*> GetSkillSlot() { return this->skillSlot; }
	
};

