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
	if (hClass == HCLASS::NONEHCLASS)
	{
		hClass = owner->GetClass();
	}
	iconImg = ImageManager::GetSingleton()->FindImage(UiDataManager::GetSingleton()->GetClassArr()[hClass] + "½ºÅ³¼Â");

	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);
	

	//iconImg=ImageManager::GetSingleton()->FindImage()
}

void Skill::Render(HDC hdc)
{	Rectangle(hdc, iconRC.left, iconRC.top, iconRC.right, iconRC.bottom);
	if (iconImg) {
		iconImg->FrameRender(hdc, pos.x+10, pos.y+10, skillNum, skillstate, true,0.7);
	}

}

void Skill::SkillInit()
{
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
	case NONESKILLTYPE:
		break;
	default:
		break;
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
	owner->SetCurrState(State::SKILL1);
	//target->SetCurrState(State::HURT);
	//target->Hurt();
	target->Hurt(x);
	//for (int i = 0; i < UiDataManager::GetSingleton()->GetTarGet().size(); i++) {
	//	//UiDataManager::GetSingleton()->GetTarGet()[i].setHp(gethp - 1);
	//}
	//
}

ArangeAttack::ArangeAttack(Character* owner)
{
	this->owner = owner;

}
