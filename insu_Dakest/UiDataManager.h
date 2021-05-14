#pragma once
#include "config.h"
#include "Singleton.h"

class Character;
class Skill;
class SkillManager;
class CharacterManager;
class UiDataManager : public Singleton<UiDataManager>
{
private:
	Character* selectedChr;
	Skill* selctedSkill;

	SkillManager* SS_MGR;
	CharacterManager* SC_MGR;

public:
	HRESULT Init();
	void Release();
	void Update();

	void selectSkill(Skill* select) { this->selctedSkill = select; }
	void SelectChar(Character* select) { this->selectedChr = select; }
	void SetSS_MGR(SkillManager* s_mgr) { this->SS_MGR = s_mgr; }
	void SetSC_MGR(CharacterManager* c_mgr) { this->SC_MGR = c_mgr; }

	Character* GetSelectedChar() { if (selectedChr) { return this->selectedChr; } }
	Skill* GetSelectedSkill() { if (selctedSkill) { return this->selctedSkill; }  }
	SkillManager* GetSS_MGR() { if (SS_MGR) { return this->SS_MGR; } };
	CharacterManager* GetSC_MGR() { if (SC_MGR) { return this->SC_MGR; } };
};

