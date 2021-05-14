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
	SkillState Skillstate;
	int slotNum;
	int index;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	RECT GetRect() { return this->iconRC; }
	void SetPos(int x) { this->pos.x = x; }
	POINT GetPos() { return this->pos; }

	void SetIndex(int index) { this->index = index; }
	Skill()
	{
		index = 0;
		pos.y = 530;
	}
	virtual ~Skill() {};
};

