#include "H_Crusader.h"
#include "Image.h"
#include "CommonFunction.h"
HRESULT H_Crusader::Init()
{

    pos.x = WINSIZE_X / 2-200;
    pos.y = WINSIZE_Y/3;

    img = ImageManager::GetSingleton()->AddImage("크루세이더 컴뱃", "resource/hero/crusader/combat/crusader_combat.BMP", 2115, 300,15,1,true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 워크", "resource/hero/crusader/walk/crusader_walk.BMP", 2896, 300, 16, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 아이들", "resource/hero/crusader/idle/crusader_idle.BMP", 5808, 300, 33, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 아이콘", "resource/hero/crusader/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 기본공격", "resource/hero/crusader/attack.BMP", 295, 295,1,1, true, RGB(88, 88, 88));
    currFrameX = 0;
    elapsed = 0.0f;
    walkElapsed = 0;
    currstate = State::COMBAT;
    hClass = HCLASS::CRUSADER;
    return S_OK;
}

void H_Crusader::Release()
{
}

void H_Crusader::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);

   
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
    {
      /*  for (int i = 0; i < v_Heros.size(); i++)
        {
            v_Heros[i]->SetState(Character::State::IDLE);
        }*/
        SetState(Character::State::ATTACK1);
      
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RETURN))
    {
        SetState(Character::State::COMBAT);


      

    }
    Move();

  /*  if (pos.x < WINSIZE_X / 2)
    {

        pos.x += 2;
    }*/
  //  Move();
}

void H_Crusader::Render(HDC hdc)
{
  
        img->FrameRender(hdc, pos.x, pos.y + 50, currFrameX, 0, true, 1.1);
        Rectangle(hdc, body.left, body.top, body.right, body.bottom);

       // RenderRectToCenter(hdc, pos.x, pos.y + 50, 80, 300);
}
void H_Crusader::Render2(HDC hdc)
{
    img->FrameRender(hdc, pos.x, pos.y + 50, currFrameX, 0, true, 1.5);
    //img->Render(hdc, pos.x, pos.y);
}
void H_Crusader::Move()
{
  /*  if (currstate == State::COMBAT)
    {
        img = ImageManager::GetSingleton()->FindImage("크루세이더 아이들");
    }
    else if (currstate == State::WALK)
    {
        img = ImageManager::GetSingleton()->FindImage("크루세이더 워크");
    }
    else if (currstate == State::IDLE)
    {
        img = ImageManager::GetSingleton()->FindImage("크루세이더 컴뱃");
    }
    else if (currstate == State::ATTACK1)
    {
        img = ImageManager::GetSingleton()->FindImage("크루세이더 기본공격");
    }*/
    switch (currstate)
    {
    case Character::IDLE:
        img = ImageManager::GetSingleton()->FindImage("크루세이더 아이들");
        break;
    case Character::WALK:
        img = ImageManager::GetSingleton()->FindImage("크루세이더 워크");
        break;
    case Character::COMBAT:
        img = ImageManager::GetSingleton()->FindImage("크루세이더 컴뱃");
        break;
    case Character::ATTACK1:
        currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(classArr[hClass]+"기본공격");
        break;
    case Character::NONESTATE:
        break;
    default:
        break;
    }
    if (currstate == State::COMBAT) {
        elapsed += TimerManager::GetSingleton()->GetElapsedTime();
        if (elapsed > 0.05f)
        {
            currFrameX++;

            elapsed = 0;
        }

        if (currFrameX > 14)
        {
            currFrameX = 0;
        }
    }
    //float walkElapsed = 0.0f;
    if(KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
        currstate = State::WALK;

        walkElapsed += 5;
        //elapsed += 0.05f;
        if (walkElapsed>50/*elapsed > 0.3f*/) {
            currFrameX++;
           // elapsed = 0;
            walkElapsed = 0;
        }
        if (currFrameX >= 16) {
            currFrameX = 0;
        }
       // pos.x += 1;
    }
    else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
        currstate = State::WALK;

        walkElapsed += 5;
        //elapsed += 0.1f;
        if (walkElapsed > 50/*elapsed > 0.2f*/) {
            currFrameX++;
            //elapsed = 0;
            walkElapsed = 0;
        }
        if (currFrameX >= 16) {
            currFrameX = 0;
        }
       // pos.x -= 1;
    }
     if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) || KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
    {
        walkElapsed = 0;
        currFrameX = 0;
        SetCurrState(State::COMBAT);
      
       
    }
}
