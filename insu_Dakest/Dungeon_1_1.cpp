#include "Dungeon_1_1.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Character.h"
#include "CharacterManager.h"
#include "H_Crusader.h"
#include "H_BountyHunter.h"
#include "UnderUi.h"
#include "OverUi.h"
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
	C_MGR->AddHero(new H_Crusader);
	C_MGR->AddHero(new H_BountyHunter);
	//C_MGR->AddHero(new H_Crusader);
	//C_MGR->AddHero(new H_Crusader);
	
	overUi = new OverUi;
	overUi->Init();

	underUI = new UnderUi;
	underUI->Init();
	
	UiDataManager::GetSingleton()->SelectChar(C_MGR->GetVHeros()[0]);

	return S_OK;
}

void Dungeon_1_1::Release()
{
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

	if (underUI)
	{
		underUI->Update();
	}
	if (overUi)
	{
		overUi->Update();
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

	CamBuffer->Render2(hdc,WINSIZE_X/2,300,true);


	if (C_MGR)
	{
		C_MGR->Render(hdc);
		//C_MGR->Render(camDC);
	}
	underUI->Render(hdc);
	overUi->Render(hdc);
	//CamBuffer->Render2(hdc,C_MGR->GetHeroPos()-WINSIZE_X/2,0,false,1.5);


	//확대되서 움직여야할곳 표시
	//for (int i = 0; i < 4; i++)
	//{
	//	Rectangle(hdc, battlePos[i] - 50, 400, battlePos[i], 450);
	//}
	
}
