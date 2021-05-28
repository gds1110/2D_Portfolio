#include "skeleton_bearer.h"
#include "Image.h"
HRESULT skeleton_bearer::Init()
{
	maxFrameArr[State::COMBAT] = 17;

	img = ImageManager::GetSingleton()->AddImage("���̷��汳�� �Ĺ�", "resource/monster/skeleton_bearer/combat/combat.BMP", 3281, 250, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷��汳�� �ǰ�", "resource/monster/skeleton_bearer/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	currstate = State::COMBAT;
	mkinds = MonsterKinds::SKELETON_BEARER;
	size = 0.9;
	return S_OK;

}

void skeleton_bearer::Release()
{
}

void skeleton_bearer::Update()
{
	SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
	MUpdate();
}

void skeleton_bearer::Render(HDC hdc)
{
	img->FrameRender(hdc, pos.x, pos.y + 110, currFrameX, 0, true, size);

}
