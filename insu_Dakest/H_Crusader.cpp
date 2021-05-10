#include "H_Crusader.h"
#include "Image.h"
HRESULT H_Crusader::Init()
{

    pos.x = WINSIZE_X / 2-200;
    pos.y = 300;

    img = ImageManager::GetSingleton()->AddImage("ũ�缼�̴� �Ĺ�", "resource/hero/crusader/combat/crusader_combat.BMP", 2115, 300,15,1,true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("ũ�缼�̴� ��ũ", "resource/hero/crusader/walk/crusader_walk.BMP", 2896, 300, 16, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("ũ�缼�̴� ���̵�", "resource/hero/crusader/idle/crusader_idle.BMP", 5808, 300, 33, 1, true, RGB(88, 88, 88));
    currFrameX = 0;
    elapsed = 0.0f;
    walkElapsed = 0;
    currstate = State::COMBAT;
    return S_OK;
}

void H_Crusader::Release()
{
}

void H_Crusader::Update()
{
  
    Move();
}

void H_Crusader::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x, pos.y, currFrameX, 0);
}

void H_Crusader::Move()
{
    if (currstate == State::COMBAT)
    {
        img = ImageManager::GetSingleton()->FindImage("ũ�缼�̴� ���̵�");
    }
    else if (currstate == State::WALK)
    {
        img = ImageManager::GetSingleton()->FindImage("ũ�缼�̴� ��ũ");
    }

    if (currstate == State::COMBAT) {
        elapsed += TimerManager::GetSingleton()->GetElapsedTime();
        if (elapsed > 0.05f)
        {
            currFrameX++;

            elapsed = 0;
        }

        if (currFrameX >= 33)
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
