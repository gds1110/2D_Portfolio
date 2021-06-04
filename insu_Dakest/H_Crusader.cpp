#include "H_Crusader.h"
#include "Image.h"
#include "CommonFunction.h"
#include "SkillManager.h"
#include "skill.h"
HRESULT H_Crusader::Init()
{

    maxFrameArr[State::IDLE] = 33;
    maxFrameArr[State::COMBAT] = 15;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::SKILL1] = 1;
    img = ImageManager::GetSingleton()->AddImage("크루세이더 컴뱃", "resource/hero/crusader/combat/combat.BMP", 2115, 300,15,1,true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 워크", "resource/hero/crusader/walk/walk.BMP", 2896, 300, 16, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 아이들", "resource/hero/crusader/idle/idle.BMP", 5808, 300, 33, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 아이콘", "resource/hero/crusader/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 기본공격", "resource/hero/crusader/attack.BMP", 295, 295,1,1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 스킬셋", "resource/hero/crusader/skill/skillset.BMP", 504, 144, 7, 2, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 피격", "resource/hero/crusader/hurt.BMP", 300, 500, 1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 스킬1", "resource/hero/crusader/attack.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 스킬2", "resource/hero/crusader/skill2.BMP", 402, 610, 1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 스킬3", "resource/hero/crusader/skill3.BMP", 841, 465, 1, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 스킬4", "resource/hero/crusader/heal.BMP", 329, 600, 1, 1, true, RGB(88, 88, 88));

    currstate = State::IDLE;
    hClass = HCLASS::CRUSADER;
    skillSeting();

    S_MGR->AddSkill3(COMBATSKILL, 0, 0);
    S_MGR->AddSkill3(ARANGESKILL, 1, 1);
    S_MGR->AddSkill3(CHARGESKILL, 5, 2);
    S_MGR->AddSkill3(HEALSKILL, 4, 3);
    S_MGR->AddSkill3(SWAPSKILL, 10, 4);
    S_MGR->AddSkill3(NOTURNSKILL, 10, 5);

    return S_OK;
}

void H_Crusader::Release()
{
}

void H_Crusader::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
  
   
   SharedUpdate();

  /*  if (pos.x < WINSIZE_X / 2)
    {

        pos.x += 2;
    }*/
  //  Move();
}

void H_Crusader::Render(HDC hdc)
{
    if (UiDataManager::GetSingleton()->GetBattleState() == true) {
        img->FrameRender(hdc, pos.x + 30, pos.y + 80, currFrameX, 0, true, 1);
    }
    else
    {
        img->FrameRender(hdc, pos.x + 30, pos.y + 110, currFrameX, 0, true, 0.9);

    }
    //Rectangle(hdc, body.left, body.top, body.right, body.bottom);

       // RenderRectToCenter(hdc, pos.x, pos.y + 50, 80, 300);
}
