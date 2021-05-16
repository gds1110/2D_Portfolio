#include "H_Vestel.h"
#include "Image.h"

HRESULT H_Vestel::Init()
{
    maxFrameArr[State::IDLE] = 18;
    maxFrameArr[State::COMBAT] = 15;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::ATTACK1] = 1;
    ImageManager::GetSingleton()->AddImage("���� ���̵�", "resource/hero/Vestel/idle/idle.BMP", 2745, 300, maxFrameArr[State::IDLE], 1, true, RGB(88, 88, 88));
    img = ImageManager::GetSingleton()->AddImage("���� �Ĺ�", "resource/hero/Vestel/combat/combat.BMP", 2565, 300, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("���� ��ũ", "resource/hero/Vestel/walk/walk.BMP", 3072, 300, maxFrameArr[State::WALK], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("���� ������", "resource/hero/Vestel/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("���� ��ų", "resource/hero/Vestel/skill/skillset.BMP", 504, 144, 7, 2, true, RGB(88, 88, 88));


    currstate = State::COMBAT;
    hClass = HCLASS::VESTEL;
    skillSeting();

	return S_OK;
}

void H_Vestel::Release()
{
}

void H_Vestel::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
    SharedUpdate();   
    IdleCombatUpdate();

    /*  switchSprite();

      IdleCombatUpdate();

      Move();*/
}

void H_Vestel::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x+30, pos.y + 110, currFrameX, 0, true, 0.9);
    
   // Rectangle(hdc, body.left, body.top, body.right, body.bottom);
}
