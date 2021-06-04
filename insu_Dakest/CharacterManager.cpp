#include "CharacterManager.h"
#include "Image.h"
#include "Character.h"
#include "CommonFunction.h"
#include <algorithm>
#include "skeleton_arbalistar.h"
#include "skeleton_bearer.h"
#include "skeleton_captain.h"
#include "skeleton_common.h"

HRESULT CharacterManager::Init()
{
    index = 0;
 
    timers = 0;
    return S_OK;
}

HRESULT CharacterManager::Init(int num)
{
    timers = 0;

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
            v_Characters[index]->SetCurrState(State::IDLE);

            v_Characters[index]->SetIndex(index);
            v_Characters[index]->SetPos((WINSIZE_X / 2 - 100) - (index * 150));
            index++;
        }
        else if(type == UnitType::MONSTER)
        {
            v_Characters.push_back(chr);
            v_Characters[index]->SetType(type);
            v_Characters[index]->Init();
            v_Characters[index]->SetIndex(index);
            v_Characters[index]->SetPos((WINSIZE_X / 2 + 100) + (index * 150));
            index++;
        }

    }
}
void CharacterManager::AddCharacter2(Character* chr, int indexx, bool isroster, UnitType type)
{
    if (type == UnitType::HERO) {
        v_Characters.push_back(chr);
        v_Characters[index]->SetType(type);
        v_Characters[index]->Init();
        v_Characters[index]->SetIconPos({ WINSIZE_X / 2 + 400,50 + index * 70 });
        v_Characters[index]->RosterInit();
      
      
       /* rosterBg->Render(hdc, WINSIZE_X / 2 + 400, 50 + index * 70);
        rosterIcon->Render(hdc, WINSIZE_X / 2 + 400, 50 + index * 70);*/
        v_Characters[index]->SetIndex(index);
        
        index++;
    }

}
void CharacterManager::AddMonster(int charIndex)
{

    if (v_Characters.size() > 3)
    {
        return;
    }
    else
    {
       
        switch (charIndex)  
        {
        case 0:
            v_Characters.push_back(new skeleton_arbalistar);

            break;
        case 1:
            v_Characters.push_back(new skeleton_common);

            break;
        case 2:
            v_Characters.push_back(new skeleton_captain);

            break;
        case 3:
            v_Characters.push_back(new skeleton_common);
            break;

        default:
            break;
        }
            v_Characters[index]->SetType(UnitType::MONSTER);
            v_Characters[index]->Init();
            v_Characters[index]->SetIndex(index);
            v_Characters[index]->SetPos((WINSIZE_X / 2 + 100) + (index * 150));
            index++;    
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
        v_Characters[i]->SetIndex(i);
        v_Characters[i]->Update();
        if (UiDataManager::GetSingleton()->GetBattleState()==true)
        {
            v_Characters[i]->SetCurrState(State::COMBAT);
        }
        if (v_Characters[i]->GetCurrState() == State::COMBAT && UiDataManager::GetSingleton()->GetBattleState() == false)
        {//
            v_Characters[i]->SetCurrState(State::IDLE);
        }
        else
        {

        }
    }
   
    for (itChr = v_Characters.begin(); itChr != v_Characters.end();)
    {
        if ((*itChr)->GetDead() == true) {
            itChr = v_Characters.erase(itChr);

            break;
        }
    
        else {
            itChr++;
        }
    }
    

 
}

void CharacterManager::Render(HDC hdc)
{
   
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDead() == false) {

            v_Characters[i]->BehindFxRender(hdc);
        }

    }
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDead()==false) {
            if (v_Characters[i]->GetDepth() == 1)
            {
                v_Characters[i]->Render(hdc);
               // v_Characters[i]->ShareRender(hdc);


            }
        }
    }
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDead() == false){

            if (v_Characters[i]->GetDepth() == 2)
            {
                v_Characters[i]->Render(hdc);
              //  v_Characters[i]->ShareRender(hdc);

            }
        }
    }
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDead() == false) {

            if (v_Characters[i]->GetDepth() == 3)
            {
                v_Characters[i]->Render(hdc);
               // v_Characters[i]->ShareRender(hdc);


            }
        }
    }
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDead() == false) {
     
                v_Characters[i]->ShareRender(hdc);   
        }

    }
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDead() == false) {

            v_Characters[i]->FrontFxRender(hdc);
            v_Characters[i]->FontRender(hdc);
        }

    }

}