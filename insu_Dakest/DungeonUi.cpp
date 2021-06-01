#include "DungeonUi.h"
#include "Image.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "MapGenManager.h"

HRESULT DungeonUi::Init()
{
	underUi = ImageManager::GetSingleton()->FindImage("유아이");
	underIcon = nullptr;
	selSkillIcon = ImageManager::GetSingleton()->FindImage("스킬선택");
	MapBG = ImageManager::GetSingleton()->FindImage("미니맵배경");
	selSkill = nullptr;
	selSkillmgr = nullptr;
	c_mgr = nullptr;
	m_mgr = nullptr;

	minmap = UiDataManager::GetSingleton()->GetMiniMap();
	MiniMap = ImageManager::GetSingleton()->FindImage("미니맵배경색");
	minimapposx = (WINSIZE_X / 2 + 10);
	minimapposy = (WINSIZE_Y - WINSIZE_Y / 3) + 20;
	mouseOffsetX = ((WINSIZE_X / 2 + 10));
	mouseOffsetY = ((WINSIZE_Y - WINSIZE_Y / 3) + 20);
	currTile = UiDataManager::GetSingleton()->GetTile();
	currTileChange = true;
	firstTile = true;
	return S_OK;
}

HRESULT DungeonUi::Init(CharacterManager* SC_MGR, CharacterManager* SM_MGR, DUNGEONINFO d_info, Tile* currTile)
{
	this->currTile = currTile;
	this->d_info = d_info;
	underUi = ImageManager::GetSingleton()->FindImage("유아이");
	underIcon = nullptr;
	selSkillIcon = ImageManager::GetSingleton()->FindImage("스킬선택");
	MapBG = ImageManager::GetSingleton()->FindImage("미니맵배경");
	selSkill = nullptr;
	selSkillmgr = nullptr;
	c_mgr = SC_MGR;
	m_mgr = SM_MGR;

	minmap = UiDataManager::GetSingleton()->GetMiniMap();
	MiniMap = ImageManager::GetSingleton()->FindImage("미니맵배경색");
	minimapposx = (WINSIZE_X / 2 + 10);
	minimapposy = (WINSIZE_Y - WINSIZE_Y / 3) + 20;
	mouseOffsetX = ((WINSIZE_X / 2 + 10));
	mouseOffsetY = ((WINSIZE_Y - WINSIZE_Y / 3) + 20);
	//currTile = UiDataManager::GetSingleton()->GetTile();
	currTileChange = true;
	firstTile = true;
	return S_OK;
	return S_OK;
}



void DungeonUi::Release()
{
}

void DungeonUi::Update()
{
	mouseOffsetX = d_info.pos.x-215; // UiDataManager::GetSingleton()->GetTile()->getPos().x - 215;
	mouseOffsetY = d_info.pos.y-100; //UiDataManager::GetSingleton()->GetTile()->getPos().y - 100;
	//if (UiDataManager::GetSingleton()->GetTile()) {
	//	currTile = UiDataManager::GetSingleton()->GetTile();
	//	//mouseOffsetX = (WINSIZE_X / 2 + 10);//+ 20;
	//	//mouseOffsetY = (WINSIZE_Y - WINSIZE_Y / 3);//+ 20 + 20 ;
	//}

	/*for (int i = 0; i < minmap.size(); i++)
	{
		minmap[i]->Update();

	}*/

	if (currTileChange == true) {
		if (firstTile == true) {
			for (int i = 0; i < minmap.size(); i++)
			{
				//minmap[i]->SetPos(minmap[i]->getPos().x + (WINSIZE_X / 2 + 10), minmap[i]->getPos().y + (WINSIZE_Y - WINSIZE_Y / 3) + 20);
			}
			firstTile = false;
		}

		currTileChange = false;
	}

	currTile->Update();

	for (int i = 0; i < currTile->GetWay().size(); i++)
	{
		if (currTile->GetWay()[i]->getindex() > -1)
		{
			currTile->GetWay()[i]->SetIsWay(true);
			currTile->GetWay()[i]->Update();
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

void DungeonUi::Render(HDC hdc)
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
	//wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x - minimapposx, g_ptMouse.y - minimapposy);
	//TextOut(hdc, 200, 60, szText, strlen(szText));
	//wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x - minimapposx + mouseOffsetX, g_ptMouse.y - minimapposy + mouseOffsetY);
	//TextOut(hdc, 800, 100, szText, strlen(szText));
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
				//minmap[i]->Render(hdc);
				minmap[i]->Render(miniDC);
			}
		}
		//MiniMap->Render(hdc, WINSIZE_X / 2 + 10, WINSIZE_Y - WINSIZE_Y / 3 + 20);
		//MiniMap->MinimapRender(hdc, minimapposx, minimapposy, UiDataManager::GetSingleton()->GetTile(),false);
		MiniMap->MinimapRender(hdc, minimapposx, minimapposy, currTile, false);
		//MiniMap->Render(hdc, 0, 0);
		//MiniMap->Render5(hdc, WINSIZE_X / 2 + 10, WINSIZE_Y - WINSIZE_Y / 3 + 20,
		//	false, 1, UiDataManager::GetSingleton()->GetMin(), UiDataManager::GetSingleton()->GetMax());
	/*	MiniMap->Render5(hdc, 0,0,
			false, 1, UiDataManager::GetSingleton()->GetMin(), UiDataManager::GetSingleton()->GetMax());*/
			//MiniMap->Render6(hdc, WINSIZE_X / 2 + 10, WINSIZE_Y - WINSIZE_Y / 3 + 20,
			//	false, 1, UiDataManager::GetSingleton()->GetMin(), UiDataManager::GetSingleton()->GetMax(),0,0,(UiDataManager::GetSingleton()->GetTile()));
	}

	//for (int i = 0; i < minrc.size(); i++)
	//{
	//	Rectangle(hdc, minrc[i].left, minrc[i].top, minrc[i].right, minrc[i].bottom);
	//}
}
