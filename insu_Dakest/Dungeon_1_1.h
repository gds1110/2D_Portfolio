#pragma once
#include "GameNode.h"

class Image;
class Character;
class CharacterManager;
class Dungeon_1_1 : public GameNode
{
private:
	Image* Ip_Bg_First;
	Image* Ip_Bg_Second;
	Image* Ip_BG_Passage;


	int CamPos;
	CharacterManager* C_MGR;
	Character* ptr_Hero1;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~Dungeon_1_1() {};
};

