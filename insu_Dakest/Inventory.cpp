#include "Inventory.h"
#include "Image.h"
#include "ItemObject.h"

HRESULT Inventory::Init()
{
    img = ImageManager::GetSingleton()->FindImage("인벤토리");
    index = 0;
    return S_OK;
}

void Inventory::Release()
{
}

void Inventory::Update()
{
    list<ItemObject>::iterator it;

    SetRect(&closeButton, pos.x + 445, pos.y + 110, pos.x + 480, pos.y + 160);
    SetRect(&openButton, pos.x + 445, pos.y + 165, pos.x + 480, pos.y + 215);


    if (UiDataManager::GetSingleton()->GetIShome() == true)
    {
        isOpen = true;
        for (it = inventoryList.begin(); it != inventoryList.end(); ++it)
        {
            (*it).SetPos({ 545 + (*it).GetIndex() * 55,360 });
        }
    }
    else if(UiDataManager::GetSingleton()->GetIShome() == false)
    {
        for (it = inventoryList.begin(); it != inventoryList.end(); ++it)
        {
            (*it).SetPos({ pos.x+10 + (*it).GetIndex() * 55,pos.y+17 });

        }
    }
}

void Inventory::Render(HDC hdc)
{
    if (isOpen==true) {
        img->Render(hdc, pos.x, pos.y);
        list<ItemObject>::iterator it;

        for (it = inventoryList.begin(); it != inventoryList.end(); ++it)
        {
            (*it).Render(hdc);
        }
    }
}
void Inventory::AddItem(ItemObject item)
{
    bool check = false;
    list<ItemObject>::iterator it;
    
    list<ItemObject>::iterator it2;
    it2 = inventoryList.end();
    if (inventoryList.begin() == inventoryList.end())
    {
        ItemObject temp = item;
        temp.SetItemNum(1);
        temp.setIndex(index);
        index++;
        inventoryList.push_back(temp);
        return;
    }

    for (it = inventoryList.begin(); it != inventoryList.end();++it)
    {   
        if ((*it).GetType() == item.GetType())
        {
            if ((*it).GetItemNum().x < 8)
            {

                (*it).SetItemNum((*it).GetItemNum().x + 1);
                return;
              
            }
            check = true;

        }
   /*     if (it == (--it2)&& (*it).GetType() != item.GetType())
        {
            ItemObject temp = item;
            temp.SetItemNum(1);
            inventoryList.push_back(temp);
            return;
        }
        */
    }
    if (check == true)
    {
        ItemObject temp = item;
        temp.SetItemNum(1);
        temp.setIndex(index);
        index++;
        inventoryList.push_back(temp);
        return;
    }
    if (check == false)
    {
        ItemObject temp = item;
        temp.SetItemNum(1);
        temp.setIndex(index);
        index++;
        inventoryList.push_back(temp);
        return;
    }

    return;
}

void Inventory::Delete(ItemObject item)
{
    list<ItemObject>::iterator it;
    for (it = inventoryList.begin(); it != inventoryList.end(); it++)
    {
        if ((*it).GetType() == item.GetType())
        {
            if ((*it).GetItemNum().x == 1)
            {
                inventoryList.erase(it);
                break;
            }
            else
            {
                (*it).SetItemNum((*it).GetItemNum().x - 1);
                break;
            }
        }
    }

    return;
}
