#pragma once
#include "UI.h"

class Image;
class Skill;
class SkillManager;
class Character;
class UnderUi :public UI
{
private:
	Image* underUi;
	Image* underIcon;
	Image* selSkillIcon;

	Character* selChr;
	Skill* selSkill;
	SkillManager* selSkillmgr;
	CharacterManager* c_mgr;

	string iconKey;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	inline void setSelSkill(Skill* skill) { this->selSkill = skill; }

	virtual ~UnderUi() {};

};

