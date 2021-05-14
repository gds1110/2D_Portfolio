#include "UiDataManager.h"
#include "Character.h"
#include "Skill.h"
#include "CharacterManager.h"
#include "SkillManager.h"
#include "CommonFunction.h"
HRESULT UiDataManager::Init()
{
	selectedChr = nullptr;
	selctedSkill = nullptr;
	SS_MGR = nullptr;
	SC_MGR = nullptr;
	return S_OK;
}

void UiDataManager::Release()
{

}

void UiDataManager::Update()
{
	/*if (SS_MGR) {
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{

			for (int i = 0; i < SS_MGR->GetSkillSlot().size(); i++)
			{
				if (PointInRect(g_ptMouse, SS_MGR->GetSkillSlot()[i]->GetRect())) {

					selctedSkill = (SS_MGR->GetSkillSlot()[i]);
				}
			}
		}

	}*/
}

