#pragma once
#include "GameNode.h"
#include "Character.h"
#include <algorithm>

class UI;
class OverUi;
class UnderUi;
class Image;
class Character;
class CharacterManager;
class SkillManager;
class DataManager;
class MapGenManager;
//using dices = pair<Character*, int>;

class Dungeon_1_1 : public GameNode
{



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
	//static bool compare(const dices &a,const dices &b)
	//{
	//	if (a.second == b.second)
	//	{
	//		return a.first->GetStat().atkSpeed < b.first->GetStat().atkSpeed;
	//	}
	//	else {
	//		return a.second < b.second;
	//	}

	//	return false;
	//}
	Dungeon_1_1() {
		isDungeon = true;
	}
	

	virtual ~Dungeon_1_1() {};
};

