#include "skeleton_arbalistar.h"
#include "Image.h"
HRESULT skeleton_arbalistar::Init()
{
	maxFrameArr[State::COMBAT] = 15;
	img = ImageManager::GetSingleton()->FindImage("���̷����ó �Ĺ�");

	/*img = ImageManager::GetSingleton()->AddImage("���̷����ó �Ĺ�", "resource/monster/skeleton_arbalista/combat/combat.BMP", 2115, 250, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷����ó �ǰ�", "resource/monster/skeleton_arbalista/defend/hurt.BMP", 300, 400,1,1, true, RGB(88, 88, 88));*/
	currstate = State::COMBAT;
	mkinds = MonsterKinds::SKELETON_ARBALISTAR;
	size = 0.9;
	return S_OK;
}

void skeleton_arbalistar::Release()
{
}

void skeleton_arbalistar::Update()
{
	SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
	MUpdate();
	/*IdleCombatUpdate();
	MswitchSprite();
	abliiltyUpdate();*/

}

void skeleton_arbalistar::Render(HDC hdc)
{
	img->FrameRender(hdc, pos.x, pos.y + 110, currFrameX, 0, true, size);
	//Rectangle(hdc, body.left, body.top, body.right, body.bottom);
}
