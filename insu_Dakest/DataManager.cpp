#include "DataManager.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "UnderUI.h"
#include "MapGenManager.h"
#include "OverUi.h"
#include "Image.h"
#include "Inventory.h"
#include "ItemObject.h"
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
	HitEffect = nullptr;
	SetRect(&minimapZone, WINSIZE_X / 2 + 10, (WINSIZE_Y - WINSIZE_Y / 3) + 10, WINSIZE_X / 2 + 10 + 430, (WINSIZE_Y - WINSIZE_Y / 3) + 10 + 230);
	SetRect(&statusZone, 0, (WINSIZE_Y - WINSIZE_Y / 3) + 10, WINSIZE_X / 2 , (WINSIZE_Y - WINSIZE_Y / 3) + 10 + 230);
	SetRect(&characterZone, 0, 0, WINSIZE_X, (WINSIZE_Y - WINSIZE_Y / 3));
	d_info = UiDataManager::GetSingleton()->GetTile()->GetDinfo();
	isChange = false;
	overUi = new OverUi();
	overUi->Init();
	battleTurn = 0;
	HitEffectCheck = false;
	inven = UiDataManager::GetSingleton()->GetInven();
	inven->SetPos({ 640, 480 });
	return S_OK;
}


void DataManager::Release()
{
	//SAFE_RELEASE(underUI);
	SAFE_RELEASE(underUI);
	SAFE_RELEASE(overUi);
}

