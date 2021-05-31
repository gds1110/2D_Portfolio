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

HRESULT DataManager::Init(CharacterManager* C_MGR, CharacterManager* M_MGR,Tile* currTile)
{

	camPos = 0;
	this->C_MGR = C_MGR;
	this->M_MGR = M_MGR;
	this->minmap = UiDataManager::GetSingleton()->GetMiniMap();
	underUI = new UnderUi();
	underUI->Init(currTile, minmap);
	thisTile = currTile;
	/*C_MGR->GetCharacters()[1]->getSkillMgr()->AddSkill(new CombatAttack);*/
	BattleStage = false;
	cursorChar = nullptr;
	targeton = false;
	SetRect(&minimapZone, WINSIZE_X / 2 + 10, (WINSIZE_Y - WINSIZE_Y / 3) + 10, WINSIZE_X / 2 + 10 + 430, (WINSIZE_Y - WINSIZE_Y / 3) + 10 + 230);
	SetRect(&statusZone, 0, (WINSIZE_Y - WINSIZE_Y / 3) + 10, WINSIZE_X / 2 , (WINSIZE_Y - WINSIZE_Y / 3) + 10 + 230);
	SetRect(&characterZone, 0, 0, WINSIZE_X, (WINSIZE_Y - WINSIZE_Y / 3));
	d_info = UiDataManager::GetSingleton()->GetTile()->GetDinfo();
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
{
	SAFE_RELEASE(underUI);
	
}

void DataManager::Update()
{
	d_info = UiDataManager::GetSingleton()->GetTile()->GetDinfo();

	mouseOffsetX =thisTile->getPos2().x - 215;
	mouseOffsetY =thisTile->getPos2().y - 100;	
	minimapposx = (WINSIZE_X / 2 + 10);
	minimapposy = (WINSIZE_Y - WINSIZE_Y / 3) + 20;
	
	for (int i = 0; i < minmap.size(); i++)
	{
		minmap[i]->Update();
	}

	if (C_MGR)
	{
		C_MGR->Update();
	}
	if (M_MGR)
	{
		M_MGR->Update();
	}
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
		if (PtInRect(&minimapZone, g_ptMouse)) {
			//Tile* tempTile = UiDataManager::GetSingleton()->GetTile();
			if (d_info.dType == DungeonType::ROOM || d_info.dType == DungeonType::START)
			{
				for (int i = 0; i < thisTile->GetWay().size(); i++) {

					Tile* tempTile = thisTile->GetWay()[i];
					RECT rc = tempTile->GetRC();
					int ptmousetestx = g_ptMouse.x - minimapposx + mouseOffsetX;
					int ptmousetesty = g_ptMouse.y - minimapposy + mouseOffsetY;
					if (PtInRect(&(rc), { ptmousetestx , ptmousetesty }))
					{
						for (int j = 0; j < minmap.size(); j++)
						{
							if (minmap[j]->GetIsPath())
							{
								int prx = minmap[j]->GetPrevNnext().x;
								int pry = minmap[j]->GetPrevNnext().y;
								if ( (prx== thisTile->getindex() && pry == tempTile->getindex())) 
								{
									SceneManager::GetSingleton()->ChangeTile(minmap[j]);

								}
								if ((pry == thisTile->getindex() && prx == tempTile->getindex()))
								{
									SceneManager::GetSingleton()->ChangeTile(minmap[j]);

								}
							}
						}
						//SceneManager::GetSingleton()->ChangeTile();
					}
				}
			}
			else if (d_info.dType == DungeonType::PATH)
			{

			}
			
		}
		else if (PtInRect(&statusZone, g_ptMouse)) {

			if (S_MGR)
			{
				for (int i = 0; i < S_MGR->GetSkillSlot().size(); i++)
				{
					RECT tempRC = S_MGR->GetSkillSlot()[i]->GetRect();
					if (PtInRect(&tempRC, g_ptMouse)) {
						if (S_MGR->GetSkillSlot()[i]->GetSkillState() == Skill::SkillState::ON) {
							underUI->setSelSkill(S_MGR->GetSkillSlot()[i]);
							selectSkill(S_MGR->GetSkillSlot()[i]);
						}
					}
				}
			}

		}
		else if (PtInRect(&characterZone,g_ptMouse))
		{
			if (!C_MGR->GetCharacters().empty()) {
				for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
				{
					RECT tempRC = C_MGR->GetCharacters()[i]->GetRect();
					if (PtInRect(&tempRC, g_ptMouse))
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

			if (selectedChr && selctedSkill)
			{
				if (M_MGR) {
					for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
					{
						if (M_MGR->GetCharacters()[i]->GetFixed() == true)
						{
							selctedSkill->run(0, M_MGR->GetCharacters()[i]);
							M_MGR->GetCharacters()[i]->SetPos(WINSIZE_X / 2 + 100 * i);
							selectedChr->SetPos(WINSIZE_X / 2);
							//selectedChr->SetCurrState(State::SKILL1);
						}
						else
						{

						}
					}
				}

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
	if (underUI) {
		underUI->Render(hdc);
	}
	if (M_MGR)
	{
		M_MGR->Render(hdc);
	}
	if (C_MGR)
	{
		C_MGR->Render(hdc);
	}
	wsprintf(szText, "X : %d, Y : %d", thisTile->getindex(), thisTile->getindex());
	TextOut(hdc, 200, 60, szText, strlen(szText));
	wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x - minimapposx + mouseOffsetX, g_ptMouse.y - minimapposy + mouseOffsetY);
	TextOut(hdc, 800, 100, szText, strlen(szText));
	wsprintf(szText, "X : %d, Y : %d", UiDataManager::GetSingleton()->GetTile()->getindex(), UiDataManager::GetSingleton()->GetTile()->GetPrevNnext().y);
	TextOut(hdc, 200, 500, szText, strlen(szText));
	/*Rectangle(hdc, statusZone.left, statusZone.top, statusZone.right, statusZone.bottom);
	Rectangle(hdc, characterZone.left, characterZone.top, characterZone.right, characterZone.bottom);*/
}
