#include "DungeonRoom.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Character.h"
#include "CharacterManager.h"
#include "H_Crusader.h"
#include "H_BountyHunter.h"
#include "H_Leaper.h"
#include "H_HighWayMan.h"
#include "H_Vestel.h"
#include "UnderUi.h"
#include "OverUi.h"
#include "skeleton_arbalistar.h"
#include "skeleton_bearer.h"
#include "skeleton_captain.h"
#include "skeleton_common.h"
#include "MapGenManager.h"
#include "SkillManager.h"
#include "DataManager.h"
#include "DungeonUi.h"

HRESULT DungeonRoom::Init()
{
	d_info.infoDone = false;
	d_info.isEnemyed = false;
	d_info.isSuddenEnemy = false;
	d_info.isCurios = false;
	d_info.roomType = 0;
	d_info.pathType = -1;
	d_info.tileDone = false;
	d_info.enemySize = 2;
	d_info.dType = DungeonType::START;
	for (int i = 0; i < d_info.enemySize; i++)
	{
		d_info.enemyArr[i] = 0;
	}


	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();
	M_MGR = new CharacterManager;
	for (int i = 0; i < d_info.enemySize; i++)
	{
		M_MGR->AddMonster(d_info.enemyArr[i]);
	}
	CamPos = 400;
	//CamPos = WINSIZE_X / 2;
	camBuffer = new Image();
	camBuffer->Init(WINSIZE_X * 2, WINSIZE_Y);

	/*d_UI = new DungeonUi();
	d_UI->Init();*/
	
	FindFirstBg(this->d_info);

	DM = new DataManager();
	DM->Init();

	return S_OK;
}

HRESULT DungeonRoom::DungoenInit(Tile* flowTile)
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	if (flowTile->GetDinfo().infoDone == false)
	{
		d_info.infoDone = true;
		d_info.isEnemyed = true;
		d_info.isSuddenEnemy = false;
		d_info.isCurios = false;
		d_info.roomType = 0;
		d_info.pathType = -1;
		d_info.tileDone = false;
		d_info.enemySize = 2;
		d_info.dType = DungeonType::ROOM;
		for (int i = 0; i < d_info.enemySize; i++)
		{
			d_info.enemyArr[i] = 0;
		}
	}
	else
	{
		this->d_info = flowTile->GetDinfo();
	}
	if (d_info.dType == DungeonType::START)
	{
		d_info.isEnemyed = false;
		d_info.enemySize = 0;
	}
	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();

	for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
	{
		C_MGR->GetCharacters()[i]->SetPos(90 + 150 * i);
	}
	if (d_info.isEnemyed) {
		M_MGR = new CharacterManager;
		for (int i = 0; i < d_info.enemySize; i++)
		{
			M_MGR->AddMonster(d_info.enemyArr[i]);
		}
	}
	CamPos = 400;
	//CamPos = WINSIZE_X / 2;
	camBuffer = new Image();
	camBuffer->Init(WINSIZE_X * 2, WINSIZE_Y);


	/*d_UI = new DungeonUi();
	d_UI->Init(C_MGR, M_MGR, d_info,UiDataManager::GetSingleton()->GetTile());*/

	FindFirstBg(this->d_info);
	DM = new DataManager();
	DM->Init(C_MGR, M_MGR,flowTile);
	return S_OK;
}

HRESULT DungeonRoom::DungeonRoomInit(CharacterManager cmgr, Tile* flowTile, DUNGEONINFO info)
{

	if (info.infoDone == false)
	{
		d_info.infoDone = true;
		d_info.isEnemyed = true;
		d_info.isSuddenEnemy = false;
		d_info.isCurios = false;
		d_info.roomType = 0;
		d_info.pathType = -1;
		d_info.tileDone = false;
		d_info.enemySize = 2;
		d_info.dType = DungeonType::ROOM;
		for (int i = 0; i < d_info.enemySize; i++)
		{
			d_info.enemyArr[i] = 0;
		}
	}
	else
	{
		this->d_info = info;
	}
	if (d_info.dType == DungeonType::START)
	{
		d_info.isEnemyed = false;
		d_info.enemySize = 0;
	}
	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();
	
	for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
	{
		C_MGR->GetCharacters()[i]->SetPos(90 + 150 * i);
	}
	M_MGR = new CharacterManager;
	for (int i = 0; i < d_info.enemySize; i++)
	{
		M_MGR->AddMonster(d_info.enemyArr[i]);
	}
	CamPos = 400;
	//CamPos = WINSIZE_X / 2;
	camBuffer = new Image();
	camBuffer->Init(WINSIZE_X * 2, WINSIZE_Y);

	/*d_UI = new DungeonUi();
	d_UI->Init(C_MGR, M_MGR, d_info,UiDataManager::GetSingleton()->GetTile());*/

	FindFirstBg(this->d_info);
	DM = new DataManager();
	DM->Init(C_MGR,M_MGR,flowTile);
	return S_OK;
}

void DungeonRoom::Release()
{
	//SAFE_RELEASE(C_MGR);
	SAFE_RELEASE(M_MGR);
	SAFE_RELEASE(camBuffer);
	SAFE_RELEASE(DM);
}

void DungeonRoom::Update()
{
	if (d_info.isEnemyed)
	{
	}

	if (DM)
	{
		DM->Update();
	}

	
}

void DungeonRoom::Render(HDC hdc)
{
	HDC camDC = camBuffer->GetMemDC();

	if (bgFirst) {
		if (d_info.dType == DungeonType::ROOM) {
			bgFirst->FrameRender(camDC, CamPos, 0, 0, d_info.roomType);
		}
		else if (d_info.dType == DungeonType::START) {
			bgFirst->Render(camDC, CamPos, 0);
		}
	}
	
	camBuffer->CamRender2(hdc, WINSIZE_X / 2 + 370, 350, true);
	wsprintf(szText, "campos : %d", CamPos);
	
	if (DM)
	{
		DM->Render(hdc);
	}

	TextOut(hdc, WINSIZE_X / 2, 100, szText, strlen(szText));
	//d_UI->Render(hdc);
}

void DungeonRoom::FindFirstBg(DUNGEONINFO d_info)
{
	switch (d_info.dType)
	{
	case DungeonType::ROOM:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("规技飘");
		break;
	case DungeonType::START:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("带傈涝备");

		break;
	default:
		break;
	}
}