void DataManager::Update()
{
	d_info = UiDataManager::GetSingleton()->GetTile()->GetDinfo();

	mouseOffsetX =thisTile->getPos2().x - 215;
	mouseOffsetY =thisTile->getPos2().y - 100;	
	minimapposx = (WINSIZE_X / 2 + 10);
	minimapposy = (WINSIZE_Y - WINSIZE_Y / 3) + 20;
	inven->Update();
	C_MGR = UiDataManager::GetSingleton()->GetSC_MGR();
	if (C_MGR)
	{
		C_MGR->Update();
		if (UiDataManager::GetSingleton()->GetBattleState() == true) {
			if (C_MGR->GetCharacters().size() == 0)
			{
				UiDataManager::GetSingleton()->SetBattleState(false);
			}
		}

	}
	if (HitEffectCheck == true) {

	HitTimes += TimerManager::GetSingleton()->GetElapsedTime() * 10;
		if (HitTimes > 0.5f)
		{
			if (hiteffectFrame < 9) {
				hiteffectFrame += 1;
				HitTimes = 0;
			}
			else
			{
				hiteffectFrame = 0;
				HitEffectCheck = false;
			}
		}
	}
	UiDataManager::GetSingleton()->SetCampos(camPos);
	for (int i = 0; i < minmap.size(); i++)
	{
		minmap[i]->Update();
	}
	if (UiDataManager::GetSingleton()->GetCampos() <= -1780)
	{
		SetRect(&Door, 980, 100, 1160, (WINSIZE_Y - WINSIZE_Y / 3)-50);
	}
	else
	{
		SetRect(&Door, -100, -100, -100, -100);

	}


	if (UiDataManager::GetSingleton()->GetBattleState() == false) {
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{


			RECT closerc = inven->getcloseRC();
			RECT openrc = inven->getoPenRc();

			if (PtInRect(&closerc, g_ptMouse))
			{
				inven->SetOpen(false);
			}
			if (PtInRect(&openrc, g_ptMouse))
			{
				inven->SetOpen(true);
			}


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
							for (int i = 0; i < C_MGR->GetCharacters().size();i++)
							{
								C_MGR->GetCharacters()[i]->SetSelected(false);
							}

							for (int j = 0; j < minmap.size(); j++)
							{
								if (minmap[j]->GetIsPath())
								{
									int prx = minmap[j]->GetPrevNnext().x;
									int pry = minmap[j]->GetPrevNnext().y;
									if ((prx == thisTile->getindex() && pry == tempTile->getindex()))
									{
										thisTile->SetIsCurrted(false);

										thisTile->SetIsVisited(true);
										UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);
										UiDataManager::GetSingleton()->SetCurrtile(minmap[j]);
										UiDataManager::GetSingleton()->SetDestTile(tempTile);
										UiDataManager::GetSingleton()->GetDestTile()->SetIsDest(true);
										SceneManager::GetSingleton()->ChangeTile(minmap[j]);
										return;
									}
									if ((pry == thisTile->getindex() && prx == tempTile->getindex()))
									{
										thisTile->SetIsCurrted(false);
										
										thisTile->SetIsVisited(true);
										UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);

										UiDataManager::GetSingleton()->SetCurrtile(minmap[j]);
										UiDataManager::GetSingleton()->SetDestTile(tempTile);
										UiDataManager::GetSingleton()->GetDestTile()->SetIsDest(true);
										SceneManager::GetSingleton()->ChangeTile(minmap[j]);

										return;
									}
								}
							}
						}
					}
				}

			}
			if (PtInRect(&characterZone, g_ptMouse))
			{
				if (d_info.dType == DungeonType::PATH)
				{
					if (PtInRect(&Door, g_ptMouse))
					{
						for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
						{
							C_MGR->GetCharacters()[i]->SetSelected(false);
						}

						UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);

						UiDataManager::GetSingleton()->GetDestTile()->SetIsDest(false);
						UiDataManager::GetSingleton()->GetTile()->SetIsDest(false);
						UiDataManager::GetSingleton()->SetCurrtile(UiDataManager::GetSingleton()->GetDestTile());
						SceneManager::GetSingleton()->ChangeTile(UiDataManager::GetSingleton()->GetDestTile());
						return;
					}
				}
			}

			 if (PtInRect(&characterZone, g_ptMouse))
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
							selctedSkill = nullptr;
							selectedChr->SetSelected(true);
							underUI->SetSelChr(C_MGR->GetCharacters()[i]);

							if (!selectedChr)
							{
								selctedSkill = nullptr;
							}
						}
					}
				}
			}
		}
	}

	
	if (M_MGR)
	{
		M_MGR->Update();
		if (UiDataManager::GetSingleton()->GetBattleState() == true) {
			if (M_MGR->GetCharacters().size() <1)
			{
				UiDataManager::GetSingleton()->SetBattleState(false);
				d_info.isEnemyed = false;
				thisTile->SetIsEnemy(false);
		
			}
		}
	}
	if (selectedChr) {
		S_MGR = selectedChr->getSkillMgr();
	}
	/*if (UiDataManager::GetSingleton()->GetBattleState() == true) {
		BattleStages((*C_MGR),(*M_MGR));
    }*/
	if (UiDataManager::GetSingleton()->GetBattleState() == true) {
	
		
		if (overUi->GetDoneStart() == true) {
			if (BPG == NOBATTLE || BPG == ING) {

				for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
				{
		
					C_MGR->GetCharacters()[i]->SetHaveTurn(true);
					BDice.push_back((make_pair(C_MGR->GetCharacters()[i], C_MGR->GetCharacters()[i]->Dice())));

				}
				for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
				{
					M_MGR->GetCharacters()[i]->SetHaveTurn(true);
					BDice.push_back((make_pair(M_MGR->GetCharacters()[i], M_MGR->GetCharacters()[i]->Dice())));

				}

				sort(BDice.begin(), BDice.end(), compare);
				BPG = BSTART;

				//boiter = BDice.begin();
			}
			if (BPG == BSTART) {
	
				if (BDice.back().first->GetUnitType() == UnitType::HERO)
				{
					BDice.back().first->SetHaveTurn(false);
					if (BattleStages2((C_MGR), (M_MGR), BDice.back().first->GetThis()) == true)
					{
						BDice.pop_back();
					}
				
		
				}

				else if(BDice.back().first->GetUnitType() == UnitType::MONSTER) {
					eltimess += TimerManager::GetSingleton()->GetElapsedTime();
					BDice.back().first->SetHaveTurn(false);
					{
						if (eltimess > 1.0f) {
							if (BDice.back().first->GetStat().hp > 0) {

								if (BattleStages2((C_MGR), (M_MGR), BDice.back().first->GetThis()) == true)
								{
									BDice.pop_back();
									eltimess = 0;
								}
							}
							else
							{
								BDice.pop_back();
								eltimess = 0;
							}
						}
					}

				}
				else
				{
					BPG = ING;
				}



				if (UiDataManager::GetSingleton()->GetBattleState() != false && BDice.size() == 0)
				{
					BPG = ING;
				}
				else
				{
					BPG = BSTART;

				}
			}

		}
		if (BPG == BEND) {
			UiDataManager::GetSingleton()->SetBattleState(false);
			thisTile->SetIsEnemy(false);

			for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
			{
				C_MGR->GetCharacters()[i]->SetCurrState(State::IDLE);
				BPG = NOBATTLE;
			}
		}
    }
	if (overUi)
	{
		overUi->Update();
	}
	
	if (underUI)
	{
		underUI->Update();

	}
}

