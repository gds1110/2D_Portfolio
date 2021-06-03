#pragma once
#include "GameNode.h"
#include <utility>
#include <algorithm>
class Skill;
class SkillManager;
class Character;
class CharacterManager;
class UnderUi;
class OverUi;

using BODER = pair<Character*, int>;

class DataManager : public GameNode
{
	enum BattleProGress
	{
		BSTART,
		ING,
		BEND,
		NOBATTLE
	};
	enum TurnType
	{
		PLAYERTURN,
		MONTURN,
		NONETURN
	};

private:
	int camPos;
	Character* selectedChr;
	Character* cursorChar;
	Character* MselctetChr;
	vector<Character*> targetChr;
	vector<Tile*> minmap;
	Skill* selctedSkill;
	string* arrClass;
	SkillManager* S_MGR;
	CharacterManager* C_MGR;
	CharacterManager* M_MGR;
	UnderUi* underUI;
	OverUi* overUi;
	bool selCheck;
	bool targeton;
	bool BattleStage;
	RECT minimapZone;
	RECT characterZone;
	RECT statusZone;
	RECT Door;
	char szText[128];
	Tile* thisTile;
	BattleProGress BPG =NOBATTLE;
	TurnType TTYPE = NONETURN;
	bool isChange;
	int battleTurn;
	vector<BODER> BDice;
	vector<BODER>::iterator boiter;
	int mouseOffsetX;
	int mouseOffsetY;
	int minimapposx;
	int	minimapposy;
	float eltimess = 0;

	int hiteffectFrame;
	Image* HitEffect;
	float HitTimes;
	bool HitEffectCheck;

public:
	virtual HRESULT Init();
	virtual HRESULT Init(CharacterManager* SC_MGR,CharacterManager* SM_MGR,Tile* currTile);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);


	static bool compare(const BODER& a, const BODER& b);


	bool BattleStages2(CharacterManager* C_MGR,CharacterManager* M_MGR, Character* turnchr);


	bool GetBattle() { return BattleStage; }
	void SetBattle(bool setbatte) { this->BattleStage = setbatte; }

	int GetCampos() { return this->camPos; }
	void SetCampos(int cam) { this->camPos = cam; }

	void SetCursorChar(Character* chr) { this->cursorChar = chr; }
	Character* GetCursorChar() { return this->cursorChar; }

	void selectSkill(Skill* select) { this->selctedSkill = select; }
	void SelectChar(Character* select) { this->selectedChr = select; }

	void SetS_MGR(SkillManager* s_mgr) { this->S_MGR = s_mgr; }
	void SetC_MGR(CharacterManager* c_mgr) { this->C_MGR = c_mgr; }
	void SetM_MGR(CharacterManager* m_mgr) { this->M_MGR = m_mgr; }

	void SetselCheck(bool check) { this->selCheck = check; }
	bool GetselCheck() { return this->selCheck; }

	Character* GetSelectedChar() { if (selectedChr) { return this->selectedChr; } }
	Skill* GetSelectedSkill() { if (selctedSkill) { return this->selctedSkill; } }
	vector<Character*> GetTarGet() { if (!targetChr.empty()) return this->targetChr; }

	SkillManager* GetS_MGR() { if (S_MGR) { return this->S_MGR; } };
	CharacterManager* GetC_MGR() { if (C_MGR) { return this->C_MGR; } };
	CharacterManager* GetM_MGR() { if (M_MGR) { return this->M_MGR; } };

	void SetClassArr(string* arr) { this->arrClass = arr; }
	string* GetClassArr() { if (arrClass)return this->arrClass; }

	void AddTarget(Character* target) { targetChr.push_back(target); }

	bool DoHitEffect(TurnType types);

};

