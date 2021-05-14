#include "Character.h"
#include "Skill.h"
#include "SkillManager.h"
HRESULT Character::Init()
{
	return S_OK;
}

void Character::Release()
{
}

void Character::Update()
{
}

void Character::Render(HDC hdc)
{
}

void Character::Render2(HDC hdc)
{
}

void Character::SharedUpdate()
{
    switchSprite();
    Move();
    IdleCombatUpdate();
    S_MGR->Update();
    //UiDataManager::GetSingleton()->SetSS_MGR(S_MGR);
}

void Character::switchSprite()
{
    switch (currstate)
    {
    case IDLE:
        //currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(classArr[hClass] +"아이들");
        break;
    case WALK:
       // currFrameX = 0;

        img = ImageManager::GetSingleton()->FindImage(classArr[hClass]+"워크");
        break;
    case COMBAT:
      //  currFrameX = 0;

        img = ImageManager::GetSingleton()->FindImage(classArr[hClass]+"컴뱃");
        break;
    case ATTACK1:
        currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(classArr[hClass] + "기본공격");
        break;
    case NONESTATE:
        break;
    default:
        break;
    }
  
}

void Character::Move()
{

    //float walkElapsed = 0.0f;
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)|| KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
        currstate = State::WALK;

        walkElapsed += 5;
        //elapsed += 0.05f;
        if (walkElapsed > 50/*elapsed > 0.3f*/) {
            currFrameX++;
            // elapsed = 0;
            walkElapsed = 0;
        }
        if (currFrameX >= maxFrameArr[State::WALK]) {
            currFrameX = 0;
        }
        // pos.x += 1;
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) || KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
    {
        walkElapsed = 0;
        currFrameX = 0;
        SetCurrState(State::IDLE);

    }
}

void Character::IdleCombatUpdate()
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

Character::Character()
{
    index = -1;
    img = nullptr;
    pos = { 0,WINSIZE_Y / 3 };
    hClass = NONEHCLASS;
    currstate = NONESTATE;
    currFrameX = 0;
    elapsed = 0.0f;
    walkElapsed = 0;
    SetRect(&body, pos.x - 45, pos.y - 40, pos.x + 45, pos.y + 40);
    S_MGR = new SkillManager();
    S_MGR->Init();
    S_MGR->AddSkill(new Skill);
    S_MGR->AddSkill(new Skill);
    S_MGR->AddSkill(new Skill);
    S_MGR->AddSkill(new Skill);
    S_MGR->AddSkill(new Skill);

}
