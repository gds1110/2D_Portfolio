#include "Home.h"
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

HRESULT Home::Init()
{
	bg = ImageManager::GetSingleton()->FindImage("시작상점");
	mouseIcon = nullptr;
	rosterList = new CharacterManager();
	rosterList->Init();
	rosterList->AddCharacter2(new H_Crusader,0);
	rosterList->AddCharacter2(new H_BountyHunter,1);
	rosterList->AddCharacter2(new H_Crusader,2);
	rosterList->AddCharacter2(new H_BountyHunter,3);
	rosterList->AddCharacter2(new H_HighWayMan,4);
	rosterList->AddCharacter2(new H_Vestel,5);
	rosterList->AddCharacter2(new H_Leaper,6);
	startButton = ImageManager::GetSingleton()->FindImage("출발버튼");
	for (int i = 0; i < 4; i++)
	{
		heroSlot[i].hero = nullptr;
		heroSlot[i].HeroNum = -1;
		heroSlot[i].icon = nullptr;
		heroSlot[i].size = 60;
		//500 580
		heroSlot[i].pos.x = 505 + i * 60;
		heroSlot[i].pos.y = 585;
		SetRect(&heroSlot[i].rc, heroSlot[i].pos.x , heroSlot[i].pos.y , heroSlot[i].pos.x + heroSlot[i].size, heroSlot[i].pos.y + heroSlot[i].size);
		heroSlot[i].isSetting = false;
	}
	SetRect(&divideRc, 0, 0, 1000, 560);
	SetRect(&startRC, WINSIZE_X / 2-150, 650, WINSIZE_X/2 + 120, 700);
	selectNum = -1;
	buttonframe = 0;
	return S_OK;
}

void Home::Release()
{
}

void Home::Update()
{
	if (PtInRect(&divideRc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON)) {
			if (mouseIcon != nullptr && selectNum != -1) {

				mouseIcon = nullptr;
				selectNum = -1;
			}
		}
	}
	else {
		if (PtInRect(&startRC, g_ptMouse))
		{
			buttonframe = 1;
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				if (ready == true)
				{
					UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[3].HeroNum]);
					UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[2].HeroNum]);
					UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[1].HeroNum]);
					UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[0].HeroNum]);

					SceneManager::GetSingleton()->ChangeScene("통로");

				}
			}
		}
		else if (!PtInRect(&startRC, g_ptMouse))
		{
			buttonframe = 0;
		}

		for (int i = 0; i < rosterList->GetCharacters().size(); i++)
		{
			rosterList->GetCharacters()[i]->RosterUpdate();

			RECT tempRC = rosterList->GetCharacters()[i]->GetIconRC();
			if (PtInRect(&tempRC, g_ptMouse))
			{
				rosterList->GetCharacters()[i]->SetIconMouseOver(true);

			}
			else
			{
				rosterList->GetCharacters()[i]->SetIconMouseOver(false);

			}



		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&heroSlot[i].rc, g_ptMouse) && mouseIcon != nullptr)
				{

					heroSlot[i].icon = mouseIcon;
					heroSlot[i].HeroNum = selectNum;
					mouseIcon = nullptr;
					selectNum = -1;
				}
			}
		}


		for (int i = 0; i < rosterList->GetCharacters().size(); i++)
		{
			RECT tempRC = rosterList->GetCharacters()[i]->GetIconRC();
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON) && PtInRect(&tempRC, g_ptMouse) && rosterList->GetCharacters()[i]->GetIconIsSelecetd() == false)
			{
				mouseIcon = rosterList->GetCharacters()[i]->GetIconImage();
				selectNum = rosterList->GetCharacters()[i]->GetIndex();
			}
			else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
			{
				mouseIcon = nullptr;
				selectNum = -1;
			}
			/*if (rosterList->GetCharacters()[i]->GetIconMouseOver() == true)
			{
			}*/


		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < rosterList->GetCharacters().size(); j++)
			{
				if (heroSlot[i].HeroNum == rosterList->GetCharacters()[j]->GetIndex())
				{
					rosterList->GetCharacters()[j]->SetIconIsSelecetd(true);

				}

			}
			if (heroSlot[i].HeroNum == -1)
			{
				ready = false;
			}
			else
			{
				ready = true;
			}
		}
	}
}

void Home::Render(HDC hdc)
{
	bg->Render(hdc);
	for (int i = 0; i < 4; i++)
	{
		//Rectangle(hdc, heroSlot[i].rc.left, heroSlot[i].rc.top, heroSlot[i].rc.right, heroSlot[i].rc.bottom);
		if (heroSlot[i].icon != nullptr)
		{
			heroSlot[i].icon->Render(hdc, heroSlot[i].pos.x, heroSlot[i].pos.y);
		}
	}
	

	for (int i = 0; i < rosterList->GetCharacters().size(); i++)
	{
		rosterList->GetCharacters()[i]->RosterRender(hdc);
	}

	if (mouseIcon != nullptr)
	{
		mouseIcon->Render(hdc, g_ptMouse.x, g_ptMouse.y);
	}
	//Rectangle(hdc, startRC.left, startRC.top, startRC.right, startRC.bottom);
	if (startButton != nullptr)
	{
		if (buttonframe == 0) {
			startButton->FrameRender(hdc, WINSIZE_X / 2 - 125, 652, 0, buttonframe);
		}
		else if (buttonframe == 1)
		{
			startButton->FrameRender(hdc, WINSIZE_X / 2 - 125, 650, 0, buttonframe);

		}
	}
	//Rectangle(hdc, divideRc.left, divideRc.top, divideRc.right, divideRc.bottom);
	wsprintf(szText, "campos : %d", ready);
	TextOut(hdc, WINSIZE_X / 2, 100, szText, strlen(szText));
}
