#pragma once
#include "config.h"
#include "Singleton.h"
#include <string>
#include <vector>
#include "config.h"

class MapGenManager;
class Character;
class Skill;
class SkillManager;
class CharacterManager;
class Image;
class Tile;
class UiDataManager : public Singleton<UiDataManager>
{
public: enum SceneInfo
{
	MAPGEN,
	PATH,
	ROOM,
	TOWN,
	NONESCENE,
	};

private:
	Character* selectedChr;
	vector<Tile*> minmap;
	vector<Character*> targetChr;
	bool selCheck;
	Skill* selctedSkill;
	string* arrClass;
	SkillManager* SS_MGR;
	CharacterManager* SC_MGR;
	CharacterManager* SM_MGR;
	SceneInfo prevScene;
	SceneInfo selScene;
	Image* RenderMinimap;
	Image* Minimap;
	POINT minIndex = { 99,99 };
	POINT maxIndex = { -1,-1 };
	HDC mapHdc;

	MapGenManager* MapGen;
	bool isBattleState;
	int campos;
	Tile** map;
	Tile* currtile;
	Tile* destTile;

	bool turnexitCheck = false;	

	SceneInfo currScene;
public:
	HRESULT Init();
	void Release();
	void Update();

	void SetTurnExit(bool set) { turnexitCheck = set; }
	bool GetTurnExit() { return this->turnexitCheck; }
	
	void SetCurrScene(SceneInfo scene) { this->currScene = scene; }
	SceneInfo GetCurrScene() { return this->currScene; }

	int GetCampos() { return this->campos; }
	void SetCampos(int a) { this->campos = a; }

	void SetBattleState(bool is) { this->isBattleState = is; }
	bool GetBattleState() { return this->isBattleState; }

	void SetDestTile(Tile* tile) { this->destTile = tile; }
	Tile* GetDestTile() { return this->destTile; }

	
	SceneInfo GetPrevScene() { return this->prevScene; }

	void SetCurrtile(Tile* tile) { this->currtile = tile; }
	Tile* GetTile() { return this->currtile; }

	void SetSceneInfo(SceneInfo prevScene, SceneInfo selScene) {
		this->prevScene = prevScene;
		this->selScene = selScene;
	}
	MapGenManager* GetMapGen() { return this->MapGen; }
	void SetMapGeN(MapGenManager* map) { this->MapGen = map; }

	void SetHdc(HDC hdc) { this->mapHdc = hdc; }
	HDC GetHdc() { return this->mapHdc; }

	void SetMin(POINT min) { this->minIndex = min; }
	void SetMax(POINT max) { this->maxIndex = max; }

	POINT GetMin() { return this->minIndex; }
	POINT GetMax() { return this->maxIndex; }

	void selectSkill(Skill* select) { this->selctedSkill = select; }
	void SelectChar(Character* select) { this->selectedChr = select; }

	void SetSS_MGR(SkillManager* s_mgr) { this->SS_MGR = s_mgr; }
	void SetSC_MGR(CharacterManager* c_mgr) { this->SC_MGR = c_mgr; }
	void SetSM_MGR(CharacterManager* m_mgr) { this->SM_MGR = m_mgr; }

	void SetselCheck(bool check) { this->selCheck = check; }
	bool GetselCheck() { return this->selCheck; }

	void SetMapimg(Image* image) { this->Minimap = image; }
	Image* GetMapimg() { return this->Minimap; }

	void SetMiniMap(vector<Tile*>  map) { this->minmap = map; }
	vector<Tile*>  GetMiniMap() { return this->minmap; }

	Character* GetSelectedChar() { if (selectedChr) { return this->selectedChr; } }
	Skill* GetSelectedSkill() { if (selctedSkill) { return this->selctedSkill; }  }
	vector<Character*> GetTarGet() { if (!targetChr.empty()) return this->targetChr; }

	SkillManager* GetSS_MGR() { if (SS_MGR) { return this->SS_MGR; } };
	CharacterManager* GetSC_MGR() { if (SC_MGR) { return this->SC_MGR; } };
	CharacterManager* GetSM_MGR() { if (SM_MGR) { return this->SM_MGR; } };

	void SetClassArr(string* arr) { this->arrClass = arr; }
	string* GetClassArr() { if(arrClass)return this->arrClass; }

	void AddTarget(Character* target);
};

