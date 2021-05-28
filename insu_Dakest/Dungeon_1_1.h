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
class Dungeon_1_1 : public GameNode
{
	enum DungeonType
	{
		START,
		PATH,
		ROOM,
		END,
	};
private:
	Image* Ip_Bg_First;
	Image* Ip_Bg_Second;
	Image* Ip_BG_Passage;
	UnderUi* underUI;
	OverUi* overUi;
	DungeonType D_TYPE;

	Image* CamBuffer;
	DataManager* DM;
	int battlePos[4];
	char szText[128] = "";
	bool BattleStage;
	float test = 0.0f;
	int CamPos;
	CharacterManager* C_MGR;
	CharacterManager* M_MGR;
	Tile* thisTile;
	bool Enemy;

public:
	virtual HRESULT Init();
	virtual HRESULT DungoenInit(Tile* flowTile);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Dungeon_1_1() {
		isDungeon = true;
	}
	

	virtual ~Dungeon_1_1() {};
};

