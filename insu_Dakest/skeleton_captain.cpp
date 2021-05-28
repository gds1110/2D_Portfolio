#include "skeleton_captain.h"
#include "Image.h"
HRESULT skeleton_captain::Init()
{
	maxFrameArr[State::COMBAT] = 17;

	img = ImageManager::GetSingleton()->FindImage("½ºÄÌ·¹Åæ Ä¸Æ¾");
	//img = ImageManager::GetSingleton()->AddImage("½ºÄÌ·¹ÅæÄ¸Æ¾ ÄÄ¹î", "resource/monster/skeleton_captain/combat/combat.BMP", 3706, 400, maxFrameArr[State::COMBAT], 1, true, RGB(88, 88, 88));
	//ImageManager::GetSingleton()->AddImage("½ºÄÌ·¹ÅæÄ¸Æ¾ ÇÇ°Ý", "resource/monster/skeleton_captain/defend/hurt.BMP", 400, 500, 1, 1, true, RGB(88, 88, 88));
	currstate = State::COMBAT;
	mkinds = MonsterKinds::SKELETON_CAPTAIN;
	size =1;

	return S_OK;

}

void skeleton_captain::Release()
{
}

void skeleton_captain::Update()
{
	SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
	MUpdate();
}

void skeleton_captain::Render(HDC hdc)
{
	img->FrameRender(hdc, pos.x, pos.y + 50, currFrameX, 0, true, size);

}
