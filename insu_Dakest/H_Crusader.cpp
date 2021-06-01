#include "H_Crusader.h"
#include "Image.h"
#include "CommonFunction.h"
HRESULT H_Crusader::Init()
{

    maxFrameArr[State::IDLE] = 33;
    maxFrameArr[State::COMBAT] = 15;
    maxFrameArr[State::WALK] = 16;
    maxFrameArr[State::SKILL1] = 1;
    img = ImageManager::GetSingleton()->AddImage("크루세이더 컴뱃", "resource/hero/crusader/combat/combat.BMP", 2115, 300,15,1,true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 워크", "resource/hero/crusader/walk/walk.BMP", 2896, 300, 16, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 아이들", "resource/hero/crusader/idle/idle.BMP", 5808, 300, 33, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 아이콘", "resource/hero/crusader/icon.BMP", 65, 65, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 기본공격", "resource/hero/crusader/attack.BMP", 295, 295,1,1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("크루세이더 스킬", "resource/hero/crusader/skill/skillset.BMP", 504, 144, 7, 2, true, RGB(88, 88, 88));

    currstate = State::IDLE;
    hClass = HCLASS::CRUSADER;
    skillSeting();

    return S_OK;
}

void H_Crusader::Release()
{
}

void H_Crusader::Update()
{
    SetRect(&body, pos.x - 20, pos.y - 50, pos.x + 80, pos.y + 200);
  
   
   SharedUpdate();

  /*  if (pos.x < WINSIZE_X / 2)
    {

        pos.x += 2;
    }*/
  //  Move();
}

void H_Crusader::Render(HDC hdc)
{
    if (currstate == State::COMBAT){
        img->FrameRender(hdc, pos.x, pos.y + 80, currFrameX, 0, true, 1);
    }
    if (currstate == State::IDLE || currstate == State::WALK) {
        img->FrameRender(hdc, pos.x, pos.y + 110, currFrameX, 0, true, 0.9);

    }
        //Rectangle(hdc, body.left, body.top, body.right, body.bottom);

       // RenderRectToCenter(hdc, pos.x, pos.y + 50, 80, 300);
}
void H_Crusader::Render2(HDC hdc)
{
    //img->FrameRender(hdc, pos.x-300+speed, pos.y + 50, currFrameX, 0, true, 1.5);
    //img->Render(hdc, pos.x, pos.y);
}