#include "UnderUi.h"
#include "Image.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
HRESULT UnderUi::Init()
{
	underUi = ImageManager::GetSingleton()->AddImage("유아이", "resource/dungeon/UI/D_under_ui2.BMP", 1280, 240, false);
	underIcon = nullptr;
	selSkillIcon = ImageManager::GetSingleton()->AddImage("스킬선택", "resource/sharedUi/sel_skill.BMP",60,60,true,RGB(88,88,88));
	selSkill = nullptr;
	selSkillmgr = nullptr;
	c_mgr = nullptr;
	m_mgr = nullptr;
	return S_OK;
}

void UnderUi::Release()
{

}

void UnderUi::Update()
{

	if (selChr)
	{
		iconKey = selChr->GetClassArr()[selChr->GetClass()] + "아이콘";
		underIcon = ImageManager::GetSingleton()->FindImage(iconKey);
		selSkillmgr = selChr->getSkillMgr();
		for (int i = 0; i < selSkillmgr->GetSkillSlot().size(); i++) {
			if (selChr->GetIndex() < selSkillmgr->GetSkillSlot()[i]->GetSkillInfo().skillRank.x || selChr->GetIndex() > selSkillmgr->GetSkillSlot()[i]->GetSkillInfo().skillRank.y)
			{
				selSkillmgr->GetSkillSlot()[i]->SetSkillState(Skill::SkillState::OFF);
			}
		}
		
	}


}

void UnderUi::Render(HDC hdc)
{
	underUi->Render(hdc, 0, WINSIZE_Y - WINSIZE_Y / 3);
	if (underIcon) {
		underIcon->Render2(hdc, 210, WINSIZE_Y - WINSIZE_Y / 3 + 50, true, 0.5);
	}
	if (selChr) {
		
		selSkillmgr->Render(hdc);		
	}
	if (selSkill)
	{
		selSkillIcon->Render(hdc, selSkill->GetPos().x, selSkill->GetPos().y, true);
	}
}
