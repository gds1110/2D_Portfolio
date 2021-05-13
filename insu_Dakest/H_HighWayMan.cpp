#include "H_HighWayMan.h"
#include "Image.h"
HRESULT H_HighWayMan::Init()
{
    ImageManager::GetSingleton()->AddImage("��󰭵� ���̵�", "resource/hero/highwayman/idle/idle.BMP", 2745, 300, 15, 1, true, RGB(88, 88, 88));
    img = ImageManager::GetSingleton()->AddImage("��󰭵� �Ĺ�", "resource/hero/highwayman/combat/combat.BMP", 2646, 300, 14, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("��󰭵� ��ũ", "resource/hero/highwayman/walk/walk.BMP", 2848, 300, 16, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("��󰭵� ������", "resource/hero/highwayman/icon.BMP", 65, 65, true, RGB(88, 88, 88));

    maxFrameArr[State::IDLE] = 15;
    maxFrameArr[State::COMBAT] = 14;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::ATTACK1] = 1;
    currstate = State::COMBAT;
    hClass = HCLASS::HIGHWAYMAN;
	return S_OK;
}

void H_HighWayMan::Release()
{
}

void H_HighWayMan::Update()
{

    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
    switchSprite();

    IdleCombatUpdate();

    Move();
}

void H_HighWayMan::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x+30, pos.y + 110, currFrameX, 0, true, 0.9);
    //Rectangle(hdc, body.left, body.top, body.right, body.bottom);
}
