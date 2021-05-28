#include "DataManager.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "UnderUI.h"
HRESULT DataManager::Init()
{
	
	return S_OK;
}

HRESULT DataManager::Init(CharacterManager* C_MGR, CharacterManager* M_MGR, UnderUi* ui)
{
    ImageManager::GetSingleton()->AddImage("선택아이콘", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("타겟아이콘", "resource/sharedUi/target.BMP", 197, 412, 1, 2, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("힐아이콘", "resource/sharedUi/target_h.BMP", 175, 206, 1, 1, true, RGB(88, 88, 88));
	camPos = 0;
	this->C_MGR = C_MGR;
	this->M_MGR = M_MGR;
	this->underUI = ui;

	/*C_MGR->GetCharacters()[1]->getSkillMgr()->AddSkill(new CombatAttack);*/
	BattleStage = false;
	cursorChar = nullptr;
	targeton = false;
	return S_OK;
}

void DataManager::Release()
{/*
	SAFE_RELEASE(C_MGR);
	SAFE_RELEASE(M_MGR);*/
}

void DataManager::Update()
{
	if (selectedChr) {
		S_MGR = selectedChr->getSkillMgr();
	}
	if (selctedSkill)
	{
		if (BattleStage) {
			if (selctedSkill->GetSkillType() == SKILLTYPE::COMBATSKILL || selctedSkill->GetSkillType() == SKILLTYPE::ARANGESKILL)
			{
				for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
				{
					M_MGR->GetCharacters()[i]->SetFixed(false);

					if (selctedSkill->GetSkillInfo().targetRank.x <= M_MGR->GetCharacters()[i]->GetIndex()
						&& selctedSkill->GetSkillInfo().targetRank.y >= M_MGR->GetCharacters()[i]->GetIndex())
					{
						M_MGR->GetCharacters()[i]->SetTargeted(true);


					}
					else
					{
						M_MGR->GetCharacters()[i]->SetTargeted(false);
					}
				}

				for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
				{


					if (PointInRect(g_ptMouse, M_MGR->GetCharacters()[i]->GetRect())) {
						if (M_MGR->GetCharacters()[i]->GetTargeted() == true && selctedSkill->GetSkillInfo().range > 1)
						{
							for (int j = 0; j < selctedSkill->GetSkillInfo().range; j++)
							{

								if (M_MGR->GetCharacters()[i]->GetIndex() + j >= 4)
								{
									break;
								}
								else {
									if (i + j >= M_MGR->GetCharacters().size())
									{

									}
									else if (M_MGR->GetCharacters()[(i + j)])
									{
										/*if (i + j < selctedSkill->GetSkillInfo().range) {
											M_MGR->GetCharacters()[(i + j)]->SetFixed(true);
										}*/
										if (M_MGR->GetCharacters()[(i + j)]->GetTargeted() == true) {
											M_MGR->GetCharacters()[(i + j)]->SetFixed(true);
										}
										targeton = true;


									}

								}

							}
						}
						else if (M_MGR->GetCharacters()[i]->GetTargeted() == true)
						{
							M_MGR->GetCharacters()[i]->SetFixed(true);
							targeton = true;

						}
						else
						{
							targeton = false;
						}
					}

				}

			}
		}

	}
	
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
        {
            if (PointInRect(g_ptMouse, C_MGR->GetCharacters()[i]->GetRect()))
            {
              
				if (selectedChr) {
					selectedChr->SetSelected(false);
				}
				SelectChar(C_MGR->GetCharacters()[i]);
            
				selectedChr->SetSelected(true);
				underUI->SetSelChr(C_MGR->GetCharacters()[i]);
			
                if (!selectedChr)
                {
					selctedSkill = nullptr;
                }
            }
        }
		if (S_MGR)
		{
			for (int i = 0; i < S_MGR->GetSkillSlot().size(); i++)
			{
				if (PointInRect(g_ptMouse, S_MGR->GetSkillSlot()[i]->GetRect())) {
					if (S_MGR->GetSkillSlot()[i]->GetSkillState() == Skill::SkillState::ON) {
						underUI->setSelSkill(S_MGR->GetSkillSlot()[i]);
						selectSkill(S_MGR->GetSkillSlot()[i]);
					}
				}
			}
		}

		if (selectedChr && selctedSkill)
		{
				for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
				{
					if (M_MGR->GetCharacters()[i]->GetFixed() == true)
					{
						selctedSkill->run(0, M_MGR->GetCharacters()[i]);
						M_MGR->GetCharacters()[i]->SetPos(WINSIZE_X / 2 + 100 * i);
						selectedChr->SetPos(WINSIZE_X / 2);
						//selectedChr->SetCurrState(State::SKILL1);
					}
				}

			
		}
    }
	


	if (C_MGR)
	{
		C_MGR->Update();
		if (camPos < 300)
		{
			for (int i = 0; i < 4; i++)
			{
				C_MGR->GetCharacters()[i]->SetCurrState(State::COMBAT);
			}
		}

	}
	if (M_MGR)
	{
		M_MGR->Update();

	}
	if (underUI)
	{
		underUI->Update();

	}
}

void DataManager::Render(HDC hdc)
{
}
