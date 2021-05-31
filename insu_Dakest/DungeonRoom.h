#pragma once
#include "GameNode.h"

class UI;
class OverUi;
class UnderUi;
class Image;
class Character;
class CharacterManager;
class SkillManager;
class DataManager;
class MapGenManager;
class DungeonUi;
class DungeonRoom : public GameNode
{
private:
	Image* bgFirst;

	Image* camBuffer;
	Tile* thisTile;
	DataManager* DM;
	CharacterManager* C_MGR;
	CharacterManager* M_MGR;
	DungeonUi* d_UI;
	//UnderUi* underUi;
	int CamPos;
	char szText[128] = "";

public:

	virtual HRESULT Init();
	virtual HRESULT DungoenInit(Tile* flowTile);
	virtual HRESULT DungeonRoomInit(CharacterManager cmgr, Tile* flowTile, DUNGEONINFO info = { 0 });
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void FindFirstBg(DUNGEONINFO d_info);

	DungeonRoom() {
		isDungeon = true;
	}


	virtual ~DungeonRoom() {};
};

