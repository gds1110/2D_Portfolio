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
	hdc2 = UiDataManager::GetSingleton()->GetHdc();
	maps = UiDataManager::GetSingleton()->GetMapimg();
	minmap = UiDataManager::GetSingleton()->GetMiniMap();
	//tile = UiDataManager::GetSingleton()->GetMiniMap();
	MiniMap = new Image();
	MiniMap->Init(430, 230);
	currTile = nullptr;
	return S_OK;
}

void UnderUi::Release()
{
}

void UnderUi::Update()
{
	if (UiDataManager::GetSingleton()->GetTile()) {
		currTile = UiDataManager::GetSingleton()->GetTile();
	}

	for (int i = 0; i < minmap.size(); i++)
	{
		minmap[i]->Update();
		
	}
	if (currTile)
	{
		for (int i = 0; i < currTile->GetWay().size(); i++)
		{
			if (currTile->GetWay()[i]->getindex() > -1)
			{
				currTile->GetWay()[i]->SetIsWay(true);
			}
		
		}
		for (int i = 0; i < currTile->GetWay().size(); i++) {
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				if (PointInRect({ (WINSIZE_X / 2 + 10) + g_ptMouse.x,(WINSIZE_Y - WINSIZE_Y / 3) + 20 + g_ptMouse.y }, (currTile->GetWay()[i]->GetRC())) && currTile->GetWay()[i]->GetIsWay() == true)
				{
					currTile->GetWay()[i]->SetIsCurrted(true);
					currTile = currTile->GetWay()[i];
				}
			}

		}
	}
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
	

	/*if (!minmap.empty()) {
		

		for (int i = 0; i < minmap.size(); i++)
		{
			minmap[i]->SetPos( minmap[i]->GetIdX() * TILE_SIZE ,WINSIZE_Y/4+minmap[i]->GetIdY() *  (TILE_SIZE));
			minmap[i]->Update();
		}
	}*/
}

void UnderUi::Render(HDC hdc)
{

	HDC miniDC = MiniMap->GetMemDC();
	//UiDataManager::GetSingleton()->SetHdc(miniDC);

	underUi->Render(hdc, 0, WINSIZE_Y - WINSIZE_Y / 3);
	if (MapBG)
	{
		MapBG->Render(hdc, WINSIZE_X / 2, WINSIZE_Y - WINSIZE_Y / 3);
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
	wsprintf(szText, "X : %d, Y : %d", (WINSIZE_X / 2 + 10) + g_ptMouse.x, (WINSIZE_Y - WINSIZE_Y / 3) + 20 + g_ptMouse.y);
	TextOut(hdc, 200, 60, szText, strlen(szText));
	if (!minmap.empty())
	{
		
		for (int i = 0; i < minmap.size(); i++)
		{
			if (minmap[i]->GetType() == TileType::Path) {
				//openList[i]->Render(miniDC);
				
				minmap[i]->Render(miniDC);
			}
		}
		for (int i = 0; i < minmap.size(); i++)
		{
			if (minmap[i]->GetType() == TileType::Room) {
				//openList[i]->Render(miniDC);
				minmap[i]->Render(hdc);
				minmap[i]->Render(miniDC);
			}
		}
		MiniMap->Render(hdc, WINSIZE_X / 2 + 10, WINSIZE_Y - WINSIZE_Y / 3 + 20);
		//MiniMap->Render(hdc, 100, 0);
		//MiniMap->Render5(hdc, WINSIZE_X / 2 + 10, WINSIZE_Y - WINSIZE_Y / 3 + 20,
		//	false, 1, UiDataManager::GetSingleton()->GetMin(), UiDataManager::GetSingleton()->GetMax());
	/*	MiniMap->Render5(hdc, 0,0,
			false, 1, UiDataManager::GetSingleton()->GetMin(), UiDataManager::GetSingleton()->GetMax());*/
		//MiniMap->Render6(hdc, WINSIZE_X / 2 + 10, WINSIZE_Y - WINSIZE_Y / 3 + 20,
		//	false, 1, UiDataManager::GetSingleton()->GetMin(), UiDataManager::GetSingleton()->GetMax(),0,0,(UiDataManager::GetSingleton()->GetTile()));
	}
}
