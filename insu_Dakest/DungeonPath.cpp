#include "DungeonPath.h"
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
HRESULT DungeonPath::Init()
{
		d_info.infoDone = false;
		d_info.isEnemyed = true;
		d_info.isSuddenEnemy = false;
		d_info.isCurios = false;
		d_info.roomType = -1;
		d_info.pathType = 0;
		d_info.tileDone = false;
		d_info.enemySize = 2;
		d_info.dType = DungeonType::PATH;
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
	camBuffer->Init(WINSIZE_X*2, WINSIZE_Y);

	d_UI = new DungeonUi();
	d_UI->Init();

	bgThird = ImageManager::GetSingleton()->FindImage("원거리배경");
	bgSecond = ImageManager::GetSingleton()->FindImage("근거리");
	FindFirstBg(this->d_info);

	return S_OK;
}

HRESULT DungeonPath::DungeonPathInit(Tile* flowTile)
{
	return S_OK;
}

HRESULT DungeonPath::DungeonPathInit(CharacterManager cmgr, Tile* flowTile, DUNGEONINFO info)
{
	if (info.infoDone == false)
	{
		d_info.infoDone = false;
		d_info.isEnemyed = true;
		d_info.isSuddenEnemy = false;
		d_info.isCurios = false;
		d_info.roomType = -1;
		d_info.pathType = 0;
		d_info.tileDone = false;
		d_info.enemySize = 2;
		d_info.dType=DungeonType::PATH;
		for (int i = 0; i < d_info.enemySize; i++)
		{
			d_info.enemyArr[i] = 0;
		}
	}
	else
	{
		this->d_info = info;
	}
	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();
	M_MGR = new CharacterManager;
	for (int i = 0; i < d_info.enemySize; i++)
	{
		M_MGR->AddMonster(d_info.enemyArr[i]);
	}
	CamPos = 1920 / 2;
	camBuffer = new Image();
	camBuffer->Init(1920, 720);


	bgThird = ImageManager::GetSingleton()->FindImage("원거리배경");
	bgSecond = ImageManager::GetSingleton()->FindImage("근거리");
	FindFirstBg(this->d_info);

	return S_OK;
}

void DungeonPath::Release()
{
	SAFE_RELEASE(C_MGR);
	SAFE_RELEASE(M_MGR);
	SAFE_RELEASE(camBuffer);
	SAFE_RELEASE(DM);
	SAFE_RELEASE(d_UI);
}

void DungeonPath::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) || KeyManager::GetSingleton()->IsStayKeyDown('D')) {
		//
		if (CamPos >-1790)
		{
			CamPos -= 10;

			if ((CamPos - 2) < -WINSIZE_X * 2)
			{
				CamPos = -WINSIZE_X * 2;
			}
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) || KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		//
		if (CamPos <400)
		{
			CamPos += 10;;
			if (CamPos - 1 > WINSIZE_X / 2)
			{
				CamPos = WINSIZE_X / 2;
			}

		}
	}
	if (C_MGR)
	{
		C_MGR->Update();
	}
}

void DungeonPath::Render(HDC hdc)
{
	HDC camDC = camBuffer->GetMemDC();

	if (bgThird) {
		bgThird->Render(camDC, CamPos / 5, 0, false);
	}
	if (bgSecond) {
		bgSecond->Render(camDC, CamPos / 2, 0, false);
	}
	if (bgFirst) {
		bgFirst->Render(camDC, CamPos , 0, false);
	}
	if (C_MGR)
	{
		C_MGR->Render(hdc);
	}
	
	wsprintf(szText, "campos : %d", CamPos);

	camBuffer->CamRender(hdc, WINSIZE_X/2+400, 350, true);
	TextOut(hdc, WINSIZE_X / 2, 100, szText, strlen(szText));

	d_UI->Render(hdc);
}

void DungeonPath::FindFirstBg(DUNGEONINFO d_info)
{
	switch (d_info.pathType)
	{
	case 0:
		this->bgFirst=ImageManager::GetSingleton()->FindImage("복도배경1");
		break;
	case 1:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("복도배경1");
		break;
	case 2:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("복도배경2");
		break;
	case 3:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("복도배경3");
		break;
	case 4:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("복도배경4");
		break;
	case 5:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("복도배경5");
		break;
	case 6:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("복도배경6");
		break;
	default:
		this->bgFirst = ImageManager::GetSingleton()->FindImage("복도배경1");
		break;
	}
}

