#pragma once
#include "GameNode.h"

class Image;
class skill :public GameNode
{
public:
	enum skillState
	{
		ON,
		OFF,
		SKILLNONE
	};
private:
	Image* iconImg;
	RECT iconRC;
	POINT pos;
	skillState skillstate;
	int slotNum;
	

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void setPos(int x) { this->pos.x = x; }
	skill()
	{
		pos.y = 570;
	}
	virtual ~skill() {};
};

