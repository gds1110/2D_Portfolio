#include "Skill.h"
#include "Image.h"
#include "Character.h"
#include "config.h"

HRESULT Skill::Init()
{
	iconImg = nullptr;
	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);
	tooltip = ImageManager::GetSingleton()->FindImage("스킬툴팁");
	isMouseOver = false;
	return S_OK;
}

void Skill::Release()
{
}

void Skill::Update()
{
	iconImg = ImageManager::GetSingleton()->FindImage(UiDataManager::GetSingleton()->GetClassArr()[hClass] + "스킬셋");

	if (hClass == HCLASS::NONEHCLASS)
	{
		hClass = owner->GetClass();
	}
	if (type == SWAPSKILL)
	{
		iconImg = ImageManager::GetSingleton()->FindImage("스왑스킬");
	}
	if (type == NOTURNSKILL)
	{
		iconImg = ImageManager::GetSingleton()->FindImage("노턴스킬");

	}
	for (int i = 0; i < 8; i++)
	{
		if (i < 4) {
			tipsinfo[i].pos = { (pos.x + 20) - i * 15,pos.y + 40 };
		}
		else
		{
			tipsinfo[i].pos = { (pos.x - 20) + i * 15,pos.y + 40 };
		}
	}
	for (int i = s_info.skillRank.x; i <= s_info.skillRank.y; i++)
	{
		tipsinfo[i].canskill = true;
		tipsinfo[i].ss = PLAYERPOS;
		if (this->GetSkillType() == SWAPSKILL)
		{
			tipsinfo[4-i].canskill = true;
		}
	}
	
	for (int i = s_info.targetRank.x; i <= s_info.targetRank.y; i++)
	{
		tipsinfo[4 + i].canhit = true;
		tipsinfo[4 + i].ss = ENEMYPOS;
		if (this->GetSkillType() == HEALSKILL)
		{
			tipsinfo[4 + i].ss = HEALORMOVE;
		}

	}
	if (this->GetSkillType() == SWAPSKILL)
	{
		for (int i = 0; i < 8; i++)
		{
			tipsinfo[i].ss = HEALORMOVE;
		}
	}

	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);
	
	if (PtInRect(&iconRC, g_ptMouse))
	{
		isMouseOver = true;
	}
	else
	{
		isMouseOver = false;
	}

	//iconImg=ImageManager::GetSingleton()->FindImage()
}

void Skill::Render(HDC hdc)
{	//Rectangle(hdc, iconRC.left, iconRC.top, iconRC.right, iconRC.bottom);
 {
		if (iconImg) {
			if (type == SWAPSKILL)
			{
				//iconImg->FrameRender(hdc, pos.x + 10, pos.y + 10, 1, 1, true, 0.7);
				iconImg->Render2(hdc, pos.x + 10, pos.y + 5, true,0.8);
			}
			else if (type == NOTURNSKILL)
			{
				//iconImg->FrameRender(hdc, pos.x -30, pos.y + 10, 1, 1, true, 0.7);
				iconImg->Render2(hdc, pos.x , pos.y + 5, true, 0.8);


			}
			else {
				iconImg->FrameRender(hdc, pos.x + 10, pos.y + 10, skillNum, skillstate, true, 0.7);
			}
		}

		if (isMouseOver == true)
		{
			tooltip->Render(hdc,pos.x-50,pos.y+25);
			for (int i = 0; i < 8; i++)
			{
				tipsinfo[i].img->FrameRender(hdc, tipsinfo[i].pos.x, tipsinfo[i].pos.y, tipsinfo[i].ss, 0);
			}
			HFONT font,oldfont;
			font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
			oldfont = (HFONT)SelectObject(hdc, font);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));
			wsprintf(szText, "RANGE : %d",s_info.range);
			TextOut(hdc, pos.x-15, pos.y+100, szText, strlen(szText));
			SelectObject(hdc, oldfont);
			DeleteObject(font);

			SetBkMode(hdc, TRANSPARENT);
		}

	}
}

