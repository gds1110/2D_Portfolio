#include "Skill.h"
#include "Image.h"

HRESULT Skill::Init()
{
	iconImg = nullptr;
	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);

	return S_OK;
}

void Skill::Release()
{
}

void Skill::Update()
{
	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);
}

void Skill::Render(HDC hdc)
{
	Rectangle(hdc, iconRC.left, iconRC.top, iconRC.right, iconRC.bottom);
	//iconImg->FrameRender(hdc, pos.x, pos.y, slotNum, Skillstate, true);
}
