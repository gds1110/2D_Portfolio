#include "Dungeon_1_1.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Character.h"
#include "CharacterManager.h"
#include "MonsterManager.h"
#include "H_Crusader.h"
#include "H_BountyHunter.h"
#include "H_Leaper.h"
#include "H_HighWayMan.h"
#include "H_Vestel.h"
#include "UnderUi.h"
#include "OverUi.h"
#include "skeleton_arbalistar.h"
#include "SkillManager.h"

HRESULT Dungeon_1_1::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	
	Ip_Bg_First = ImageManager::GetSingleton()->AddImage("원거리배경", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	Ip_Bg_Second = ImageManager::GetSingleton()->AddImage("근거리", "resource/dungeon/Stage1/NearBG.BMP", 4320, 480, true, RGB(88, 88, 88));;
	Ip_BG_Passage = ImageManager::GetSingleton()->AddImage("복도배경", "resource/dungeon/Stage1/PassageBG1.BMP", 4320, 480, true, RGB(88, 88, 88));;

	CamPos = 0;

	CamBuffer = new Image;
	CamBuffer->Init(WINSIZE_X,600);

	for (int i = 0; i < 4; i++)
	{
		battlePos[i] = (WINSIZE_X/2) - (i * 100);
	}

	C_MGR = new CharacterManager;
	C_MGR->Init();
	C_MGR->AddHero(new H_Leaper);
	C_MGR->AddHero(new H_BountyHunter);
	C_MGR->AddHero(new H_HighWayMan);
	C_MGR->AddHero(new H_Vestel);

	M_MGR = new MonsterManager;
	M_MGR->Init();
	M_MGR->AddMonster(new skeleton_arbalistar);
	M_MGR->AddMonster(new skeleton_arbalistar);
	M_MGR->AddMonster(new skeleton_arbalistar);
	M_MGR->AddMonster(new skeleton_arbalistar);

	

	overUi = new OverUi;
	overUi->Init();


	UiDataManager::GetSingleton()->SelectChar(C_MGR->GetVHeros()[0]);

	underUI = new UnderUi;
	underUI->Init();

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
	if (C_MGR)
	{
		C_MGR->Update();
		UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);

	}
	if (M_MGR)
	{
		M_MGR->Update();
		UiDataManager::GetSingleton()->SetSM_MGR(M_MGR);

	}


	if (underUI)
	{
		underUI->Update();
	}
	if (overUi)
	{
		overUi->Update();
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
		//
		if (CamPos > -WINSIZE_X * 2.3)
		{
			CamPos -= 2;
			if ((CamPos - 2) < -WINSIZE_X * 2.3)
			{
				CamPos = -WINSIZE_X * 2.3;
			}
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		//
		if (CamPos < 0)
		{
			CamPos += 1;;
			if (CamPos - 1 > 0)
			{
				CamPos = 0;
			}

		}
	}


}

void Dungeon_1_1::Render(HDC hdc)
{
	HDC camDC = CamBuffer->GetMemDC();

	if (Ip_Bg_First) {
		Ip_Bg_First->Render(camDC, CamPos / 5, 0, false);
	}
	if (Ip_Bg_Second) {
		Ip_Bg_Second->Render(camDC, CamPos / 2, 0, false);
	}
	if (Ip_BG_Passage) {
		Ip_BG_Passage->Render(camDC, CamPos, 0, false);
	}

	CamBuffer->Render2(hdc, WINSIZE_X / 2, 300, true);


	if (C_MGR)
	{
		C_MGR->Render(hdc);
		//C_MGR->Render(camDC);
	}
	if (M_MGR)
	{
		M_MGR->Render(hdc);
	}

	underUI->Render(hdc);
	overUi->Render(hdc);

}
