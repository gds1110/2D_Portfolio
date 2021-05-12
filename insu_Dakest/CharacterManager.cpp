#include "CharacterManager.h"
#include "Image.h"
#include "Character.h"
#include "H_BountyHunter.h"
#include "H_Crusader.h"
#include "H_HighWayMan.h"
#include "H_Leaper.h"
#include "H_Vestel.h"

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
    v_Heros.resize(num);
    for (int i = 0; i < v_Heros.size(); i++)
    {
        v_Heros[i] = new Character();
        v_Heros[i]->Init();
        v_Heros[i]->SetPos(WINSIZE_X/2-(i*200));
        index++;
    }

    return S_OK;
}

void CharacterManager::AddHero(Character* chr)
{

    vector<Character*>::iterator it;
    if (v_Heros.size() > 3)
    {
        return;
    }
    else
    {

        v_Heros.push_back(chr);
      /*  (*it) = v_Heros.back();
        (*it)->Init();
        (*it)->SetPos(WINSIZE_X / 2 - (index * 200));*/
        v_Heros[index]->Init();
        //v_Heros[index]->SetPos(WINSIZE_X / 2-(index * 100));
        //v_Heros[index]->SetPos(WINSIZE_X / 2-(posarray[index]));
        v_Heros[index]->SetPos((WINSIZE_X / 2-100)-(index*150));
        index++;

    }

}

int CharacterManager::GetHeroPos()
{
    if (!v_Heros.empty())
    {
        return v_Heros[0]->GetPosx();
    }
}

void CharacterManager::Release()
{
    for (int i = 0; i < v_Heros.size(); i++)
    {
        SAFE_RELEASE(v_Heros[i]);
    }
    v_Heros.clear();
}

void CharacterManager::Update()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {

       
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
    {
      
    }


    for (int i = 0; i < v_Heros.size(); i++)
    {
        v_Heros[i]->Update();
    }


    //vector<Character*>::iterator it;
    //for (it = v_Heros.begin(); it < v_Heros.end(); it++)
    //{
    //    (*it)->Update();
    //}
}

void CharacterManager::Render(HDC hdc)
{
   
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
    {
        for (int i = 0; i < v_Heros.size(); i++)
          {
                 v_Heros[i]->Render2(hdc);
         }
    }
    else {
        vector<Character*>::iterator it;
        for (it = v_Heros.begin(); it < v_Heros.end(); it++)
        {

            (*it)->Render(hdc);
            
        }
    }
  /*  }*/
}
