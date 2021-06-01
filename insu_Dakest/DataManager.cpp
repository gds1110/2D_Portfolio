#include "DataManager.h"
#include "Character.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "SkillManager.h"
#include "CommonFunction.h"
#include "UnderUI.h"
#include "MapGenManager.h"
#include "OverUi.h"
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
	isChange = false;
	overUi = new OverUi();
	overUi->Init();
	battleTurn = 0;
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
									if ((prx == thisTile->getindex() && pry == tempTile->getindex()))
									{
										UiDataManager::GetSingleton()->SetCurrtile(minmap[j]);
										UiDataManager::GetSingleton()->SetDestTile(tempTile);
										SceneManager::GetSingleton()->ChangeTile(minmap[j]);
										return;
									}
									if ((pry == thisTile->getindex() && prx == tempTile->getindex()))
									{
										UiDataManager::GetSingleton()->SetCurrtile(minmap[j]);
										UiDataManager::GetSingleton()->SetDestTile(tempTile);
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
	if (M_MGR)
	{
		M_MGR->Update();
		if (UiDataManager::GetSingleton()->GetBattleState() == true) {
			if (M_MGR->GetCharacters().size() <1)
			{
				UiDataManager::GetSingleton()->SetBattleState(false);
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
		if (BPG == NOBATTLE || BPG == BEND) {

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
		/*	vector<BODER>::reverse_iterator rbitor;
			for (rbitor = BDice.rbegin(); rbitor != BDice.rend();++rbitor)
			{
				BattleStages((C_MGR), (M_MGR), (*rbitor).first);
			}*/
			
			if (BattleStages2((C_MGR), (M_MGR), BDice.back().first->GetThis()) == true) {
				BDice.pop_back();
			}
				
			
				
				
		
			if (UiDataManager::GetSingleton()->GetBattleState() != false && BDice.size()==0)
			{
				BPG = BEND;
			}
			else
			{
				BPG = BSTART;

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
	if (underUI) {
		underUI->Render(hdc);
	}
	if (overUi)
	{
		overUi->Render(hdc);
	}
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
	wsprintf(szText, "X : %d, Y : %d", thisTile->getindex(), thisTile->getindex());
	TextOut(hdc, 200, 60, szText, strlen(szText));
	wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x - minimapposx + mouseOffsetX, g_ptMouse.y - minimapposy + mouseOffsetY);
	TextOut(hdc, 800, 100, szText, strlen(szText));
	wsprintf(szText, "X : %d, Y : %d", UiDataManager::GetSingleton()->GetTile()->getindex(), UiDataManager::GetSingleton()->GetTile()->GetPrevNnext().y);
	TextOut(hdc, 200, 500, szText, strlen(szText));

	Rectangle(hdc, Door.left, Door.top, Door.right, Door.bottom);
	/*Rectangle(hdc, statusZone.left, statusZone.top, statusZone.right, statusZone.bottom);
	Rectangle(hdc, characterZone.left, characterZone.top, characterZone.right, characterZone.bottom);*/
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

void DataManager::BattleStages(CharacterManager& C_MGR, CharacterManager& M_MGR)
{
	int num = 0;
	bool monfindTarget = false;
	if (BPG == NOBATTLE || BPG == BEND) {

		for (int i = 0; i < C_MGR.GetCharacters().size(); i++)
		{
			C_MGR.GetCharacters()[i]->SetHaveTurn(true);
			BDice.push_back((make_pair(C_MGR.GetCharacters()[i], C_MGR.GetCharacters()[i]->Dice())));
			num += 1;
		}
		for (int i = 0; i < M_MGR.GetCharacters().size(); i++)
		{
			M_MGR.GetCharacters()[i]->SetHaveTurn(true);
			BDice.push_back((make_pair(M_MGR.GetCharacters()[i], M_MGR.GetCharacters()[i]->Dice())));
			num += 1;
		}

		sort(BDice.begin(), BDice.end(), compare);
		BPG = BSTART;

		//boiter = BDice.begin();
	}


	//boiter = BDice.begin();

	//for (boiter = BDice.begin(); boiter != BDice.end();) {

	//}

	if (!BDice.empty()) {
		if (BDice.back().first->GetUnitType() == UnitType::MONSTER)//(*boiter).first->GetUnitType() == UnitType::MONSTER)
		{
			TTYPE = MONTURN;
			if (TTYPE == MONTURN && BDice.back().first->GetHaveTurn() == true)//(*boiter).first->GetHaveTurn() == true)
			{
				int randomhero;
				randomhero = rand() % C_MGR.GetCharacters().size();
				MselctetChr = C_MGR.GetCharacters()[randomhero];
				BDice.back().first->SetHaveTurn(false);
				eltimess += TimerManager::GetSingleton()->GetElapsedTime();
				if (monfindTarget == false) {
					MselctetChr->SetTargeted(true);
					monfindTarget = true;

				}
				if (monfindTarget == true) {
					BDice.back().first->Attack(MselctetChr);
					BDice.back().first->SetCurrState(State::SKILL1);
					MselctetChr->SetTargeted(false);
					monfindTarget = false;
					eltimess += TimerManager::GetSingleton()->GetElapsedTime();
					MselctetChr = nullptr;
					if (eltimess > 1.5f) {
						UiDataManager::GetSingleton()->SetTurnExit(true);
						eltimess = 0;
					}
						BDice.pop_back();
					if (UiDataManager::GetSingleton()->GetTurnExit() == true) {
						UiDataManager::GetSingleton()->SetTurnExit(false);
						return;
					}

				}
			}


		}
	}
	if (!BDice.empty()) {
		if (BDice.back().first->GetUnitType() == UnitType::HERO)
		{
			TTYPE = PLAYERTURN;
			//selectedChr=;
			if (selectedChr) {
				selectedChr->SetSelected(false);
				underUI->SetSelChr(selectedChr);
			}
			SelectChar(BDice.back().first->GetThis());
			selectedChr->SetSelected(true);
			//selctedSkill = nullptr;
			if (selectedChr->GetHaveTurn() == true) {
				BDice.back().first->SetHaveTurn(false);
			}


		}
		if (!selectedChr)
		{
			selctedSkill = nullptr;
		}

	}

		

	if (!BDice.empty()) {
		if (selctedSkill)
		{
			if (selctedSkill->GetSkillType() == SKILLTYPE::COMBATSKILL || selctedSkill->GetSkillType() == SKILLTYPE::ARANGESKILL)
			{
				for (int i = 0; i < M_MGR.GetCharacters().size(); i++)
				{
					M_MGR.GetCharacters()[i]->SetFixed(false);

					if (selctedSkill->GetSkillInfo().targetRank.x <= M_MGR.GetCharacters()[i]->GetIndex()
						&& selctedSkill->GetSkillInfo().targetRank.y >= M_MGR.GetCharacters()[i]->GetIndex())
					{
						M_MGR.GetCharacters()[i]->SetTargeted(true);


					}
					else
					{
						M_MGR.GetCharacters()[i]->SetTargeted(false);
					}
				}

				for (int i = 0; i < M_MGR.GetCharacters().size(); i++)
				{
					if (PointInRect(g_ptMouse, M_MGR.GetCharacters()[i]->GetRect())) {
						if (M_MGR.GetCharacters()[i]->GetTargeted() == true && selctedSkill->GetSkillInfo().range > 1)
						{
							for (int j = 0; j < selctedSkill->GetSkillInfo().range; j++)
							{

								if (M_MGR.GetCharacters()[i]->GetIndex() + j >= 4)
								{
									break;
								}
								else {
									if (i + j >= M_MGR.GetCharacters().size())
									{

									}
									else if (M_MGR.GetCharacters()[(i + j)])
									{
										/*if (i + j < selctedSkill->GetSkillInfo().range) {
											M_MGR->GetCharacters()[(i + j)]->SetFixed(true);
										}*/
										if (M_MGR.GetCharacters()[(i + j)]->GetTargeted() == true) {
											M_MGR.GetCharacters()[(i + j)]->SetFixed(true);
										}
										targeton = true;
									}

								}

							}
						}
						else if (M_MGR.GetCharacters()[i]->GetTargeted() == true)
						{
							M_MGR.GetCharacters()[i]->SetFixed(true);
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
	if (!BDice.empty()) {
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{

			if (PtInRect(&statusZone, g_ptMouse)) {

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
			else if (PtInRect(&characterZone, g_ptMouse))
			{


				if (selectedChr && selctedSkill)
				{
					if (!M_MGR.GetCharacters().empty()) {
						for (int i = 0; i < M_MGR.GetCharacters().size(); i++)
						{
							if (M_MGR.GetCharacters()[i]->GetFixed() == true)
							{
								int attdmg = rand() % selectedChr->GetStat().damage.y + selectedChr->GetStat().damage.x;
								selctedSkill->run(attdmg, M_MGR.GetCharacters()[i]);
								M_MGR.GetCharacters()[i]->SetPos(WINSIZE_X / 2 + 100 * i);


								//selectedChr->SetPos(WINSIZE_X / 2);
								//selectedChr->SetCurrState(State::SKILL1);
							}
							else
							{

							}
						}

						selectedChr->SetSelected(false);
						selectedChr = nullptr;
						if (eltimess > 1.5f) {
							UiDataManager::GetSingleton()->SetTurnExit(true);
							eltimess = 0;
							BDice.pop_back();
						}
						if (UiDataManager::GetSingleton()->GetTurnExit() == true) {
							UiDataManager::GetSingleton()->SetTurnExit(false);
							TTYPE = NONETURN;
							//return;
						}


					}

				}

			}
		}
	}
	if (UiDataManager::GetSingleton()->GetBattleState() != false &&BDice.empty())
	{
		BPG = BEND;
	}
}

void DataManager::BattleStages(CharacterManager* C_MGR, CharacterManager* M_MGR, Character* turnchr)
{
	int num = 0;
	bool monfindTarget = false;
	

	//boiter = BDice.begin();

	//for (boiter = BDice.begin(); boiter != BDice.end();) {

	//}

	if (turnchr->GetUnitType() == UnitType::MONSTER)//(*boiter).first->GetUnitType() == UnitType::MONSTER)
	{
		TTYPE = MONTURN;

	}
	else if (turnchr->GetUnitType() == UnitType::HERO)
	{
		TTYPE = PLAYERTURN;
	}
			if (TTYPE == MONTURN && turnchr->GetHaveTurn() == true)//(*boiter).first->GetHaveTurn() == true)
			{
				int randomhero;
				randomhero = rand() % C_MGR->GetCharacters().size();
				MselctetChr = C_MGR->GetCharacters()[randomhero];
				turnchr->SetHaveTurn(false);
				if (monfindTarget == false) {
					MselctetChr->SetTargeted(true);
					monfindTarget = true;

				}
					if (monfindTarget == true) {
						turnchr->Attack(MselctetChr);
						turnchr->SetCurrState(State::SKILL1);
						MselctetChr->SetTargeted(false);
						monfindTarget = false;
						MselctetChr = nullptr;

					}
					UiDataManager::GetSingleton()->SetTurnExit(true);
					eltimess = 0;
					return;
				
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
			if (selectedChr->GetHaveTurn() == true) {
				turnchr->SetHaveTurn(false);
			}



			if (!selectedChr)
			{
				selctedSkill = nullptr;
			}
		}



			if (selctedSkill)
			{
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

			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{

				if (PtInRect(&statusZone, g_ptMouse)) {

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
				else if (PtInRect(&characterZone, g_ptMouse))
				{


					if (selectedChr && selctedSkill)
					{
						if (!M_MGR->GetCharacters().empty()) {
							for (int i = 0; i < M_MGR->GetCharacters().size(); i++)
							{
								if (M_MGR->GetCharacters()[i]->GetFixed() == true)
								{
									int attdmg = rand() % selectedChr->GetStat().damage.y + selectedChr->GetStat().damage.x;
									selctedSkill->run(attdmg, M_MGR->GetCharacters()[i]);
									M_MGR->GetCharacters()[i]->SetPos(WINSIZE_X / 2 + 100 * i);


								}
								else
								{

								}
							}
					
							selectedChr->SetSelected(true);
							selectedChr = nullptr;
							return;


						}


					}

				}

			}
		
}

bool DataManager::BattleStages2(CharacterManager* C_MGR, CharacterManager* M_MGR, Character* turnchr)
{
	int num = 0;
	bool monfindTarget = false;
	
	bool itouch = false;
	//boiter = BDice.begin();

	//for (boiter = BDice.begin(); boiter != BDice.end();) {

	//}

	if (turnchr->GetUnitType() == UnitType::MONSTER)//(*boiter).first->GetUnitType() == UnitType::MONSTER)
	{
		TTYPE = MONTURN;

	}
	else if (turnchr->GetUnitType() == UnitType::HERO)
	{
		TTYPE = PLAYERTURN;
	}
	if (TTYPE == MONTURN && turnchr->GetHaveTurn() == true)//(*boiter).first->GetHaveTurn() == true)
	{
		int randomhero;
		randomhero = rand() % C_MGR->GetCharacters().size();
		MselctetChr = C_MGR->GetCharacters()[randomhero];
		turnchr->SetHaveTurn(false);
		if (monfindTarget == false) {
			MselctetChr->SetTargeted(true);
			monfindTarget = true;

		}
		if (monfindTarget == true) {
			eltimess += TimerManager::GetSingleton()->GetElapsedTime();
			turnchr->Attack(MselctetChr);
			turnchr->SetCurrState(State::SKILL1);
			MselctetChr->SetTargeted(false);
			monfindTarget = false;
			MselctetChr = nullptr;

		}
		if (eltimess >= 3.0f) {
			eltimess = 0;
			return true;
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
		if (selectedChr->GetHaveTurn() == true) {
			turnchr->SetHaveTurn(false);
		}



		if (!selectedChr)
		{
			selctedSkill = nullptr;
		}
	}



	if (selctedSkill)
	{
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
	if (itouch == true) {
		eltimess += TimerManager::GetSingleton()->GetElapsedTime();

		if (eltimess > 2.0f) {
			UiDataManager::GetSingleton()->SetTurnExit(true);
			eltimess = 0;
		}
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


			if (selectedChr && selctedSkill)
			{
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
					
					selectedChr->SetSelected(true);
					selectedChr = nullptr;
					return true;

					if (UiDataManager::GetSingleton()->GetTurnExit() == true) {
						UiDataManager::GetSingleton()->SetTurnExit(false);
					}


				}


			}

		}

	}
}




