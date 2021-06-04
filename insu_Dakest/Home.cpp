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
#include "Inventory.h"
#include "ItemObject.h"

HRESULT Home::Init()
{
	bg = ImageManager::GetSingleton()->FindImage("���ۻ���");
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
	rosterList->AddCharacter2(new H_Leaper,7);
	startButton = ImageManager::GetSingleton()->FindImage("��߹�ư");
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
	myInven = new Inventory();
	myInven->Init();

	item1 = new ItemObject();
	item2 = new ItemObject();
	item3 = new ItemObject();
	item1->Init(ItemObject::ITEMTYPE::DECODING);
	item2->Init(ItemObject::ITEMTYPE::BANDAGE);
	item3->Init(ItemObject::ITEMTYPE::TORCH);
	item1->SetItemNum(8);
	item2->SetItemNum(8);
	item3->SetItemNum(8);
	item1->SetPos({ WINSIZE_X / 2,100 });
	item2->SetPos({ WINSIZE_X / 2+100,100 });
	item3->SetPos({ WINSIZE_X / 2+200,100 });

	UiDataManager::GetSingleton()->SetIShome(true);
	return S_OK;
}

void Home::Release()
{
	//SAFE_RELEASE(rosterList);  //�������Ҽ���
}

void Home::Update()
{
		item1->Update();
		item2->Update();
		item3->Update();
	if (myInven) {
		myInven->Update();
		myInven->SetPos({ 530, 340 });
	}




	if (PtInRect(&divideRc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON)) {
			if (mouseIcon != nullptr && selectNum != -1) {

				mouseIcon = nullptr;
				selectNum = -1;
			}

			RECT rc1 = item1->GetRC();
			RECT rc2 = item2->GetRC();
			RECT rc3 = item3->GetRC();
			if (PtInRect(&rc1, g_ptMouse))
			{
				if (item1->GetItemNum().x - 1 >= 0)
				{
					myInven->AddItem((*item1));
					item1->SetItemNum(item1->GetItemNum().x - 1);
				}
			}
			if (PtInRect(&rc2, g_ptMouse))
			{
				if (item2->GetItemNum().x - 1 >= 0)
				{
					myInven->AddItem((*item2));
					item2->SetItemNum(item2->GetItemNum().x - 1);

				}
			}
			if (PtInRect(&rc3, g_ptMouse))
			{
				if (item3->GetItemNum().x - 1 >= 0)
				{
					myInven->AddItem((*item3));
					item3->SetItemNum(item3->GetItemNum().x - 1);

				}
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
					if (heroSlot[3].HeroNum > -1) {
						UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[3].HeroNum]);
					}
					if (heroSlot[2].HeroNum > -1) {

						UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[2].HeroNum]);
					}
					if (heroSlot[1].HeroNum > -1) {
						UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[1].HeroNum]);
					}
					if (heroSlot[0].HeroNum > -1) {

						UiDataManager::GetSingleton()->GetSC_MGR()->AddCharacter(rosterList->GetCharacters()[heroSlot[0].HeroNum]);
					}
					UiDataManager::GetSingleton()->SetSceneInfo(UiDataManager::SceneInfo::TOWN, UiDataManager::SceneInfo::MAPGEN);
					UiDataManager::GetSingleton()->SetIShome(false);
					UiDataManager::GetSingleton()->SetInven(myInven);
					SceneManager::GetSingleton()->ChangeScene("���������");
					return;

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

		if(KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON)){
			for (int i = 0; i < rosterList->GetCharacters().size(); i++)
			{
				RECT tempRC = rosterList->GetCharacters()[i]->GetIconRC();
				if (PtInRect(&tempRC, g_ptMouse)) {
					if (PtInRect(&tempRC, g_ptMouse) && rosterList->GetCharacters()[i]->GetIconIsSelecetd() == false)
					{
						if (mouseIcon == nullptr) {
							mouseIcon = rosterList->GetCharacters()[i]->GetIconImage();
							selectNum = rosterList->GetCharacters()[i]->GetIndex();
						}
					}

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
			if (heroSlot[i].HeroNum >-1)
			{
				ready = true;
			}
		}
	}
}

void Home::Render(HDC hdc)
{
	bg->Render(hdc);

	item1->Render(hdc);
	item2->Render(hdc);
	item3->Render(hdc);


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

	
	//Rectangle(hdc, startRC.left, startRC.top, startRC.right, startRC.bottom);

	for (int i = 0; i < rosterList->GetCharacters().size(); i++)
	{
		rosterList->GetCharacters()[i]->RosterRender(hdc);
	}	

	myInven->Render(hdc);

	for (int i = 0; i < 4; i++)
	{
		//Rectangle(hdc, heroSlot[i].rc.left, heroSlot[i].rc.top, heroSlot[i].rc.right, heroSlot[i].rc.bottom);
		if (heroSlot[i].icon != nullptr)
		{
			heroSlot[i].icon->Render(hdc, heroSlot[i].pos.x, heroSlot[i].pos.y);
		}
	}

if (mouseIcon != nullptr)
	{
		mouseIcon->Render(hdc, g_ptMouse.x, g_ptMouse.y);
	}

	////Rectangle(hdc, divideRc.left, divideRc.top, divideRc.right, divideRc.bottom);
	//wsprintf(szText, "campos : %d", ready);
	//TextOut(hdc, WINSIZE_X / 2, 100, szText, strlen(szText));
}
