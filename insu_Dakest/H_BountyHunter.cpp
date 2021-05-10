#include "H_BountyHunter.h"
#include "Image.h"

HRESULT H_BountyHunter::Init()
{

    img = ImageManager::GetSingleton()->AddImage("바운티헌터 컴뱃", "resource/hero/bountyHunter/combat/bountyHunter_combat.BMP", 3152, 300, 16, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 워크", "resource/hero/bountyHunter/walk/bountyHunter_walk.BMP", 2688, 300, 16, 1, true, RGB(88, 88, 88));
    ImageManager::GetSingleton()->AddImage("바운티헌터 아이들", "resource/hero/bountyHunter/idle/bountyHunter_idle.BMP", 2880, 300, 18, 1, true, RGB(88, 88, 88));
    currFrameX = 0;
    pos.y = 300;
    elapsed = 0.0f;
    walkElapsed = 0;
    currstate = State::COMBAT;
    return S_OK;
}

void H_BountyHunter::Release()
{
}

void H_BountyHunter::Update()
{
    Move();

}

void H_BountyHunter::Render(HDC hdc)
{
    img->FrameRender(hdc, pos.x, pos.y, currFrameX, 0);
}

void H_BountyHunter::Move()
{
    if (currstate == State::COMBAT)
    {
        img = ImageManager::GetSingleton()->FindImage("바운티헌터 아이들");
    }
    else if (currstate == State::WALK)
    {
        img = ImageManager::GetSingleton()->FindImage("바운티헌터 워크");
    }

    if (currstate == State::COMBAT) {
        elapsed += TimerManager::GetSingleton()->GetElapsedTime();
        if (elapsed > 0.05f)
        {
            currFrameX++;

            elapsed = 0;
        }

        if (currFrameX >= 16)
        {
            currFrameX = 0;
        }
    }
    //float walkElapsed = 0.0f;
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
        currstate = State::WALK;

        walkElapsed += 5;
        //elapsed += 0.05f;
        if (walkElapsed > 50/*elapsed > 0.3f*/) {
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
