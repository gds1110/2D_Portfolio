#include "H_BountyHunter.h"
#include "Image.h"

HRESULT H_BountyHunter::Init()
{
    maxFrameArr[State::IDLE] = 18;
    maxFrameArr[State::COMBAT] = 16;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::ATTACK1] = 1;
    img = ImageManager::GetSingleton()->AddImage("바운티헌터 컴뱃", "resource/hero/bountyhunter/combat/combat.BMP", 3152, 300, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 워크", "resource/hero/bountyhunter/walk/walk.BMP", 2688, 300, maxFrameArr[State::WALK], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 아이들", "resource/hero/bountyhunter/idle/idle.BMP", 2880, 300, maxFrameArr[State::IDLE], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 아이콘", "resource/hero/bountyhunter/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 스킬", "resource/hero/bountyhunter/skill/skillset.BMP", 504, 144,7,2, true, RGB(88, 88, 88));
    currstate = State::COMBAT;
    hClass = HCLASS::BOUNTYHUNTER;
    skillSeting();


    return S_OK;
}

void H_BountyHunter::Release()
{
}

void H_BountyHunter::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);

    SharedUpdate();
    IdleCombatUpdate();
    /*  switchSprite();

      IdleCombatUpdate();

      Move();*/
}

void H_BountyHunter::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x+30, pos.y+110, currFrameX, 0,true,0.9);
    //Rectangle(hdc, body.left, body.top, body.right, body.bottom);
}

