#pragma once
#include "GameNode.h"

class CharacterManager;
class Image;
class Character;
class Inventory;
class ItemObject;
class Home : public GameNode
{

	struct HeroSlot
	{
		RECT rc;
		int size;
		POINT pos;
		int HeroNum;
		bool isSetting;
		Image* icon;
		Character* hero;
	};

private:
	ItemObject* item1;
	ItemObject* item2;
	ItemObject* item3;


	Image* bg;
	CharacterManager* rosterList;
	Image* mouseIcon;
	RECT divideRc;
	HeroSlot heroSlot[4];
	char szText[128] = "";
	int selectNum;
	int heroArr[4];
	int buttonframe;
	bool ready;
	Image* startButton;
	RECT startRC;
	
	Inventory* myInven;
public:

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

