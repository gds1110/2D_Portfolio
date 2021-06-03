#include "H_Leaper.h"
#include "Image.h"
#include "SkillManager.h"
#include "skill.h"
HRESULT H_Leaper::Init()
{
    maxFrameArr[State::IDLE] = 18;
    maxFrameArr[State::COMBAT] = 16;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::SKILL1] = 1;
    maxFrameArr[State::SKILL2] = 1;
    maxFrameArr[State::SKILL3] = 1;
    maxFrameArr[State::SKILL4] = 1;
    ImageManager::GetSingleton()->AddImage("����ȯ�� ���̵�", "resource/hero/Leaper/idle/idle.BMP", 3600, 300, maxFrameArr[State::IDLE], 1, true, RGB(88, 88, 88));
    img = ImageManager::GetSingleton()->AddImage("����ȯ�� �Ĺ�", "resource/hero/Leaper/combat/combat.BMP", 3248, 300, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ��ũ", "resource/hero/Leaper/walk/walk.BMP", 3232, 300, maxFrameArr[State::WALK], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ������", "resource/hero/Leaper/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ��ų��", "resource/hero/Leaper/skill/skillset.BMP", 504, 144, 7, 2, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ��ų1", "resource/hero/Leaper/skill/chop/hchop.BMP", 600, 450,1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ��ų2", "resource/hero/Leaper/skill1.BMP", 600, 450,1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ��ų3", "resource/hero/Leaper/skill2.BMP", 600, 450,1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ��ų4", "resource/hero/Leaper/skill3.BMP", 600, 450,1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� �ǰ�", "resource/hero/Leaper/hurt.BMP", 400, 500,1, 1, true, RGB(88, 88, 88));

    currstate = State::IDLE;
    hClass = HCLASS::LEAPER;
    skillSeting();

    S_MGR->AddSkill3(COMBATSKILL, 0, 0);
    S_MGR->AddSkill3(ARANGESKILL, 1, 1);
    S_MGR->AddSkill3(COMBATSKILL, 4, 2);
    S_MGR->AddSkill3(HEALSKILL, 5, 3);
    S_MGR->AddSkill3(SWAPSKILL, 10, 4);
    S_MGR->AddSkill3(NOTURNSKILL, 10, 5);


   /* S_MGR->AddSkill(new CombatAttack);
    S_MGR->AddSkill(new ArangeAttack);
    S_MGR->AddSkill(new ChargeAttack);
    S_MGR->AddSkill(new Skill);
    S_MGR->AddSkill(new Skill);*/
    
    size = 0.8f;
    //skillSeting();

	return S_OK;
}

void H_Leaper::Release()
{
}

void H_Leaper::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
    SharedUpdate();   

  

}

void H_Leaper::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x, pos.y + 110, currFrameX, 0, true, 0.9);

}
