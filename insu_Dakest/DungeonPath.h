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
class DungeonPath : public GameNode
{
private:
	Image* bgFirst;
	Image* bgSecond;
	Image* bgThird;
	Image* camBuffer;
	Tile* thisTile;
	DataManager* DM;
	CharacterManager* C_MGR;
	CharacterManager* M_MGR;
	DungeonUi* d_UI;
	//UnderUi* underUi;

	int CamPos;
	char szText[128] = "";

	bool battleState;
public:
	
	virtual HRESULT Init();
	virtual HRESULT DungeonPathInit(CharacterManager cmgr, Tile* flowTile, DUNGEONINFO info = { 0 });
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual HRESULT DungoenInit(Tile* flowTile);

	void FindFirstBg(DUNGEONINFO d_info);

	DungeonPath() {
		isDungeon = true;
	}


	virtual ~DungeonPath() {};
};

