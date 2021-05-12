#include "UnderUi.h"
#include "Image.h"
#include "Character.h"
HRESULT UnderUi::Init()
{
	underUi = ImageManager::GetSingleton()->AddImage("유아이", "resource/dungeon/UI/D_under_ui.BMP", 1280, 240, false);
	//underIcon = ImageManager::GetSingleton()->FindImage("크루세이더 아이콘");
	underIcon = nullptr;
	return S_OK;
}

void UnderUi::Release()
{

}

void UnderUi::Update()
{
	
	if (UiDataManager::GetSingleton()->GetSelectedChar())
	{
		
		iconKey = UiDataManager::GetSingleton()->GetSelectedChar()->GetClassArr()[UiDataManager::GetSingleton()->GetSelectedChar()->GetClass()] + "아이콘";
		underIcon = ImageManager::GetSingleton()->FindImage(iconKey);
	}
}

void UnderUi::Render(HDC hdc)
{
	underUi->Render(hdc, 0, WINSIZE_Y - WINSIZE_Y / 3);
	if (underIcon) {
		underIcon->Render2(hdc, 210, WINSIZE_Y - WINSIZE_Y / 3 + 50, true, 0.5);
	}
}
