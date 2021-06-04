#pragma once
#include "GameNode.h"

class Image;
class ItemObject : public GameNode
{
public:
	enum ITEMTYPE
	{
		DECODING,
		BANDAGE,
		TORCH
	};
private:
	Image* itemimg;
	POINT pos;
	RECT rc;
	ITEMTYPE itemtype;
	POINT num = { 0,8 }; //x 현재수량 y 최대수량
	int index;
	char szText[128] = "";

public:
	virtual HRESULT Init();
	virtual HRESULT Init(ITEMTYPE itemtype);

	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	
	void setIndex(int a) { this->index = a; }
	int GetIndex() { return this->index; }

	RECT GetRC() { return this->rc; }

	void SetItemNum(int x) {
		num.x = x;
	}
	POINT GetItemNum() { return this->num; }

	void Run() {};
	ITEMTYPE GetType() { return this->itemtype; }
	void SetPos(POINT pos) { this->pos = pos; }
	POINT GetPos() { return this->pos; }

};

