#include "Monster.h"

HRESULT Monster::Init()
{
    return E_NOTIMPL;
}

void Monster::Release()
{
}

void Monster::Update()
{
}

void Monster::Render(HDC hdc)
{
}

void Monster::IdleCombatUpdate()
{


    if (currstate == State::COMBAT || currstate == State::IDLE) {

        elapsed += TimerManager::GetSingleton()->GetElapsedTime();
        if (elapsed > 0.07f)
        {
            currFrameX++;

            if (currFrameX >= maxFrameArr[currstate])
            {
                currFrameX = 0;
            }
            elapsed = 0;
        }

    }
}