void DataManager::Render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	//wsprintf(szText, "X : %d, Y : %d", thisTile->getindex(), thisTile->getindex());
	//TextOut(hdc, 200, 60, szText, strlen(szText));
	//wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x - minimapposx + mouseOffsetX, g_ptMouse.y - minimapposy + mouseOffsetY);
	//TextOut(hdc, 800, 100, szText, strlen(szText));
	//wsprintf(szText, "X : %d, Y : %d", UiDataManager::GetSingleton()->GetTile()->getindex(), UiDataManager::GetSingleton()->GetTile()->GetPrevNnext().y);
	//TextOut(hdc, 200, 500, szText, strlen(szText));
	SetBkMode(hdc, TRANSPARENT);


	if (M_MGR)
	{
		if (BattleStage) {
			M_MGR->Render(hdc);
		}
	}
	if (C_MGR)
	{
		C_MGR->Render(hdc);
	}
	if (overUi)
	{
		overUi->Render(hdc);
	}


	if (underUI) {
		underUI->Render(hdc);
		underUI->SetSelChr(selectedChr);

		if (selectedChr)
		{
			wsprintf(szText, "HP : %d", selectedChr->GetStat().hp);
			TextOut(hdc, 210, 580, szText, strlen(szText));
			wsprintf(szText, "ATK : %d", selectedChr->GetStat().damage.x);
			TextOut(hdc, 190, 630, szText, strlen(szText));
			wsprintf(szText, " ~  %d", selectedChr->GetStat().damage.y);
			TextOut(hdc, 240, 630, szText, strlen(szText));
			wsprintf(szText, "AS : %d", selectedChr->GetStat().atkSpeed);
			TextOut(hdc, 190, 660, szText, strlen(szText));
			//190 , 630

		}

	}
	//inven->Render(hdc);
	underUI->SkillRender(hdc);
	//if(inven->GetOpen()==true)
	if (HitEffect)
	{
		if (HitEffectCheck == true) {
			//if
			if (TTYPE2 == PLAYERTURN)
			{
				HitEffect->FrameRender(hdc, WINSIZE_X / 2, 0, hiteffectFrame, 0, false, 1.4);

			}
			else if (TTYPE2 == MONTURN)
			{
				HitEffect->FrameRender(hdc, 00, 0, hiteffectFrame, 0, false, 1.4);
			}
		}
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F1)) {
		Rectangle(hdc, Door.left, Door.top, Door.right, Door.bottom);
			Rectangle(hdc, statusZone.left, statusZone.top, statusZone.right, statusZone.bottom);
			Rectangle(hdc, characterZone.left, characterZone.top, characterZone.right, characterZone.bottom);
			Rectangle(hdc, minimapZone.left, minimapZone.top, minimapZone.right, minimapZone.bottom);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F2)) {
		Rectangle(hdc, Door.left, Door.top, Door.right, Door.bottom);
	}
}



bool DataManager::compare(const BODER& a, const BODER& b)
{
	{
		if (a.second == b.second)
		{
			return a.first->GetStat().atkSpeed < b.first->GetStat().atkSpeed;
		}
		else {
			return a.second < b.second;
		}

		return false;
	}

}

