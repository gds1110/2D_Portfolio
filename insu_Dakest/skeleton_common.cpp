#include "skeleton_common.h"
#include "Image.h"
HRESULT skeleton_common::Init()
{
	maxFrameArr[State::COMBAT] = 14;

	/*img = ImageManager::GetSingleton()->AddImage("½ºÄÌ·¹ÅæÄ¿¸Õ ÄÄ¹î", "resource/monster/skeleton_common/combat/combat.BMP", 2324, 250, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("½ºÄÌ·¹ÅæÄ¿¸Õ ÇÇ°Ý", "resource/monster/skeleton_common/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));*/
	img = ImageManager::GetSingleton()->FindImage("½ºÄÌ·¹ÅæÄ¿¸Õ ÄÄ¹î");
	currstate = State::COMBAT;
	mkinds = MonsterKinds::SKELETON_COMMON;
	size = 0.8f;

	return S_OK;

}

void skeleton_common::Release()
{
}

void skeleton_common::Update()
{
	SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
	MUpdate();
}

void skeleton_common::Render(HDC hdc)
{
	if(img)
	img->FrameRender(hdc, pos.x, pos.y + 130, currFrameX, 0, true, 0.9f);

}
