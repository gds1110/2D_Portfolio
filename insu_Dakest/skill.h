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
private:
	Image* iconImg;
	RECT iconRC;
	POINT pos;
	SkillState skillstate;

	HCLASS hClass;
	int skillNum;
	int slotNum;
	int index;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetHClass(HCLASS hclass) { this->hClass = hclass; }
	

	void SetskillNum(int num) { skillNum = num; }

	int getskillNum() { return skillNum; }

	SkillState GetSkillState() { return this->skillstate; }
	void SetSkillState(SkillState state) { this->skillstate = state; }

	RECT GetRect() { return this->iconRC; }
	void SetPos(int x) { this->pos.x = x; }
	POINT GetPos() { return this->pos; }

	void SetIndex(int index) { this->index = index; }
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

