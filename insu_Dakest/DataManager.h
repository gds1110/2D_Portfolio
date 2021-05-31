#pragma once
#include "GameNode.h"

class Skill;
class SkillManager;
class Character;
class CharacterManager;
class UnderUi;
class DataManager : public GameNode
{
private:
	int camPos;
	Character* selectedChr;
	Character* cursorChar;
	vector<Character*> targetChr;
	Skill* selctedSkill;
	string* arrClass;
	SkillManager* S_MGR;
	CharacterManager* C_MGR;
	CharacterManager* M_MGR;
	UnderUi* underUI;
	bool selCheck;
	bool targeton;
	bool BattleStage;
public:
	virtual HRESULT Init();
	virtual HRESULT Init(CharacterManager* SC_MGR,CharacterManager* SM_MGR, UnderUi* ui);
	virtual HRESULT Init(CharacterManager* SC_MGR,CharacterManager* SM_MGR, UnderUi* ui, Tile* currtile);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

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

};

