#include "MonsterManager.h"
#include "Monster.h"
HRESULT MonsterManager::Init()
{
    index = 0;
	return S_OK;
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
    for (int i = 0; i < v_Monsetr.size(); i++)
    {
        v_Monsetr[i]->Update();
    }
}

void MonsterManager::Render(HDC hdc)
{
    for (int i = 0; i < v_Monsetr.size(); i++)
    {
        v_Monsetr[i]->Render(hdc);
    }
}

void MonsterManager::AddMonster(Monster* mon)
{
    if (v_Monsetr.size() > 3)
    {
        return;
    }
    else
    {

        v_Monsetr.push_back(mon);
        /*  (*it) = v_Heros.back();
          (*it)->Init();
          (*it)->SetPos(WINSIZE_X / 2 - (index * 200));*/
        v_Monsetr[index]->Init();
        //v_Heros[index]->SetPos(WINSIZE_X / 2-(index * 100));
        //v_Heros[index]->SetPos(WINSIZE_X / 2-(posarray[index]));
        v_Monsetr[index]->SetPos((WINSIZE_X / 2 + 100) + (index * 150));
        v_Monsetr[index]->SetIndex(index);
        index++;

    }

}
