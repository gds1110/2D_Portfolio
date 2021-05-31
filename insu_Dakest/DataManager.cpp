#include "DataManager.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "UnderUI.h"
#include "MapGenManager.h"
HRESULT DataManager::Init()
{
	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();
	return S_OK;
}

HRESULT DataManager::Init(CharacterManager* C_MGR, CharacterManager* M_MGR, UnderUi* ui)
{

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

HRESULT DataManager::Init(CharacterManager* SC_MGR, CharacterManager* SM_MGR, UnderUi* ui, Tile* currtile)
{
	this->C_MGR = SC_MGR;
	this->M_MGR = SM_MGR;
	this->underUI = ui;
	this->d_info = currtile->GetDinfo();
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
	int mouseOffsetX;
	int mouseOffsetY;
	int minimapposx;
	int	minimapposy;
	mouseOffsetX = d_info.pos.x - 215;
	mouseOffsetY = d_info.pos.y - 100;	
	minimapposx = (WINSIZE_X / 2 + 10);
	minimapposy = (WINSIZE_Y - WINSIZE_Y / 3) + 20;
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
		if (!C_MGR->GetCharacters().empty()) {
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
		
		Tile* tempTile = UiDataManager::GetSingleton()->GetTile();
		for (int i = 0; i < tempTile->GetWay().size(); i++) {

			RECT rc = tempTile->GetWay()[i]->GetRC();
			if (PtInRect(&(rc), { g_ptMouse.x - minimapposx + mouseOffsetX,g_ptMouse.y - minimapposy + mouseOffsetY }))
			{
				tempTile->SetIsCurrted(false);
				tempTile->GetWay()[i]->SetIsCurrted(true);
				UiDataManager::GetSingleton()->SetCurrtile(tempTile->GetWay()[i]);
				SceneManager::GetSingleton()->ChangeScene2("스테이지1", tempTile);
				return;
				//currTile = currTile->GetWay()[i];
			}
		}
    }


	if (underUI)
	{
		underUI->Update();

	}
}

void DataManager::Render(HDC hdc)
{
}
