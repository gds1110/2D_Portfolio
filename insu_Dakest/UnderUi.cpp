#include "UnderUi.h"
#include "Image.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"

HRESULT UnderUi::Init()
{
	underUi = ImageManager::GetSingleton()->AddImage("유아이", "resource/dungeon/UI/D_under_ui2.BMP", 1280, 240, false);
	underIcon = nullptr;
	selSkillIcon = ImageManager::GetSingleton()->AddImage("스킬선택", "resource/sharedUi/sel_skill.BMP",60,60,true,RGB(88,88,88));
	selSkill = nullptr;
	selSkillmgr = nullptr;
	c_mgr = nullptr;
	return S_OK;
}

void UnderUi::Release()
{

}

void UnderUi::Update()
{

	selChr = UiDataManager::GetSingleton()->GetSelectedChar();
	c_mgr=UiDataManager::GetSingleton()->GetSC_MGR();


	if (selChr)
	{
		iconKey = selChr->GetClassArr()[selChr->GetClass()] + "아이콘";
		underIcon = ImageManager::GetSingleton()->FindImage(iconKey);
		selSkillmgr = selChr->getSkillMgr();
		//selChr->getSkillMgr()->Update();

		/*iconKey = UiDataManager::GetSingleton()->GetSelectedChar()->GetClassArr()[UiDataManager::GetSingleton()->GetSelectedChar()->GetClass()] + "아이콘";
		underIcon = ImageManager::GetSingleton()->FindImage(iconKey);*/
		
	}



	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{

		
		for (int i = 0; i < c_mgr->GetVHeros().size(); i++)
		{
			if (PointInRect(g_ptMouse, c_mgr->GetVHeros()[i]->GetRect())) {
				UiDataManager::GetSingleton()->SelectChar(c_mgr->GetVHeros()[i]);
				if (selChr != c_mgr->GetVHeros()[i])
				{

					selSkill = nullptr;
				}
			}
		}
		
		for (int i = 0; i < selSkillmgr->GetSkillSlot().size(); i++)
		{
			if (PointInRect(g_ptMouse, selSkillmgr->GetSkillSlot()[i]->GetRect())) {

				UiDataManager::GetSingleton()->selectSkill(selSkillmgr->GetSkillSlot()[i]);
				selSkill = UiDataManager::GetSingleton()->GetSelectedSkill();

			}
		}

	}

	//if (selSkill)
	//{
	//	
	//}
}

void UnderUi::Render(HDC hdc)
{
	underUi->Render(hdc, 0, WINSIZE_Y - WINSIZE_Y / 3);
	if (underIcon) {
		underIcon->Render2(hdc, 210, WINSIZE_Y - WINSIZE_Y / 3 + 50, true, 0.5);
	}
	if (selChr) {
		
		selSkillmgr->Render(hdc);
			//selChr->getSkillMgr()->Render(hdc);
		
	}
	if (selSkill)
	{
		selSkillIcon->Render(hdc, selSkill->GetPos().x, selSkill->GetPos().y, true);
	}
}
