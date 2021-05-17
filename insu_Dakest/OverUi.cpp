#include "OverUi.h"
#include "Image.h"
#include "Character.h"
#include "CommonFunction.h"
#include "CharacterManager.h"
#include "skill.h"

HRESULT OverUi::Init()
{
	selecetedIcon = ImageManager::GetSingleton()->AddImage("선택아이콘", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
	targetIcon = ImageManager::GetSingleton()->AddImage("타겟아이콘", "resource/sharedUi/target.BMP", 197, 412, 1, 2, true, RGB(88, 88, 88));
	sIconCurrFrame = 0;
	eltimes = 0;
	ePos = 0;
	BLENDFUNCTION* blendFunc = targetIcon->GetBlendFunc();
	blendFunc->SourceConstantAlpha = 150;
	return S_OK;
}

void OverUi::Release()
{
}

void OverUi::Update()
{
	vector<Character*> temp_vm = UiDataManager::GetSingleton()->GetSM_MGR()->GetCharacters();
	BLENDFUNCTION* blendFunc = targetIcon->GetBlendFunc();

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
				
			if (UiDataManager::GetSingleton()->GetSelectedSkill()->GetSkillInfo().targetRank.x <= temp_vm[i]->GetIndex()&& UiDataManager::GetSingleton()->GetSelectedSkill()->GetSkillInfo().targetRank.y > temp_vm[i]->GetIndex())
			{
				if (PointInRect(g_ptMouse, temp_vm[i]->GetRect()))
				{
					blendFunc->SourceConstantAlpha = 255;
				}
				else
				{
					blendFunc->SourceConstantAlpha = 150;

				}
			}
		}

	}
	else
	{
		ePos = -200;
	}
}

void OverUi::Render(HDC hdc)
{
	selecetedIcon->FrameRender(hdc, UiDataManager::GetSingleton()->GetSelectedChar()->GetPosx()+50, 430, 0, sIconCurrFrame, true,0.8);
	if (UiDataManager::GetSingleton()->GetselCheck() == true) {
		for (int i = UiDataManager::GetSingleton()->GetSelectedSkill()->GetSkillInfo().targetRank.x; i <= UiDataManager::GetSingleton()->GetSelectedSkill()->GetSkillInfo().targetRank.y; i++) {
			targetIcon->AlphaFrameRender(hdc, (WINSIZE_X / 2 + 120) + (i * 150), 500, 0, 0, true, 0.8);

		}
	}
}
