#include "Skill.h"
#include "Image.h"
#include "Character.h"
#include "config.h"

HRESULT Skill::Init()
{
	iconImg = nullptr;
	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);

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
	
		
	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);
	

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
	}
}

void Skill::SkillInit()
{
	if (owner->GetUnitType() == UnitType::HERO) {
		switch (type)
		{
		case COMBATSKILL:
			switch (hClass)
			{
			case CRUSADER:
				break;
			case BOUNTYHUNTER:
				break;
			case HIGHWAYMAN:
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
				break;
			case BOUNTYHUNTER:
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
				break;
			case BOUNTYHUNTER:
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
				break;
			case BOUNTYHUNTER:
				break;
			case HIGHWAYMAN:
				break;
			case LEAPER:
				if (skillNum == 5)
				{
					s_info.skillRank = { 1,2 };
					s_info.targetRank = { 1,2 };
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

		}
		if (skillNum == 4) {
			owner->SetCurrState(State::SKILL3);
			if (target->GetMark() == true)
			{
				x = x * 1.5;
			}
			target->Hurt(x);

		}
	}

	else if (owner->GetClass() == BOUNTYHUNTER)
	{
		if (skillNum == 1) {
			owner->SetCurrState(State::SKILL1); 
			target->setStun(true);
			target->Hurt(1);

		}
		if (skillNum == 2) {
			owner->SetCurrState(State::SKILL2);
	
			target->Hurt(x);

		}
		if (skillNum == 5) {
			owner->SetCurrState(State::SKILL3);
			if (target->GetMark() == true)
			{
				x = x * 1.5;
			}
			target->Hurt(x);

		}
		if (skillNum == 6) {
			owner->SetCurrState(State::SKILL4);
			if (target->GetMark() == false) {
				target->setMark(true);
			}
			target->Hurt(1);

		}
	}
	else {
		owner->SetCurrState(State::SKILL1);
		if (target->GetMark() == true)
		{
			x = x * 1.5;
		}
		target->Hurt(x);

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

	}
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
		}
	}
}

StunSkill::StunSkill(Character* owner)
{
	this->owner = owner;

}

void StunSkill::run(int x, Character* target)
{
}
