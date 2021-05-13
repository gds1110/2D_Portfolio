#include "H_Leaper.h"
#include "Image.h"

HRESULT H_Leaper::Init()
{
    maxFrameArr[State::IDLE] = 18;
    maxFrameArr[State::COMBAT] = 16;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::ATTACK1] = 1;
    ImageManager::GetSingleton()->AddImage("����ȯ�� ���̵�", "resource/hero/Leaper/idle/idle.BMP", 3600, 300, maxFrameArr[State::IDLE], 1, true, RGB(88, 88, 88));
    img = ImageManager::GetSingleton()->AddImage("����ȯ�� �Ĺ�", "resource/hero/Leaper/combat/combat.BMP", 3248, 300, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ��ũ", "resource/hero/Leaper/walk/walk.BMP", 3232, 300, maxFrameArr[State::WALK], 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("����ȯ�� ������", "resource/hero/Leaper/icon.BMP", 65, 65, true, RGB(88, 88, 88));

    currstate = State::COMBAT;
    hClass = HCLASS::LEAPER;

	return S_OK;
}

void H_Leaper::Release()
{
}

void H_Leaper::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
    switchSprite();

    IdleCombatUpdate();

    Move();
}

void H_Leaper::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x, pos.y + 80, currFrameX, 0, true, 1);

}
