#pragma once
#include "GameNode.h"
#include <list>
class Image;
class ItemObject;
class Inventory:public GameNode
{
private:
	list<ItemObject> inventoryList;
	Image* img;
	POINT pos;
	bool isOpen;
	int index;
	RECT openButton;
	RECT closeButton;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	RECT getoPenRc() { return this->openButton; }
	RECT getcloseRC() { return this->closeButton; }


	void SetInventory(list<ItemObject> inven) { this->inventoryList = inven; }
	list<ItemObject> Getinventory() { return this->inventoryList; }
	void SetOpen(bool is) { this->isOpen = is; }
	bool GetOpen() { return this->isOpen; }

	void SetPos(POINT pos) { this->pos = pos; }

	void AddItem(ItemObject item);
	void Delete(ItemObject item);
};

