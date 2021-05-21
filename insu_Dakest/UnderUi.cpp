#include "UnderUi.h"
#include "Image.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "MapGenManager.h"
HRESULT UnderUi::Init()
{
	underUi = ImageManager::GetSingleton()->AddImage("유아이", "resource/dungeon/UI/D_under_ui2.BMP", 1280, 240, false);
	underIcon = nullptr;
	selSkillIcon = ImageManager::GetSingleton()->AddImage("스킬선택", "resource/sharedUi/sel_skill.BMP",60,60,true,RGB(88,88,88));
	MapBG = ImageManager::GetSingleton()->AddImage("미니맵배경", "resource/sharedUi/downpanelmap.BMP", 480, 240, false);
	selSkill = nullptr;
	selSkillmgr = nullptr;
	c_mgr = nullptr;
	m_mgr = nullptr;
	minmap = UiDataManager::GetSingleton()->GetMiniMap();
	//tile = UiDataManager::GetSingleton()->GetMiniMap();
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
	if (!minmap.empty()) {
		

		for (int i = 0; i < minmap.size(); i++)
		{
			minmap[i]->SetPos( minmap[i]->GetIdX() * TILE_SIZE ,WINSIZE_Y/4+minmap[i]->GetIdY() *  (TILE_SIZE));
			minmap[i]->Update();
		}
	}
}

void UnderUi::Render(HDC hdc)
{
	underUi->Render(hdc, 0, WINSIZE_Y - WINSIZE_Y / 3);
	if (MapBG)
	{
		MapBG->Render(hdc, WINSIZE_X / 2, WINSIZE_Y - WINSIZE_Y / 3);
		//if (tile)
		//{
		//	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
		//	{
		//		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		//		{
		//			tile[i][j].Render(hdc);
		//		}
		//	}
		//}
	}
	if (!minmap.empty())
	{
		for (int i = 0; i < minmap.size(); i++)
		{
			minmap[i]->Render2(hdc,WINSIZE_X/2,WINSIZE_Y-WINSIZE_Y/3);
		}
	}
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
