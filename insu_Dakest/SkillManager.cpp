#include "SkillManager.h"
#include "Skill.h"
#include "Image.h"
#include "CommonFunction.h"
HRESULT SkillManager::Init()
{
	index = 0;

	return S_OK;
}

void SkillManager::Release()
{
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
	
	if (skillSlot.size() > 4)
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
		//v_Heros[index]->SetPos(WINSIZE_X / 2-(index * 100));
		//v_Heros[index]->SetPos(WINSIZE_X / 2-(posarray[index]));
		skillSlot[index]->SetPos(370+ (index * 50));
		skillSlot[index]->SetIndex(index);
		index++;

	}
}

