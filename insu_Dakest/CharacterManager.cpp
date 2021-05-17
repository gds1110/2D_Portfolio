#include "CharacterManager.h"
#include "Image.h"
#include "Character.h"
#include "CommonFunction.h"
#include <algorithm>

HRESULT CharacterManager::Init()
{/*
    v_Heros.resize(4);*/
    index = 0;
    /*for (int i = 0; i < v_Heros.size(); i++)
    {
        v_Heros[i] = new Character();
        v_Heros[i]->Init();
    }*/
 
    return S_OK;
}

HRESULT CharacterManager::Init(int num)
{
   

    return S_OK;
}


void CharacterManager::AddCharacter(Character* chr, UnitType type)
{

    if (v_Characters.size() > 3)
    {
        return;
    }
    else
    {
        if (type == UnitType::HERO) {
            v_Characters.push_back(chr);
            v_Characters[index]->SetType(type);
            v_Characters[index]->Init();
            v_Characters[index]->SetPos((WINSIZE_X / 2 - 100) - (index * 150));
            v_Characters[index]->SetIndex(index);
            index++;
        }
        else if(type == UnitType::MONSTER)
        {
            v_Characters.push_back(chr);
            v_Characters[index]->SetType(type);
            v_Characters[index]->Init();
         
            v_Characters[index]->SetPos((WINSIZE_X / 2 + 100) + (index * 150));
            v_Characters[index]->SetIndex(index);
            index++;
        }

    }
}

int CharacterManager::GetCharPos()
{
    if (!v_Characters.empty())
    {
        return v_Characters[0]->GetPosx();
    }
}


void CharacterManager::Release()
{
    for (int i = 0; i < v_Characters.size(); i++)
    {
        SAFE_RELEASE(v_Characters[i]);
    }
    v_Characters.clear();
}

void CharacterManager::Update()
{
    for (int i = 0; i < v_Characters.size(); i++)
    {
        v_Characters[i]->Update();
    }


    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP)) {
      /*  if (UiDataManager::GetSingleton()->GetSelectedChar())
        {
            for (int i = 0; i < v_Heros.size(); i++)
            {
                if (UiDataManager::GetSingleton()->GetSelectedChar() != v_Heros[i])
                {
                    

               }
            }
        }*/
        swap(v_Characters[0], v_Characters[1]);
        v_Characters[0]->SetPos((WINSIZE_X / 2 - 100) - (0 * 150));
        v_Characters[1]->SetPos((WINSIZE_X / 2 - 100) - (1 * 150));
    }

    

 
}

void CharacterManager::Render(HDC hdc)
{
    for (int i = 0; i < v_Characters.size(); i++)
    {
        v_Characters[i]->Render(hdc);
    }
   
 /*   if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
    {
        for (int i = 0; i < v_Characters.size(); i++)
          {
            v_Characters[i]->Render2(hdc);
         }
    }
    else {
  
    }*/
  /*  }*/
}