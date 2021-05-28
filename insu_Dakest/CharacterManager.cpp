#include "CharacterManager.h"
#include "Image.h"
#include "Character.h"
#include "CommonFunction.h"
#include <algorithm>

HRESULT CharacterManager::Init()
{
    index = 0;
 
 
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
            v_Characters[index]->SetCurrState(State::COMBAT);

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
   

  /*  for (int i = 0; i < v_Characters.size(); i++)
    {
        (*v_Characters.begin()+i)->SetIndex(i);
    }*/

    //if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
    //{
    //    for (int i = 0; i < v_Characters.size(); i++)
    //    {
    //        if (PointInRect(g_ptMouse, v_Characters[i]->GetRect()))
    //        {
    //            UiDataManager::GetSingleton()->SelectChar(v_Characters[i]);
    //            v_Characters[i]->SetSelected(true);
    //            if (!UiDataManager::GetSingleton()->GetSelectedChar())
    //            {
    //                UiDataManager::GetSingleton()->SetselCheck(false);                
    //            }
    //        }
    //    }

    /*    if (UiDataManager::GetSingleton()->GetSelectedChar()) 
        {
           
        }*/

        //for (int i = 0; i < c_mgr->GetCharacters().size(); i++)
        //{
        //    if (PointInRect(g_ptMouse, c_mgr->GetCharacters()[i]->GetRect())) {
        //        UiDataManager::GetSingleton()->SelectChar(c_mgr->GetCharacters()[i]);
        //        if (selChr != c_mgr->GetCharacters()[i])
        //        {
        //            UiDataManager::GetSingleton()->SetselCheck(false);
        //            selSkill = nullptr;
        //        }
        //    }
        //}

        //for (int i = 0; i < selSkillmgr->GetSkillSlot().size(); i++)
        //{
        //    if (PointInRect(g_ptMouse, selSkillmgr->GetSkillSlot()[i]->GetRect())) {
        //        if (selSkillmgr->GetSkillSlot()[i]->GetSkillState() == Skill::SkillState::ON()) {
        //            UiDataManager::GetSingleton()->selectSkill(selSkillmgr->GetSkillSlot()[i]);
        //            selSkill = UiDataManager::GetSingleton()->GetSelectedSkill();
        //            UiDataManager::GetSingleton()->SetselCheck(true);
        //        }
        //    }
        //}

    //}




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
    /*    v_Characters[0]->SetIndex(v_Characters[1]->GetIndex());
        v_Characters[1]->SetIndex(v_Characters[0]->GetIndex());*/
    
    }

    

 
}

void CharacterManager::Render(HDC hdc)
{
    /*for (int i = 0; i < v_Characters.size(); i++)
    {
        for (int j = 1; j < 4; j++)
        {
            if (v_Characters[i]->GetDepth() == j)
            {
                v_Characters[i]->Render(hdc);
                v_Characters[i]->ShareRender(hdc);
            }
        }
       
    }
   */
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDepth() == 1)
        {
            v_Characters[i]->Render(hdc);
            v_Characters[i]->ShareRender(hdc);


        }
    }
    for (int i = 0; i < v_Characters.size(); i++)
    {
    if (v_Characters[i]->GetDepth() == 2)
    {
        v_Characters[i]->Render(hdc);
        v_Characters[i]->ShareRender(hdc);


    }
    }
    for (int i = 0; i < v_Characters.size(); i++)
    {
        if (v_Characters[i]->GetDepth() ==3)
        {
            v_Characters[i]->Render(hdc);
            v_Characters[i]->ShareRender(hdc);


        }
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