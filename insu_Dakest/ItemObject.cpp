#include "ItemObject.h"
#include "Image.h"

HRESULT ItemObject::Init()
{
	itemimg = ImageManager::GetSingleton()->FindImage("아이템목록");

	return S_OK;
}

HRESULT ItemObject::Init(ITEMTYPE itemtype)
{
	itemimg = ImageManager::GetSingleton()->FindImage("아이템목록");

	this->itemtype = itemtype;

	return S_OK;
}

void ItemObject::Release()
{
}

void ItemObject::Update()
{
	SetRect(&rc, pos.x, pos.y, pos.x + 50, pos.y + 100);
}

void ItemObject::Render(HDC hdc)
{
	
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	
	itemimg->FrameRender(hdc, pos.x, pos.y, itemtype, 0);
	wsprintf(szText, "%d", num.x);
	TextOut(hdc, pos.x+40, pos.y+20, szText, strlen(szText));
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	SetBkMode(hdc, TRANSPARENT);

}
