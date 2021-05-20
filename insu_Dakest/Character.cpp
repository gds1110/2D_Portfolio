#include "Character.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Image.h"
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

void Character::ShareRender(HDC hdc)
{
    if (target)
    {
        if (fixedTarget)
        {
            alpha = 255;
        }
        else
        {
            alpha = 150;
        }
        targetIcon->AlphaFrameRenders(hdc, pos.x + 30, 500, 0, 0, true, 0.8, alpha);
    }
    if (selected) {
        selecetedIcon->FrameRender(hdc,pos.x + 50, 430, 0, sIconCurrFrame, true, 0.8);
    }
}

void Character::SharedUpdate()
{
    //if selected
    eltimes += TimerManager::GetSingleton()->GetElapsedTime();
    if (selected)
    {
        if (eltimes > 0.3)
        {
            sIconCurrFrame++;
            if (sIconCurrFrame > 1) {
                sIconCurrFrame = 0;
            }
            eltimes = 0;
        }
    }

    IdleCombatUpdate();
    switchSprite();
    Move();
    S_MGR->SetHClass(hClass);
    S_MGR->Update();
  
    if (pos.x < CharArrPos[index])
    {
        pos.x += eltimes * 1;
    }
    else if(pos.x>CharArrPos[index])
    {
        pos.x -= eltimes * 1;
    }
       
}

void Character::switchSprite()
{
    switch (currstate)
    {
    case IDLE:
        //currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(classArr[hClass] +"���̵�");
        break;
    case WALK:
       // currFrameX = 0;

        img = ImageManager::GetSingleton()->FindImage(classArr[hClass]+"��ũ");
        break;
    case COMBAT:
      //  currFrameX = 0;

        img = ImageManager::GetSingleton()->FindImage(classArr[hClass]+"�Ĺ�");
        break;
    case SKILL1:
        currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(classArr[hClass] + "�⺻����");
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
        currstate = State::IDLE;
        walkElapsed = 0;
        currFrameX = 0;
        elapsed = 0;
        //SetCurrState(State::IDLE);
    }
}

void Character::IdleCombatUpdate()
{
    elapsed += TimerManager::GetSingleton()->GetElapsedTime();
    //idle or combat
    if (currstate == State::IDLE || currstate == State::COMBAT) {
       

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

void Character::skillSeting()
{
    S_MGR = new SkillManager();
    S_MGR->Init();
    S_MGR->SetHClass(hClass);
    //S_MGR->AddSkill(new CombatAttack);
    //S_MGR->AddSkill(new Skill);
    //S_MGR->AddSkill(new Skill);
    //S_MGR->AddSkill(new Skill);
    //S_MGR->AddSkill(new Skill);

}

Character::Character()
{
    selecetedIcon = ImageManager::GetSingleton()->AddImage("���þ�����", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
    targetIcon = ImageManager::GetSingleton()->AddImage("Ÿ�پ�����", "resource/sharedUi/target.BMP", 197, 412, 1, 2, true, RGB(88, 88, 88));
    UiDataManager::GetSingleton()->SetClassArr(this->classArr);
    index = -1;
    img = nullptr;
    pos = { 0,WINSIZE_Y / 3 };
    uType = NONETYPE;
    hClass = NONEHCLASS;
    currstate = NONESTATE;
    mkinds = NONEKINDS;
    currFrameX = 0;
    elapsed = 0.0f;
    walkElapsed = 0;
    target = false;
    selected = false;
    fixedTarget = false;
    alpha = 150;
    SetRect(&body, pos.x - 45, pos.y - 40, pos.x + 45, pos.y + 40);

}
