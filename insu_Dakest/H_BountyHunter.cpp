#include "H_BountyHunter.h"
#include "Image.h"
#include "SkillManager.h"
#include "skill.h"
HRESULT H_BountyHunter::Init()
{
    maxFrameArr[State::IDLE] = 18;
    maxFrameArr[State::COMBAT] = 16;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::SKILL1] = 1;
    maxFrameArr[State::SKILL2] = 1;
    maxFrameArr[State::SKILL3] = 1;
    maxFrameArr[State::SKILL4] = 1;

    img = ImageManager::GetSingleton()->AddImage("바운티헌터 컴뱃", "resource/hero/bountyhunter/combat/combat.BMP", 3152, 300, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 워크", "resource/hero/bountyhunter/walk/walk.BMP", 2688, 300, maxFrameArr[State::WALK], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 아이들", "resource/hero/bountyhunter/idle/idle.BMP", 2880, 300, maxFrameArr[State::IDLE], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 아이콘", "resource/hero/bountyhunter/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 스킬셋", "resource/hero/bountyhunter/skill/skillset.BMP", 504, 144,7,2, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 스킬1", "resource/hero/bountyhunter/skill4.BMP", 300, 500,1,1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 스킬2", "resource/hero/bountyhunter/attack1.BMP", 400, 500,1,1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 스킬3", "resource/hero/bountyhunter/skill3.BMP", 700, 500,1,1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 스킬4", "resource/hero/bountyhunter/skill2.BMP", 400, 500,1,1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 피격", "resource/hero/bountyhunter/hurt.BMP", 300, 500,1,1, true, RGB(88, 88, 88));

    currstate = State::IDLE;
    hClass = HCLASS::BOUNTYHUNTER;
    skillSeting();
    
    S_MGR->AddSkill3(CHARGESKILL, 1, 0);
    S_MGR->AddSkill3(COMBATSKILL, 2, 1);
    S_MGR->AddSkill3(COMBATSKILL, 5, 2);
    S_MGR->AddSkill3(COMBATSKILL, 6, 3);
    S_MGR->AddSkill3(SWAPSKILL, 10, 4);
    S_MGR->AddSkill3(NOTURNSKILL, 10, 5);
    return S_OK;
}

void H_BountyHunter::Release()
{
}

void H_BountyHunter::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);

    SharedUpdate();

}

void H_BountyHunter::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x+30, pos.y+140, currFrameX, 0,true,0.8);
  
    //Rectangle(hdc, body.left, body.top, body.right, body.bottom);
}

