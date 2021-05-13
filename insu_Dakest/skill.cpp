#include "skill.h"
#include "Image.h"

HRESULT skill::Init()
{
	iconImg = nullptr;
	return S_OK;
}

void skill::Release()
{
}

void skill::Update()
{
	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);
}

void skill::Render(HDC hdc)
{
	Rectangle(hdc, iconRC.left, iconRC.top, iconRC.right, iconRC.bottom);
	//iconImg->FrameRender(hdc, pos.x, pos.y, slotNum, skillstate, true);
}
