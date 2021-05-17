#pragma once
#include "config.h"
#include "Singleton.h"
#include <string>
#include <vector>

class Character;
class Skill;
class SkillManager;
class CharacterManager;
class UiDataManager : public Singleton<UiDataManager>
{
private:
	Character* selectedChr;
	vector<Character*> targetChr;
	bool selCheck;
	Skill* selctedSkill;
	string* arrClass;
	SkillManager* SS_MGR;
	CharacterManager* SC_MGR;
	CharacterManager* SM_MGR;
public:
	HRESULT Init();
	void Release();
	void Update();

	void selectSkill(Skill* select) { this->selctedSkill = select; }
	void SelectChar(Character* select) { this->selectedChr = select; }

	void SetSS_MGR(SkillManager* s_mgr) { this->SS_MGR = s_mgr; }
	void SetSC_MGR(CharacterManager* c_mgr) { this->SC_MGR = c_mgr; }
	void SetSM_MGR(CharacterManager* m_mgr) { this->SM_MGR = m_mgr; }

	void SetselCheck(bool check) { this->selCheck = check; }
	bool GetselCheck() { return this->selCheck; }

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

