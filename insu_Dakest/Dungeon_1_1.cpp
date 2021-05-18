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
#include "SkillManager.h"
#include "DataManager.h"

HRESULT Dungeon_1_1::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	
	Ip_Bg_First = ImageManager::GetSingleton()->AddImage("원거리배경", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	Ip_Bg_Second = ImageManager::GetSingleton()->AddImage("근거리", "resource/dungeon/Stage1/NearBG.BMP", 4320, 480, true, RGB(88, 88, 88));;
	Ip_BG_Passage = ImageManager::GetSingleton()->AddImage("복도배경", "resource/dungeon/Stage1/PassageBG1.BMP", 4320, 480, true, RGB(88, 88, 88));;

	CamPos = WINSIZE_X/2;

	CamBuffer = new Image;
	CamBuffer->Init(WINSIZE_X,600);

	for (int i = 0; i < 4; i++)
	{
		battlePos[i] = (WINSIZE_X/2) - (i * 100);
	}

	C_MGR = new CharacterManager;
	C_MGR->Init();
	C_MGR->AddCharacter(new H_Leaper,UnitType::HERO);
	C_MGR->AddCharacter(new H_BountyHunter, UnitType::HERO);
	C_MGR->AddCharacter(new H_HighWayMan, UnitType::HERO);
	C_MGR->AddCharacter(new H_Vestel, UnitType::HERO);

	M_MGR = new CharacterManager;
	M_MGR->Init();
	M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);
	M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);
	M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);
	M_MGR->AddCharacter(new skeleton_arbalistar, UnitType::MONSTER);

	


	overUi = new OverUi;
	overUi->Init();

	UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);
	UiDataManager::GetSingleton()->SetSM_MGR(M_MGR);

	UiDataManager::GetSingleton()->SelectChar(C_MGR->GetCharacters()[0]);

	underUI = new UnderUi;
	underUI->Init();

	DM = new DataManager();
	DM->Init(C_MGR, M_MGR, underUI);
	return S_OK;
}

void Dungeon_1_1::Release()
{
	SAFE_RELEASE(C_MGR);
	SAFE_RELEASE(M_MGR);
	SAFE_RELEASE(CamBuffer);
}

void Dungeon_1_1::Update()
{

	if (DM)
	{
		DM->Update();
	}
	if (overUi)
	{
		overUi->Update();
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
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
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		//
		if (CamPos < WINSIZE_X / 2)
		{
			CamPos += 1;;
			if (CamPos - 1 > WINSIZE_X/2)
			{
				CamPos = WINSIZE_X / 2;
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

	CamBuffer->Render2(hdc, WINSIZE_X / 2, 300, true);


	if (C_MGR)
	{
		C_MGR->Render(hdc);
		//C_MGR->Render(camDC);
	}
	if (CamPos < -1500) {
		if (M_MGR)
		{
			M_MGR->Render(hdc);
		}
	}
	underUI->Render(hdc);
	overUi->Render(hdc);
	Rectangle(hdc, CamPos - 25, 50 - 25, CamPos + 25, 50 + 50);
	// 인사
	// 마우스 좌표
	wsprintf(szText, "campos : %d",CamPos);
	TextOut(hdc, WINSIZE_X/2, 100, szText, strlen(szText));
}
/*
https://m.blog.naver.com/flqpfnrm/221279669215

https://gall.dcinside.com/mgallery/board/view/?id=darkest&no=175483
전투 구현할때 참고

*/