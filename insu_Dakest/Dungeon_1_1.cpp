#include "Dungeon_1_1.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Character.h"
#include "CharacterManager.h"
#include "H_Crusader.h"
#include "H_BountyHunter.h"

HRESULT Dungeon_1_1::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	Ip_Bg_First = ImageManager::GetSingleton()->AddImage("원거리배경", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	Ip_Bg_Second = ImageManager::GetSingleton()->AddImage("근거리", "resource/dungeon/Stage1/NearBG.BMP", 4320, 480, true, RGB(88, 88, 88));;
	Ip_BG_Passage = ImageManager::GetSingleton()->AddImage("복도배경", "resource/dungeon/Stage1/PassageBG1.BMP", 4320, 480, true, RGB(88, 88, 88));;

	UnderUI = ImageManager::GetSingleton()->AddImage("유아이", "resource/dungeon/UI/D_under_ui.BMP", 1280, 240, false);

	CamPos = 0;
	ptr_Hero1 = new H_Crusader;
	ptr_Hero1->Init();

	CamBuffer = new Image;
	CamBuffer->Init(WINSIZE_X, 600);

	C_MGR = new CharacterManager;
	C_MGR->Init();
	C_MGR->AddHero(new H_Crusader);
	C_MGR->AddHero(new H_BountyHunter);
	C_MGR->AddHero(new H_Crusader);
	C_MGR->AddHero(new H_Crusader);
	return S_OK;
}

void Dungeon_1_1::Release()
{
	SAFE_RELEASE(ptr_Hero1);
	SAFE_RELEASE(C_MGR);
	SAFE_RELEASE(CamBuffer);
}

void Dungeon_1_1::Update()
{
	if (C_MGR)
	{
		C_MGR->Update();
		
	}
	
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
		//test += 0.1f;
		if (CamPos > -WINSIZE_X * 2.5)
		{
			CamPos -= 2;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		//test -= 0.1f;
		if (CamPos < 0)
		{
			CamPos += 1;;

		}
	}
	/*if (ptr_Hero1)
	{
		
		ptr_Hero1->Update();

	}*/
}

void Dungeon_1_1::Render(HDC hdc)
{
	HDC camDC = CamBuffer->GetMemDC();

	if (Ip_Bg_First) {
		Ip_Bg_First->Render(camDC,CamPos/5,0,false);
	}
	if (Ip_Bg_Second) {
		Ip_Bg_Second->Render(camDC,CamPos/2,0,false);
	}
	if (Ip_BG_Passage) {
		Ip_BG_Passage->Render(camDC,CamPos,0,false);
	}
	if (ptr_Hero1)
	{
		//ptr_Hero1->Render(hdc);
	}

	if (C_MGR)
	{
		C_MGR->Render(camDC);
		//C_MGR->Render(camDC);
	}
	CamBuffer->Render2(hdc,WINSIZE_X/2,300,true);

	//CamBuffer->Render2(hdc,C_MGR->GetHeroPos()-WINSIZE_X/2,0,false,1.5);

	if (UnderUI)
	{
		UnderUI->Render(hdc,0,WINSIZE_Y-WINSIZE_Y/3);
	}
}
