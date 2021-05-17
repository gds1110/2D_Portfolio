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

HRESULT Dungeon_1_1::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	
	Ip_Bg_First = ImageManager::GetSingleton()->AddImage("���Ÿ����", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	Ip_Bg_Second = ImageManager::GetSingleton()->AddImage("�ٰŸ�", "resource/dungeon/Stage1/NearBG.BMP", 4320, 480, true, RGB(88, 88, 88));;
	Ip_BG_Passage = ImageManager::GetSingleton()->AddImage("�������", "resource/dungeon/Stage1/PassageBG1.BMP", 4320, 480, true, RGB(88, 88, 88));;

	CamPos = 0;

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

	}
	if (M_MGR)
	{
		M_MGR->Update();

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
