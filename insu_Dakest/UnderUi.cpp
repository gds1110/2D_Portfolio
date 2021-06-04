#include "UnderUi.h"
#include "Image.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "MapGenManager.h"
#include "Inventory.h"
#include "ItemObject.h"

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
	/*MiniMap = new Image();
	MiniMap->Init(600, 600);*/
	MiniMap = ImageManager::GetSingleton()->FindImage("미니맵배경색");
	minimapposx = (WINSIZE_X / 2 + 10);
	minimapposy = (WINSIZE_Y - WINSIZE_Y / 3) + 10;
	mouseOffsetX = ((WINSIZE_X / 2 + 10));
	mouseOffsetY = ((WINSIZE_Y - WINSIZE_Y / 3) + 20);
	currTile = UiDataManager::GetSingleton()->GetTile();
	currTileChange = true;
	firstTile = true;
	SetRect(&minimapZone, WINSIZE_X / 2 + 10, (WINSIZE_Y - WINSIZE_Y / 3) + 10, WINSIZE_X / 2 + 10+430, (WINSIZE_Y - WINSIZE_Y / 3) + 10+230);
	return S_OK;
}

HRESULT UnderUi::Init(Tile* currTile, vector<Tile*> minmap)
{
	underUi = ImageManager::GetSingleton()->AddImage("유아이", "resource/dungeon/UI/D_under_ui2.BMP", 1280, 240, false);
	underIcon = nullptr;
	selSkillIcon = ImageManager::GetSingleton()->AddImage("스킬선택", "resource/sharedUi/sel_skill.BMP", 60, 60, true, RGB(88, 88, 88));
	MapBG = ImageManager::GetSingleton()->AddImage("미니맵배경", "resource/sharedUi/downpanelmap.BMP", 480, 240, false);
	selSkill = nullptr;
	selSkillmgr = nullptr;
	c_mgr = nullptr;
	m_mgr = nullptr;
	hdc2 = UiDataManager::GetSingleton()->GetHdc();
	maps = UiDataManager::GetSingleton()->GetMapimg();
	//minmap = UiDataManager::GetSingleton()->GetMiniMap();
	this->minmap = minmap;
	MiniMap = ImageManager::GetSingleton()->FindImage("미니맵배경색");
	minimapposx = (WINSIZE_X / 2 + 10);
	minimapposy = (WINSIZE_Y - WINSIZE_Y / 3) + 10;
	mouseOffsetX = ((WINSIZE_X / 2 + 10));
	mouseOffsetY = ((WINSIZE_Y - WINSIZE_Y / 3) + 20);
	this->currTile = currTile;
	currTileChange = true;
	firstTile = true;
	currflame = ImageManager::GetSingleton()->FindImage("현재위치");
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
	if (currTile->GetType() == TileType::Path)
	{
		
		for (int i = 0; i < currTile->GetPath().size(); i++)
		{
			currTile->GetPath()[i]->SetIsVisited(true);
		}
	}

}

void UnderUi::Render(HDC hdc)
{

	HDC miniDC = MiniMap->GetMemDC();

	underUi->Render(hdc, 0, WINSIZE_Y - WINSIZE_Y / 3);
	if (MapBG)
	{
		MapBG->Render(hdc, WINSIZE_X / 2, WINSIZE_Y - WINSIZE_Y / 3);
	}
	
	if (underIcon) {
		underIcon->Render2(hdc, 210, WINSIZE_Y - WINSIZE_Y / 3 + 50, true, 1);
	}

	if (!minmap.empty())
	{
		
		for (int i = 0; i < minmap.size(); i++)
		{
			if (minmap[i]->GetType() == TileType::Path) {
		
				minmap[i]->Render(miniDC);
			}
		}
		for (int i = 0; i < minmap.size(); i++)
		{
			if (minmap[i]->GetType() == TileType::Room) {
	
				minmap[i]->Render(miniDC);
			}
		}
	
		MiniMap->MinimapRender(hdc, minimapposx, minimapposy, currTile , false);

	}
	
	if (currTile->GetType() == TileType::Room)
	{
		if (currflame)
		{
			//currflame->Render(miniDC, minimapposx + 205, minimapposy + 90);
			currflame->Render(hdc, minimapposx + 205, minimapposy + 90);
		}
	}
	else if (currTile->GetType() == TileType::Path)
	{
		if (currflame)
		{
			//currflame->Render(hdc, minimapposx + currTile->GetPath()[0]->getPos().x, minimapposy + currTile->GetPath()[0]->getPos().y);
			//currflame->flameRender(miniDC, minimapposx + 205, minimapposy + 90, currTile);
			currflame->flameRender(hdc, minimapposx-50, minimapposy, currTile);
		}
	}
	UiDataManager::GetSingleton()->GetInven()->Render(hdc);

	if (selChr) {

		selSkillmgr->Render(hdc);
	}

	if (selSkill)
	{
		selSkillIcon->Render(hdc, selSkill->GetPos().x, selSkill->GetPos().y, true);
	}
}

void UnderUi::SkillRender(HDC hdc)
{
	

}
