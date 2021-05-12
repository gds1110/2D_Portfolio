#include "OverUi.h"
#include "Image.h"
#include "Character.h"
HRESULT OverUi::Init()
{
	selecetedIcon = ImageManager::GetSingleton()->AddImage("선택아이콘", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
	sIconCurrFrame = 0;
	eltimes = 0;
	return S_OK;
}

void OverUi::Release()
{
}

void OverUi::Update()
{
	eltimes += TimerManager::GetSingleton()->GetElapsedTime();
	if (eltimes > 0.3)
	{
		sIconCurrFrame++;
		if (sIconCurrFrame > 1) {
			sIconCurrFrame = 0;
		}
		eltimes = 0;
	}
}

void OverUi::Render(HDC hdc)
{
	selecetedIcon->FrameRender(hdc, UiDataManager::GetSingleton()->GetSelectedChar()->GetPosx()+30, 410, 0, sIconCurrFrame, true);
}
