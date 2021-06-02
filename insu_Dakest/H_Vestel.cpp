#include "H_Vestel.h"
#include "Image.h"
#include "SkillManager.h"
#include "skill.h"
HRESULT H_Vestel::Init()
{
    maxFrameArr[State::IDLE] = 18;
    maxFrameArr[State::COMBAT] = 15;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::SKILL1] = 1;
    ImageManager::GetSingleton()->AddImage("���� ���̵�", "resource/hero/Vestel/idle/idle.BMP", 3420, 300, maxFrameArr[State::IDLE], 1, true, RGB(88, 88, 88));
    img = ImageManager::GetSingleton()->AddImage("���� �Ĺ�", "resource/hero/Vestel/combat/combat.BMP", 2565, 300, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("���� ��ũ", "resource/hero/Vestel/walk/walk.BMP", 3072, 300, maxFrameArr[State::WALK], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("���� ������", "resource/hero/Vestel/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("���� �ǰ�", "resource/hero/Vestel/hurt.BMP", 373, 556,1,1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("���� ��ų��", "resource/hero/Vestel/skill/skills.BMP", 504, 144, 7, 2, true, RGB(88, 88, 88));
    currstate = State::IDLE;
    hClass = HCLASS::VESTEL;
    skillSeting();
    S_MGR->AddSkill3(STUNSKILL, 0, 0);
    S_MGR->AddSkill3(COMBATSKILL, 4, 1);
    S_MGR->AddSkill3(HEALSKILL, 5, 2);
    S_MGR->AddSkill3(HEALSKILL, 6, 3);
    S_MGR->AddSkill3(SWAPSKILL, 10, 4);
    S_MGR->AddSkill3(NOTURNSKILL, 11, 5);
   

	return S_OK;
}

void H_Vestel::Release()
{
}

void H_Vestel::Update()
{
   
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
    SharedUpdate();   

}

void H_Vestel::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x+30, pos.y + 140, currFrameX, 0, true, 0.8);
   
   // Rectangle(hdc, body.left, body.top, body.right, body.bottom);
}
