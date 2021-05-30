#include "Dungeon_1_1.h"
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

HRESULT Dungeon_1_1::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	
	Ip_Bg_First = ImageManager::GetSingleton()->AddImage("���Ÿ����", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	Ip_Bg_Second = ImageManager::GetSingleton()->AddImage("�ٰŸ�", "resource/dungeon/Stage1/NearBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	Ip_BG_Passage = ImageManager::GetSingleton()->AddImage("�������1", "resource/dungeon/Stage1/PassageBG1.BMP", 2900, 480, true, RGB(88, 88, 88));

	CamPos = WINSIZE_X/2;

	CamBuffer = new Image;
	//CamBuffer->Init(WINSIZE_X,600);
	CamBuffer->Init(1920,720);

	for (int i = 0; i < 4; i++)
	{
		battlePos[i] = (WINSIZE_X/2) - (i * 100);
	}

	//C_MGR = new CharacterManager;
	//C_MGR->Init();
	//C_MGR->AddCharacter(new H_BountyHunter, UnitType::HERO);
	//C_MGR->AddCharacter(new H_Leaper,UnitType::HERO);
	//C_MGR->AddCharacter(new H_HighWayMan, UnitType::HERO);
	//C_MGR->AddCharacter(new H_Vestel, UnitType::HERO);

	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();

	M_MGR = new CharacterManager;
	M_MGR->Init();
	M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);
	M_MGR->AddCharacter(new skeleton_captain, UnitType::MONSTER);
	//M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);
	//M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);

	


	overUi = new OverUi;
	overUi->Init();

	//UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);
	//UiDataManager::GetSingleton()->SetSM_MGR(M_MGR);

	UiDataManager::GetSingleton()->SelectChar(C_MGR->GetCharacters()[0]);
	BattleStage = false;
	underUI = new UnderUi;
	underUI->Init();

	DM = new DataManager();
	DM->Init(C_MGR, M_MGR, underUI);
	return S_OK;
}

HRESULT Dungeon_1_1::DungoenInit(Tile* flowTile)
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	//SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	thisTile = flowTile;
	//CamPos = 1920 / 2;
	CamPos = 0;
	if (thisTile->GetType() == TileType::Room) {
		CamPos = 900;
	}
	else
	{
		CamPos = WINSIZE_X / 2;
	}

	CamBuffer = new Image;
	CamBuffer->Init(1920, 720);

	Ip_Bg_First = ImageManager::GetSingleton()->FindImage("���Ÿ����");
	Ip_Bg_Second = ImageManager::GetSingleton()->FindImage("�ٰŸ�");
	if (thisTile->GetType() == TileType::Room) {
		if (thisTile->GetIsStarted())
		{
			Ip_BG_Passage = ImageManager::GetSingleton()->FindImage("�����Ա�");

		}
		else
		{
			Ip_BG_Passage = ImageManager::GetSingleton()->FindImage("�漼Ʈ");
		}
	}
	else if (thisTile->GetType() == TileType::Path)
	{
		Ip_BG_Passage = ImageManager::GetSingleton()->FindImage("�漼Ʈ");

	}
	for (int i = 0; i < 4; i++)
	{
		battlePos[i] = (WINSIZE_X / 2) - (i * 100);
	}

	//C_MGR = new CharacterManager;
	//C_MGR->Init();
	//C_MGR->AddCharacter(new H_BountyHunter, UnitType::HERO);
	//C_MGR->AddCharacter(new H_Leaper,UnitType::HERO);
	//C_MGR->AddCharacter(new H_HighWayMan, UnitType::HERO);
	//C_MGR->AddCharacter(new H_Vestel, UnitType::HERO);

	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();

	M_MGR = new CharacterManager;
	M_MGR->Init();
	//if (thistile.getisenemyed)
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		if (thisTile->GetTileinfo().enemyArr[i]!= NULL)
	//		{
	//			M_MGR->AddMonster(thisTile->GetTileinfo().enemyArr[i]);
	//		}
	//	}
	//}

	

	//if (flowTile->GetTileinfo()->isEnemyed == true) {
	//	for (int i = 0; i < 4; i++)
	//	{
	//		if (flowTile->GetEnemyArr()[i] != NULL)
	//		{
	//			M_MGR->AddMonster(flowTile->GetEnemyArr()[i]);
	//		}
	//	}
	//}
	/*M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);
	M_MGR->AddCharacter(new skeleton_captain, UnitType::MONSTER);
	M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);
	M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);*/




	overUi = new OverUi;
	overUi->Init();

	//UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);
	//UiDataManager::GetSingleton()->SetSM_MGR(M_MGR);

	UiDataManager::GetSingleton()->SelectChar(C_MGR->GetCharacters()[0]);
	BattleStage = false;
	underUI = new UnderUi;
	underUI->Init();

	DM = new DataManager();
	DM->Init(C_MGR, M_MGR, underUI);
	return S_OK;
}