void Skill::SkillInit()
{
	if (owner->GetUnitType() == UnitType::HERO) {
		switch (type)
		{
		case SWAPSKILL:
			s_info.skillRank = { 0,3 };
			s_info.targetRank = { 0,3 };
			s_info.range = 1;
			break;
		case COMBATSKILL:
			switch (hClass)
			{
			case CRUSADER:
				s_info.skillRank = { 0,2 };
				s_info.targetRank = { 0,2 };
				s_info.range = 1;
				break;
			case BOUNTYHUNTER:
				s_info.skillRank = { 0,2 };
				s_info.targetRank = { 0,2 };
				s_info.range = 1;
				break;
			case HIGHWAYMAN:
				s_info.skillRank = { 0,2 };
				s_info.targetRank = { 0,2 };
				s_info.range = 1;
				break;
			case LEAPER:
				if (skillNum == 0) {
					s_info.skillRank = { 0,1 };
					s_info.targetRank = { 0,1 };
					s_info.range = 1;
				}
				if (skillNum == 4)
				{
					s_info.skillRank = { 0,1 };
					s_info.targetRank = { 0,1 };
					s_info.range = 2;
				}
				break;
			case VESTEL:
				s_info.skillRank = { 0,2 };
				s_info.targetRank = { 0,2 };
				s_info.range = 1;
				break;
			case NONEHCLASS:
				break;
			default:
				break;
			}
			break;
		case ARANGESKILL:
			switch (hClass)
			{
			case CRUSADER:
				s_info.skillRank = { 0,2 };
				s_info.targetRank = { 1,3 };
				s_info.range = 2;
				break;
			case BOUNTYHUNTER:
				s_info.skillRank = { 0,2 };
				s_info.targetRank = { 1,3 };
				s_info.range = 2;
				break;
			case HIGHWAYMAN:
				break;
			case LEAPER:
				s_info.skillRank = { 0,1 };
				s_info.targetRank = { 1,3 };
				s_info.range = 2;
				break;
			case VESTEL:
				break;
			case NONEHCLASS:
				break;
			default:
				break;
			}
			break;
		case CHARGESKILL:
			switch (hClass)
			{
			case CRUSADER:
				s_info.skillRank = { 1,3 };
				s_info.targetRank = { 1,3 };
				s_info.range = 1;

				break;
			case BOUNTYHUNTER:

				s_info.skillRank = { 1,3 };
				s_info.targetRank = { 1,3 };
				s_info.range = 1;

				break;
			case HIGHWAYMAN:
				break;
			case LEAPER:
				break;
			case VESTEL:
				break;
			case NONEHCLASS:
				break;
			default:
				break;
			}
			break;
		case HEALSKILL:
			switch (hClass)
			{
			case CRUSADER:
				s_info.skillRank = { 0,3, };
				s_info.targetRank = { 0,3 };
				s_info.range = 1;
				break;
			case BOUNTYHUNTER:
				break;
			case HIGHWAYMAN:
				break;
			case LEAPER:
				if (skillNum == 5)
				{
					s_info.skillRank = { 0,1 };
					s_info.targetRank = { 0,1 };
					s_info.range = 1;
				}
				break;
			case VESTEL:
				if (skillNum == 5)
				{
					s_info.skillRank = { 0,3 };
					s_info.targetRank = { 0,3 };
					s_info.range = 1;
				}
				if (skillNum == 6)
				{
					s_info.skillRank = { 2,3 };
					s_info.targetRank = { 0,4 };
					s_info.range = 4;
				}
				break;
			case NONEHCLASS:
				break;
			default:
				break;
			}
			break;
		case NONESKILLTYPE:
			break;
		default:
			break;
		}
	}
	else if(owner->GetUnitType()==UnitType::MONSTER)
	{
		switch (type)
		{
		case COMBATSKILL:
			switch (mkinds)
			{
			case SKELETON_ARBALISTAR:
				break;
			case SKELETON_BEARER:
				break;
			case SKELETON_CAPTAIN:
				break;
			case SKELETON_COMMON:
				break;
			case NONEKINDS:
				break;
			default:
				break;
			}
			break;
		case ARANGESKILL:
			switch (mkinds)
			{
			case SKELETON_ARBALISTAR:
				break;
			case SKELETON_BEARER:
				break;
			case SKELETON_CAPTAIN:
				break;
			case SKELETON_COMMON:
				break;
			case NONEKINDS:
				break;
			default:
				break;
			}
			break;
		case CHARGESKILL:
			switch (mkinds)
			{
			case SKELETON_ARBALISTAR:
				break;
			case SKELETON_BEARER:
				break;
			case SKELETON_CAPTAIN:
				break;
			case SKELETON_COMMON:
				break;
			case NONEKINDS:
				break;
			default:
				break;
			}
			break;
		case NONESKILLTYPE:
			switch (mkinds)
			{
			case SKELETON_ARBALISTAR:
				break;
			case SKELETON_BEARER:
				break;
			case SKELETON_CAPTAIN:
				break;
			case SKELETON_COMMON:
				break;
			case NONEKINDS:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	//switch (hClass)
	//{
	//case CRUSADER:
	//	break;
	//case BOUNTYHUNTER:
	//	break;
	//case HIGHWAYMAN:
	//	break;
	//case LEAPER:
	//	s_info.skillRank = { 0,1 };
	//	s_info.targetRank = { 0,1 };
	//	s_info.range = 1;
	//	break;
	//case VESTEL:
	//	break;
	//case NONEHCLASS:
	//	break;
	//default:
	//	break;
	//}

}

void Skill::SkillPosState()
{
}



void Skill::run(int x, Character* target)
{
	
}

void Skill::MotionRun()
{

}

Skill::Skill()
{
	skillstate = SkillState::ON;
	hClass = HCLASS::NONEHCLASS;// owner->GetClass();
	//hClass = owner->GetClass();

	pos.y = 530;
}

Skill::Skill(Character* owner)
{
	skillstate = SkillState::ON;
	//hClass = HCLASS::NONEHCLASS; owner->GetClass();
	hClass = owner->GetClass();

	pos.y = 530;
}

CombatAttack::CombatAttack()
{
}

CombatAttack::CombatAttack(Character* owner)
{
	this->owner = owner;
}

void CombatAttack::run()
{
	owner->SetCurrState(State::SKILL1);
}

void CombatAttack::run(int x, Character* target)
{
	//0145
	if (owner->GetClass() == LEAPER)
	{
		if (skillNum == 0) {
			owner->SetCurrState(State::SKILL1);
			target->Hurt(x);
			target->setdmgorhear(x, false);

		}
		if (skillNum == 4) {
			owner->SetCurrState(State::SKILL2);
			if (target->GetMark() == true)
			{
				target->setMark(false);

				x = x * 1.5;
			}
			target->Hurt(x);
			target->setdmgorhear(x, false);

		}
	}

	else if (owner->GetClass() == BOUNTYHUNTER)
	{
		if (skillNum == 1) {
			owner->SetCurrState(State::SKILL1); 
			target->setStun(true);
			target->SetFxon(Character::FxType::STUNFX);
			target->Hurt(1);
			target->setdmgorhear(x, false);

		}
		if (skillNum == 2) {
			owner->SetCurrState(State::SKILL2);
	
			target->Hurt(x);
			target->setdmgorhear(x, false);

		}
		if (skillNum == 5) {
			owner->SetCurrState(State::SKILL3);
			if (target->GetMark() == true)
			{
				target->setMark(false);

				x = x * 1.5;
			}
			target->Hurt(x);
			target->setdmgorhear(x, false);

		}
		if (skillNum == 6) {
			owner->SetCurrState(State::SKILL4);
			if (target->GetMark() == false) {
				target->setMark(true);
				target->SetFxon(Character::FxType::MARKFX);
			}
			target->Hurt(1);
			
			target->setdmgorhear(x, false);

		}
	}
	else {
		owner->SetCurrState(State::SKILL1);
		if (target->GetMark() == true)
		{
			target->setMark(false);
			x = x * 1.5;
		}
		target->Hurt(x);
		target->setdmgorhear(x, false);


	}
	//target->SetCurrState(State::HURT);
	//target->Hurt();
	//for (int i = 0; i < UiDataManager::GetSingleton()->GetTarGet().size(); i++) {
	//	//UiDataManager::GetSingleton()->GetTarGet()[i].setHp(gethp - 1);
	//}
	//
}

ArangeAttack::ArangeAttack(Character* owner)
{
	this->owner = owner;

}

void ArangeAttack::run(int x, Character* target)
{
	if (owner->GetClass() == LEAPER)
	{
		owner->SetCurrState(State::SKILL2);
		target->Hurt(x);
		target->setdmgorhear(x, false);

	}

	owner->SetCurrState(State::SKILL2);
	target->Hurt(x);
	target->setdmgorhear(x, false);
}

HealSkill::HealSkill(Character* owner)
{
	this->owner = owner;

}

void HealSkill::run(int x, Character* target)
{

	if (owner->GetClass() == LEAPER)
	{
		if (skillNum == 5) {
			int temphp = target->GetStat().hp + x;
			if (temphp > target->GetStat().maxHp)
			{
				target->SetHp(target->GetStat().maxHp);
			}
			else
			{
				target->SetHp(target->GetStat().hp + x);
				target->setdmgorhear(x, true);

			}
		}
	}
		else if (owner->GetClass() == VESTEL&&skillNum==6)
	{
		int temphp = target->GetStat().hp + 1;
		if (temphp >= target->GetStat().maxHp)
		{
			target->SetHp(target->GetStat().maxHp);
		}
		else
		{
			target->SetHp(target->GetStat().hp + 1);
			target->setdmgorhear(x, true);

		}
	}
	else {
		int temphp = target->GetStat().hp + x;
		if (temphp > target->GetStat().maxHp)
		{
			target->SetHp(target->GetStat().maxHp);
		}
		else
		{
			target->SetHp(target->GetStat().hp + x);
			target->setdmgorhear(x, true);

		}
	}
}

StunSkill::StunSkill(Character* owner)
{
	this->owner = owner;

}

void StunSkill::run(int x, Character* target)
{
	if (owner->GetClass() == VESTEL)
	{
		if (target->GetStun())
		{
			target->setStun(true);
			target->Hurt(1);
		}
		owner->SetCurrState(SKILL1);
	}
	target->setdmgorhear(x, false);

}

ChargeAttack::ChargeAttack(Character* owner)
{
	this->owner = owner;
}

void ChargeAttack::run(int x, Character* target)
{
	if (owner->GetClass() == BOUNTYHUNTER)
	{
		if (skillNum == 1) {
			owner->SetCurrState(State::SKILL1);
			target->setStun(true);
			target->SetFxon(Character::FxType::STUNFX);
			target->Hurt(1);

		}
		owner->SetCurrState(State::SKILL1);

	}
	else if(owner->GetClass()==CRUSADER)
	{
		owner->SetCurrState(State::SKILL3);
		target->setStun(true);
		target->SetFxon(Character::FxType::STUNFX);
		target->Hurt(1);
	}
	target->setdmgorhear(x, false);

}

SwapSkill::SwapSkill(Character* owner)
{
	this->owner = owner;
}

void SwapSkill::run(int x, Character* target)
{
}
