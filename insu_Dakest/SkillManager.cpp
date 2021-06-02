#include "SkillManager.h"
#include "Skill.h"
#include "config.h"
#include "Image.h"
#include "CommonFunction.h"
HRESULT SkillManager::Init()
{
	index = 0;

	return S_OK;
}

HRESULT SkillManager::Init(Character* owner)
{
	index = 0;
	this->owner = owner;
	for (int i = 0; i < 6; i++)
	{
		skillPos[i] = 370 + (i * 50);
	}
	return S_OK;
}

void SkillManager::Release()
{
	for (int i = 0; i < skillSlot.size(); i++)
	{
		SAFE_RELEASE(skillSlot[i]);
	}
}

void SkillManager::Update()
{

	for (int i = 0; i < skillSlot.size(); i++)
	{
		skillSlot[i]->Update();
	}
			
}

void SkillManager::Render(HDC hdc)
{
	for (int i = 0; i < skillSlot.size(); i++)
	{
		skillSlot[i]->Render(hdc);
	}
}

void SkillManager::AddSkill(Skill* skill)
{
	
	if (skillSlot.size() > 3)
	{
		return;
	}
	else
	{

		skillSlot.push_back(skill);
		/*  (*it) = v_Heros.back();
		  (*it)->Init();
		  (*it)->SetPos(WINSIZE_X / 2 - (index * 200));*/
		skillSlot[index]->Init();
		skillSlot[index]->SetOwner(this->owner);
		//skillSlot[index]->SetHClass();
		//v_Heros[index]->SetPos(WINSIZE_X / 2-(index * 100));
		//v_Heros[index]->SetPos(WINSIZE_X / 2-(posarray[index]));
		skillSlot[index]->SetHClass(hclass);
		skillSlot[index]->SkillInit();
		skillSlot[index]->SetPos(370+ (index * 50));
		skillSlot[index]->SetIndex(index);
		skillSlot[index]->SetskillNum(index);
		index++;

	}
}

void SkillManager::AddSkill2(Skill* skill, int skillNum, int index)
{
	if (skillSlot.size() > 3)
	{
		return;
	}
	else
	{

		skillSlot.push_back(skill);
		/*  (*it) = v_Heros.back();
		  (*it)->Init();
		  (*it)->SetPos(WINSIZE_X / 2 - (index * 200));*/
		skillSlot[index]->Init();
		skillSlot[index]->SetOwner(this->owner);
		//skillSlot[index]->SetHClass();
		//v_Heros[index]->SetPos(WINSIZE_X / 2-(index * 100));
		//v_Heros[index]->SetPos(WINSIZE_X / 2-(posarray[index]));
		skillSlot[index]->SetHClass(hclass);
		skillSlot[index]->SkillInit();

		skillSlot[index]->SetPos(370 + (index * 50));
		skillSlot[index]->SetIndex(index);
		skillSlot[index]->SetskillNum(index);

	}
}

void SkillManager::AddSkill3(SKILLTYPE type, int skillNum, int index)
{
	if (type==SWAPSKILL)
	{
		skillSlot.push_back(new SwapSkill());
		skillSlot[4]->Init();
		skillSlot[4]->SetOwner(this->owner);
		skillSlot[4]->SetSkillType(type);
		skillSlot[4]->SetHClass(hclass);
		skillSlot[4]->SetskillNum(skillNum);
		skillSlot[4]->SkillInit();

		//skillSlot[4]->SetIndex(4);
		skillSlot[4]->SetPos(skillPos[4]);
	}
	else if (type == NOTURNSKILL)
	{
		skillSlot.push_back(new NoTurn());
		skillSlot[5]->Init();
		skillSlot[5]->SetOwner(this->owner);
		skillSlot[5]->SetSkillType(type);
		skillSlot[5]->SetHClass(hclass);
		skillSlot[5]->SetskillNum(skillNum);
		skillSlot[5]->SkillInit();

		//skillSlot[5]->SetIndex(5);
		skillSlot[5]->SetPos(skillPos[5]);

	}
	else
	{
		switch (type)
		{
		case COMBATSKILL:
			skillSlot.push_back(new CombatAttack(this->owner));

			break;
		case ARANGESKILL:
			skillSlot.push_back(new ArangeAttack(this->owner));

			break;
		case CHARGESKILL:
			break;
		case NONESKILLTYPE:
			break;
		default:
			break;
		}
		/*  (*it) = v_Heros.back();
		  (*it)->Init();
		  (*it)->SetPos(WINSIZE_X / 2 - (index * 200));*/
		skillSlot[index]->Init();
		skillSlot[index]->SetOwner(this->owner);
		skillSlot[index]->SetSkillType(type);
		skillSlot[index]->SetHClass(hclass);
		skillSlot[index]->SetskillNum(skillNum);
		skillSlot[index]->SkillInit();

		skillSlot[index]->SetIndex(index);
		skillSlot[index]->SetPos(skillPos[index]);

	}
}

