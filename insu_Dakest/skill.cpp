#include "Skill.h"
#include "Image.h"
#include "Character.h"

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
	iconImg = ImageManager::GetSingleton()->FindImage(UiDataManager::GetSingleton()->GetClassArr()[hClass] + "½ºÅ³");

	SetRect(&iconRC, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);
	

	//iconImg=ImageManager::GetSingleton()->FindImage()
}

void Skill::Render(HDC hdc)
{
	Rectangle(hdc, iconRC.left, iconRC.top, iconRC.right, iconRC.bottom);
	if (iconImg) {
		iconImg->FrameRender(hdc, pos.x+10, pos.y+10, skillNum, skillstate, true,0.7);
	}

}