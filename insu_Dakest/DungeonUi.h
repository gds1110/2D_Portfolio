#pragma once
#include "GameNode.h"

class Image;
class Skill;
class SkillManager;
class Character;
class CharacterManager;
class Tile;
class MapGenManager;
class DungeonUi : public GameNode
{
private:
	Image* underUi;
	Image* underIcon;
	Image* selSkillIcon;
	Image* MapBG;
	vector<Tile*> minmap;
	vector<RECT> minrc;
	Image* maps;
	Image* MiniMap;
	char szText[128] = "";
	int mouseOffsetX;
	int mouseOffsetY;
	int minimapposx;
	int minimapposy;
	Tile* currTile;
	Character* selChr;
	Skill* selSkill;
	SkillManager* selSkillmgr;
	CharacterManager* c_mgr;
	CharacterManager* m_mgr;
	string iconKey;
	MapGenManager* mapgen;
	HDC hdc2;

	bool currTileChange;
	bool firstTile;

public:
	virtual HRESULT Init();
	virtual HRESULT Init(CharacterManager* SC_MGR, CharacterManager* SM_MGR, DUNGEONINFO d_info,Tile* currTile);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	inline void setSelSkill(Skill* skill) { this->selSkill = skill; }
	inline void SetSelChr(Character* chr) { this->selChr = chr; }
	inline void SetSkillMgr(SkillManager* smgr) { this->selSkillmgr = smgr; }
	inline void SetCMGR(CharacterManager* c_mgr) { this->c_mgr = c_mgr; }
	inline void SetMMGR(CharacterManager* m_mgr) { this->m_mgr = m_mgr; }

	inline Skill* GetSelSkill() { return this->selSkill; }
	inline Character* GetSelChr() { return this->selChr; }
	inline SkillManager* GetSkillMgr() { return this->selSkillmgr; }
	inline CharacterManager* GetCMGR() { return this->c_mgr; }
	inline CharacterManager* GetMMGR() { return this->m_mgr; }


	virtual ~DungeonUi() {};
};