void Dungeon_1_1::Release()
{
	SAFE_RELEASE(overUi);
	SAFE_RELEASE(underUI);
	SAFE_RELEASE(C_MGR);
	SAFE_RELEASE(M_MGR);
	SAFE_RELEASE(CamBuffer);
	SAFE_RELEASE(DM);
}

void Dungeon_1_1::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
	{
		SceneManager::GetSingleton()->ChangeScene("�ʻ���");
		return;
	}

	if (DM)
	{
		DM->Update();
		//DM->SetCampos(CamPos);
	}
	if (overUi)
	{
		overUi->Update();
	}
	if (thisTile->GetType() != TileType::Room) {
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) || KeyManager::GetSingleton()->IsStayKeyDown('D')) {
			//
			if (CamPos > -WINSIZE_X * 2)
			{
				CamPos -= 2;
				if ((CamPos - 2) < -WINSIZE_X * 2)
				{
					CamPos = -WINSIZE_X * 2;
				}
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) || KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			//
			if (CamPos < WINSIZE_X / 2)
			{
				CamPos += 1;;
				if (CamPos - 1 > WINSIZE_X / 2)
				{
					CamPos = WINSIZE_X / 2;
				}

			}
		}
	}

}

void Dungeon_1_1::Render(HDC hdc)
{
	HDC camDC = CamBuffer->GetMemDC();

	if (Ip_Bg_First) {
		Ip_Bg_First->Render(camDC, CamPos / 5 , 0, false);
	}
	if (Ip_Bg_Second) {
		Ip_Bg_Second->Render(camDC, CamPos / 2, 0, false);
	}
	if (Ip_BG_Passage) {
		Ip_BG_Passage->Render(camDC, CamPos-WINSIZE_X/2, 0, false);
	}

	CamBuffer->Render3(hdc, WINSIZE_X / 2, 350, true);
	//CamBuffer->Render2(hdc, WINSIZE_X / 2, 350, true);


	if (CamPos < 300) {
		if (M_MGR)
		{
			overUi->SetBattle(true);
			M_MGR->Render(hdc);
		}
	}
	if (C_MGR)
	{

		C_MGR->Render(hdc);
		
		//C_MGR->Render(camDC);
	}
	overUi->Render(hdc);
	underUI->Render(hdc);
	//Rectangle(hdc, CamPos - 25, 50 - 25, CamPos + 25, 50 + 50);
	// �λ�
	// ���콺 ��ǥ
	wsprintf(szText, "campos : %d",CamPos);
	TextOut(hdc, WINSIZE_X/2, 100, szText, strlen(szText));

	wsprintf(szText, "campos : %d", UiDataManager::GetSingleton()->GetTile()->getindex());
	TextOut(hdc, WINSIZE_X / 2, 300, szText, strlen(szText));

	
}
/*
https://m.blog.naver.com/flqpfnrm/221279669215

https://gall.dcinside.com/mgallery/board/view/?id=darkest&no=175483
���� �����Ҷ� ����

*/