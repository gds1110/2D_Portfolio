#include "Skill.h"
#include "Image.h"
#include "Character.h"

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
{
	Rectangle(hdc, iconRC.left, iconRC.top, iconRC.right, iconRC.bottom);
	if (iconImg) {
		iconImg->FrameRender(hdc, pos.x+10, pos.y+10, skillNum, skillstate, true,0.7);
	}

}

void Skill::MotionRun()
{

}

void CombatAttack::run()
{
	owner->SetCurrState(State::SKILL1);
}

void CombatAttack::run(int x, Character* target)
{
	owner->SetCurrState(State::SKILL1);
	target->SetCurrState(State::HURT);
	//for (int i = 0; i < UiDataManager::GetSingleton()->GetTarGet().size(); i++) {
	//	//UiDataManager::GetSingleton()->GetTarGet()[i].setHp(gethp - 1);
	//}
	//
}