bool DataManager::BattleStages2(CharacterManager* C_MGR, CharacterManager* M_MGR, Character* turnchr)
{
	int num = 0;
	bool monfindTarget = false;
	
	bool itouch = false;
	
	underUI->Update();

	if (turnchr->GetStun() == true)
	{
		turnchr->setStun(false);
		return true;
	}

	if (M_MGR->GetCharacters().empty())
	{
		BPG = BEND;
		UiDataManager::GetSingleton()->SetBattleState(false);
		return true;
	}
	if (M_MGR->GetCharacters().size() == 0)
	{
		BPG = BEND;
		UiDataManager::GetSingleton()->SetBattleState(false);
		return true;
	}
	vector<BODER>::iterator tempits;
	
	if (turnchr->GetUnitType() == UnitType::MONSTER)//(*boiter).first->GetUnitType() == UnitType::MONSTER)
	{
		TTYPE = MONTURN;

	}
	else if (turnchr->GetUnitType() == UnitType::HERO)
	{
		TTYPE = PLAYERTURN;
	}

	if (TTYPE == MONTURN)//(*boiter).first->GetHaveTurn() == true)
	{
		int randomhero;
		randomhero = rand() % C_MGR->GetCharacters().size();
		MselctetChr = C_MGR->GetCharacters()[randomhero];
		if (monfindTarget == false) {
			MselctetChr->SetTargeted(true);
			monfindTarget = true;

		}
		if (monfindTarget == true) {
			eltimess += TimerManager::GetSingleton()->GetElapsedTime();
			turnchr->Attack(MselctetChr);
			turnchr->SetCurrState(State::SKILL1);
			MselctetChr->SetPos(WINSIZE_X / 2 - 170);
			turnchr->SetPos(WINSIZE_X / 2 + 150);
			MselctetChr->SetTargeted(false);
			monfindTarget = false;
			MselctetChr = nullptr;
			if (DoHitEffect(TTYPE))
			{
				TTYPE2 = MONTURN;
				UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);

				return true;
			}
		}
		if (eltimess >= 0.5f) {

			eltimess = 0;
		}
		

	}




	if (turnchr->GetUnitType() == UnitType::HERO)
	{
		TTYPE = PLAYERTURN;
		//selectedChr=;
		if (selectedChr) {
			selectedChr->SetSelected(false);
			underUI->SetSelChr(selectedChr);
		}
		SelectChar(turnchr->GetThis());
		selectedChr->SetSelected(true);
		//selctedSkill = nullptr;
	



		if (!selectedChr)
		{
			selctedSkill = nullptr;
		}
	}
	if (selctedSkill == nullptr || selectedChr == nullptr)
	{
		for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
		{
			C_MGR->GetCharacters()[i]->SetHFixed(false);
			C_MGR->GetCharacters()[i]->SetHTargeted(false);
			C_MGR->GetCharacters()[i]->SetFixed(false);
			C_MGR->GetCharacters()[i]->SetTargeted(false);
			C_MGR->GetCharacters()[i]->SetMTargeted(false);
			C_MGR->GetCharacters()[i]->SetMFixed(false);
		}
	}


	if (selctedSkill)
	{
		if (selctedSkill->GetSkillType() == SKILLTYPE::SWAPSKILL)
		{
			for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
			{
				C_MGR->GetCharacters()[i]->SetHFixed(false);
				C_MGR->GetCharacters()[i]->SetHTargeted(false);
				C_MGR->GetCharacters()[i]->SetMFixed(false);

				if (C_MGR->GetCharacters()[i] != selectedChr) {
					if (selctedSkill->GetSkillInfo().targetRank.x <= C_MGR->GetCharacters()[i]->GetIndex()
						&& selctedSkill->GetSkillInfo().targetRank.y >= C_MGR->GetCharacters()[i]->GetIndex())
					{
						C_MGR->GetCharacters()[i]->SetMTargeted(true);


					}
					else
					{
						C_MGR->GetCharacters()[i]->SetMTargeted(false);
					}
				}

			}
			for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
			{
				if (PointInRect(g_ptMouse, C_MGR->GetCharacters()[i]->GetRect())) {
					if (C_MGR->GetCharacters()[i]->GetMTargeted() == true && selctedSkill->GetSkillInfo().range >= 4)
					{
						for (int j = 0; j < C_MGR->GetCharacters().size(); j++)
						{
							C_MGR->GetCharacters()[j]->SetMFixed(true);
						}
						targeton = true;
					}
					else if (C_MGR->GetCharacters()[i]->GetMTargeted() == true && selctedSkill->GetSkillInfo().range > 1 && selctedSkill->GetSkillInfo().range < 4)
					{
						for (int j = 0; j < selctedSkill->GetSkillInfo().range; j++)
						{

							if (C_MGR->GetCharacters()[i]->GetIndex() + j >= 4)
							{
								break;
							}
							else {
								if (i + j >= C_MGR->GetCharacters().size())
								{

								}
								else if (C_MGR->GetCharacters()[(i + j)])
								{
								
									if (C_MGR->GetCharacters()[(i + j)]->GetMTargeted() == true) {
										C_MGR->GetCharacters()[(i + j)]->SetMFixed(true);
									}
									targeton = true;
								}

							}

						}
					}
					else if (C_MGR->GetCharacters()[i]->GetMTargeted() == true)
					{
						C_MGR->GetCharacters()[i]->SetMFixed(true);
						targeton = true;
					}
					else
					{
						targeton = false;
					}
				}

			}
		}

		if (selctedSkill->GetSkillType() == SKILLTYPE::HEALSKILL)
		{
			for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
			{

				M_MGR->GetCharacters()[i]->SetFixed(false);
				M_MGR->GetCharacters()[i]->SetTargeted(false);
			}

			for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
			{
				C_MGR->GetCharacters()[i]->SetMTargeted(false);
				C_MGR->GetCharacters()[i]->SetMFixed(false);

				C_MGR->GetCharacters()[i]->SetHFixed(false);

				if (selctedSkill->GetSkillInfo().targetRank.x <= C_MGR->GetCharacters()[i]->GetIndex()
					&& selctedSkill->GetSkillInfo().targetRank.y >= C_MGR->GetCharacters()[i]->GetIndex())
				{
					C_MGR->GetCharacters()[i]->SetHTargeted(true);


				}
				else
				{
					C_MGR->GetCharacters()[i]->SetHTargeted(false);
				}

			}
			for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
			{
				if (PointInRect(g_ptMouse, C_MGR->GetCharacters()[i]->GetRect())) {
					if (C_MGR->GetCharacters()[i]->GetHTargeted() == true && selctedSkill->GetSkillInfo().range >= 4)
					{
						for (int j = 0; j < C_MGR->GetCharacters().size(); j++)
						{
							C_MGR->GetCharacters()[j]->SetHFixed(true);
						}
						targeton = true;
					}
					else if (C_MGR->GetCharacters()[i]->GetHTargeted() == true && selctedSkill->GetSkillInfo().range > 1&& selctedSkill->GetSkillInfo().range < 4)
					{
						for (int j = 0; j < selctedSkill->GetSkillInfo().range; j++)
						{

							if (C_MGR->GetCharacters()[i]->GetIndex() + j >= 4)
							{
								break;
							}
							else {
								if (i + j >= C_MGR->GetCharacters().size())
								{

								}
								else if (C_MGR->GetCharacters()[(i + j)])
								{
				
									if (C_MGR->GetCharacters()[(i + j)]->GetHTargeted() == true) {
										C_MGR->GetCharacters()[(i + j)]->SetHFixed(true);
									}
									targeton = true;
								}

							}

						}
					}
					else if (C_MGR->GetCharacters()[i]->GetHTargeted() == true)
					{
						C_MGR->GetCharacters()[i]->SetHFixed(true);
						targeton = true;
					}
					else
					{
						targeton = false;
					}
				}

			}
		}

		if (selctedSkill->GetSkillType() == SKILLTYPE::COMBATSKILL || selctedSkill->GetSkillType() == SKILLTYPE::ARANGESKILL|| selctedSkill->GetSkillType() == SKILLTYPE::CHARGESKILL)
		{

			for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
			{
			C_MGR->GetCharacters()[i]->SetHFixed(false);
			C_MGR->GetCharacters()[i]->SetHTargeted(false);

			C_MGR->GetCharacters()[i]->SetMTargeted(false);
			C_MGR->GetCharacters()[i]->SetMFixed(false);
			}

			for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
			{

				M_MGR->GetCharacters()[i]->SetFixed(false);
				M_MGR->GetCharacters()[i]->SetTargeted(false);
			}

		
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
	if (itouch == true) {
	/*	eltimess += TimerManager::GetSingleton()->GetElapsedTime();

		if (eltimess > 2.0f) {
			UiDataManager::GetSingleton()->SetTurnExit(true);
			eltimess = 0;
		}*/
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{

		if (PtInRect(&statusZone, g_ptMouse)) {

			if (S_MGR)
			{
				for (int i = 0; i < S_MGR->GetSkillSlot().size(); i++)
				{
					RECT tempRC = S_MGR->GetSkillSlot()[i]->GetRect();
				
					if (PtInRect(&tempRC, g_ptMouse)) {
						if (i == 5)
						{
							underUI->setSelSkill(nullptr);
							selectedChr->SetSelected(false);
							selectedChr = nullptr;
							selctedSkill = nullptr;
							UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);

							return true;
						}
				/*		if (i == 4)
						{
							underUI->setSelSkill(nullptr);
							selectedChr->SetSelected(false);
							selectedChr = nullptr;
							selctedSkill = nullptr;
							return true;
						}*/
						if (S_MGR->GetSkillSlot()[i]->GetSkillState() == Skill::SkillState::ON) {
							underUI->setSelSkill(S_MGR->GetSkillSlot()[i]);
							selectSkill(S_MGR->GetSkillSlot()[i]);
						}
					}
				}
				
			}
			
		}
		
		else if (PtInRect(&characterZone, g_ptMouse))
		{

			vector<int>tempPos;
		
			if (selectedChr && selctedSkill)
			{	
				if (selctedSkill->GetSkillType() == SKILLTYPE::SWAPSKILL)
				{
					int destIndex;
					if (!C_MGR->GetCharacters().empty()) {
						for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
						{
							if (C_MGR->GetCharacters()[i]->GetMFixed() == true)
							{
								//selctedSkill->run(0, C_MGR->GetCharacters()[i]);
								tempPos.push_back(0);
								destIndex = C_MGR->GetCharacters()[i]->GetIndex();
								itouch = true;
							}
						}
						if (itouch == true) {
							

							vector<Character*>* tempc_mgr = C_MGR->GetCharactersPointer();
							if (destIndex < selectedChr->GetIndex()) {
								int num = selectedChr->GetIndex() - destIndex;
								vector<Character*>::iterator seliter;
								vector<Character*>::iterator changeiter;
								Character* temp;
								for(int j=0;j< num;j++)
								for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
								{
									if (selectedChr == C_MGR->GetCharacters()[i])
									{

										temp = C_MGR->GetCharacters()[i];
										(*tempc_mgr)[i] = (*tempc_mgr)[i - 1];
										(*tempc_mgr)[i - 1] = temp;

										break;
									}
								}

							}
							else if(destIndex > selectedChr->GetIndex()){
								int num = destIndex - selectedChr->GetIndex();
								vector<Character*>::iterator seliter;
								vector<Character*>::iterator changeiter;
								Character* temp;
								for (int j = 0; j < num; j++) {
									for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
									{
										if (selectedChr == C_MGR->GetCharacters()[i])
										{

											temp = C_MGR->GetCharacters()[i];
											(*tempc_mgr)[i] = (*tempc_mgr)[i + 1];
											(*tempc_mgr)[i + 1] = temp;
											break;
										}
									}
								}
							}
							for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
							{
								if (C_MGR->GetCharacters()[i]->GetMTargeted() == true)
								{
									C_MGR->GetCharacters()[i]->SetMTargeted(false);

								}
								if (C_MGR->GetCharacters()[i]->GetMFixed() == true)
								{
									C_MGR->GetCharacters()[i]->SetMFixed(false);

								}

							}
							
							underUI->setSelSkill(nullptr);
							selectedChr->SetSelected(false);
							selectedChr = nullptr;
							selctedSkill = nullptr;
							itouch = false;
							UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);

							return true;
						}

						if (UiDataManager::GetSingleton()->GetTurnExit() == true) {
							UiDataManager::GetSingleton()->SetTurnExit(false);
						}


					}
				}
				else if (selctedSkill->GetSkillType() == SKILLTYPE::HEALSKILL)
				{
					if (!C_MGR->GetCharacters().empty()) {
						for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
						{
							if (C_MGR->GetCharacters()[i]->GetHFixed() == true)
							{
								int attdmg = rand() % selectedChr->GetStat().damage.y + selectedChr->GetStat().damage.x;
								selctedSkill->run(attdmg, C_MGR->GetCharacters()[i]);
								tempPos.push_back(0);
								itouch = true;
							}
						}
						if (itouch == true) {
						
							//turnchr->SetPos(WINSIZE_X / 2 - 150);

							for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
							{
								if (C_MGR->GetCharacters()[i]->GetHTargeted() == true)
								{
									C_MGR->GetCharacters()[i]->SetHTargeted(false);
								}
								if (C_MGR->GetCharacters()[i]->GetHFixed() == true)
								{
									for (int j = 0; j < tempPos.size(); j++)
									{
										//C_MGR->GetCharacters()[i]->SetPos(WINSIZE_X / 2 + j * 150);
										C_MGR->GetCharacters()[i]->SetFxon(Character::FxType::HEALFX);

									}
									C_MGR->GetCharacters()[i]->SetHFixed(false);
								}
							}
						
							underUI->setSelSkill(nullptr);
							selectedChr->SetSelected(false);
							selectedChr = nullptr;
							selctedSkill = nullptr;
							itouch = false;
							UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);

							return true;
						}

						if (UiDataManager::GetSingleton()->GetTurnExit() == true) {
							UiDataManager::GetSingleton()->SetTurnExit(false);
						}


					}
				}
				else {
					if (!M_MGR->GetCharacters().empty()) {
						for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
						{
							if (M_MGR->GetCharacters()[i]->GetFixed() == true)
							{
								int attdmg = rand() % selectedChr->GetStat().damage.y + selectedChr->GetStat().damage.x;
								selctedSkill->run(attdmg, M_MGR->GetCharacters()[i]);
								M_MGR->GetCharacters()[i]->SetPos(WINSIZE_X / 2 + 100 * i);
								itouch = true;
							}
						}
						if (itouch == true) {
							for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
							{
								if (M_MGR->GetCharacters()[i]->GetTargeted() == true)
								{
									M_MGR->GetCharacters()[i]->SetTargeted(false);
								}
								if (M_MGR->GetCharacters()[i]->GetFixed() == true)
								{
									M_MGR->GetCharacters()[i]->SetFixed(false);
								}
							}
							if (selctedSkill->GetSkillType() == SKILLTYPE::CHARGESKILL)
							{
								vector<Character*>::iterator seliter;
								vector<Character*>::iterator changeiter;
								Character* temp;
								//int tempId;
								vector<Character*>* tempc_mgr = C_MGR->GetCharactersPointer();
								for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
								{
									if (selectedChr == C_MGR->GetCharacters()[i])
									{

										//tempId = (*tempc_mgr)[i]->GetIndex();
										//(*tempc_mgr)[i]->SetIndex((*tempc_mgr)[i - 1]->GetIndex());
										//(*tempc_mgr)[i - 1]->SetIndex(tempId);
										
										//seliter = (*tempc_mgr).begin() + i;
										//changeiter = (*tempc_mgr).begin() + i - 1;
										//swap((seliter),(changeiter));

										temp = C_MGR->GetCharacters()[i]; 
										(*tempc_mgr)[i] = (*tempc_mgr)[i - 1];
										(*tempc_mgr)[i - 1] = temp;
										break;
									}
								}

							
								for (int i = 0; i < C_MGR->GetCharacters().size(); i++)
								{
									if (C_MGR->GetCharacters()[i]->GetSelected() == true)
									{
										C_MGR->GetCharacters()[i]->SetSelected(false);
									}
								}
							}
						
								underUI->setSelSkill(nullptr);
								selectedChr->SetSelected(false);
								selectedChr = nullptr;
								selctedSkill = nullptr;
								itouch = false;
						
							
							if (DoHitEffect(TTYPE))
							{
								TTYPE2 = PLAYERTURN;
								UiDataManager::GetSingleton()->SetSC_MGR(C_MGR);
								return true;
							}

						}

						if (UiDataManager::GetSingleton()->GetTurnExit() == true) {
							UiDataManager::GetSingleton()->SetTurnExit(false);
						}


					}
				}

			}

		}

	}
	
}

bool DataManager::DoHitEffect(TurnType types)
{
	if (HitEffectCheck == false) {
		this->HitEffectCheck = true;
		hiteffectFrame = 0;
	}
	
	if (types == PLAYERTURN)
	{
		HitEffect = ImageManager::GetSingleton()->FindImage("««∞›¿Ã∆Â∆Æø¿");
	}
	if(types==MONTURN)
	{
		HitEffect = ImageManager::GetSingleton()->FindImage("««∞›¿Ã∆Â∆Æøﬁ");

	}
	return true;

}




