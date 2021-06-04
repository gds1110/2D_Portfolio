#include "UiDataManager.h"
#include "Character.h"
#include "Skill.h"
#include "CharacterManager.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "H_Crusader.h"
#include "H_BountyHunter.h"
#include "H_Leaper.h"
#include "H_HighWayMan.h"
#include "H_Vestel.h"
HRESULT UiDataManager::Init()
{
	selectedChr = nullptr;
	selctedSkill = nullptr;
	SS_MGR = nullptr;
	SC_MGR = nullptr;
	selCheck = false;
	map = nullptr;
	Minimap = nullptr;
	prevScene = SceneInfo::NONESCENE;
	selScene = SceneInfo::NONESCENE;
	SC_MGR = new CharacterManager;
	SC_MGR->Init();
	//SC_MGR->AddCharacter(new H_BountyHunter, UnitType::HERO);
	//SC_MGR->AddCharacter(new H_Leaper, UnitType::HERO);
	//SC_MGR->AddCharacter(new H_HighWayMan, UnitType::HERO);
	//SC_MGR->AddCharacter(new H_Vestel, UnitType::HERO);

	return S_OK;
}

void UiDataManager::Release()
{
	SAFE_RELEASE(SC_MGR);

	if (Minimap)
	{
		//SAFE_RELEASE(Minimap);


	}
}

void UiDataManager::Update()
{
	/*if (S
	
	) {
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

void UiDataManager::SetDestTile(Tile* tile)
{
	{
		this->destTile = tile;
	}
}

void UiDataManager::AddTarget(Character* target)
{
	targetChr.push_back(target);

}

