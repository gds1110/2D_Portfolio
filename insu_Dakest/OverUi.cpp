#include "OverUi.h"
#include "Image.h"
#include "Character.h"
#include "CommonFunction.h"
#include "MonsterManager.h"

HRESULT OverUi::Init()
{
	selecetedIcon = ImageManager::GetSingleton()->AddImage("선택아이콘", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
	targetIcon = ImageManager::GetSingleton()->AddImage("타겟아이콘", "resource/sharedUi/target.BMP", 246, 412, 1, 2, true, RGB(88, 88, 88));
	sIconCurrFrame = 0;
	eltimes = 0;
	ePos = 0;
	return S_OK;
}

void OverUi::Release()
{
}

void OverUi::Update()
{
	vector<Character*> temp_vm = UiDataManager::GetSingleton()->GetSM_MGR()->GetVMonsters();

	eltimes += TimerManager::GetSingleton()->GetElapsedTime();
	if (eltimes > 0.3)
	{
		sIconCurrFrame++;
		if (sIconCurrFrame > 1) {
			sIconCurrFrame = 0;
		}
		eltimes = 0;
	}
	if (UiDataManager::GetSingleton()->GetselCheck())
	{
		for (int i = 0; i < temp_vm.size(); i++)
		{
			if (PointInRect(g_ptMouse, temp_vm[i]->GetRect()))
			{
				ePos = temp_vm[i]->GetPosx();
			}
		}

	}
}

void OverUi::Render(HDC hdc)
{
	selecetedIcon->FrameRender(hdc, UiDataManager::GetSingleton()->GetSelectedChar()->GetPosx()+50, 430, 0, sIconCurrFrame, true,0.8);
	if (UiDataManager::GetSingleton()->GetselCheck()==true) {
		targetIcon->FrameRender(hdc, ePos + 50, 200, 0, 0, true);
	}
}
