#include "Character.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Image.h"
#include "config.h"
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

HRESULT Character::RosterInit()
{
    rosterBg = ImageManager::GetSingleton()->FindImage("로스터배경");
    rosterIcon = ImageManager::GetSingleton()->FindImage(GetClassArr()[GetClass()] + "아이콘");
    SetRect(&iconRC, iconPos.x , iconPos.y ,
        iconPos.x + 160, iconPos.y + 70);
    iconMouseOver = false;
    iconIsSeleceted = false;
    return S_OK;
}

void Character::RosterRelease()
{
}

void Character::RosterUpdate()
{
    if (iconMouseOver)
    {
        iconPos.x = WINSIZE_X / 2 + 350;
        SetRect(&iconRC, iconPos.x, iconPos.y,
            iconPos.x + 160, iconPos.y + 70);
    }
    else
    {
        iconPos.x = WINSIZE_X / 2 + 400;
        SetRect(&iconRC, iconPos.x, iconPos.y,
            iconPos.x + 160, iconPos.y + 70);
    }
    //SetRect(&iconRC,WINSIZE_X / 2 + 400)
    rosterIcon= ImageManager::GetSingleton()->FindImage(GetClassArr()[GetClass()] + "아이콘");
}

void Character::RosterRender(HDC hdc)
{
  /*  rosterBg->Render(hdc,WINSIZE_X/2+400,50+index*70);
    rosterIcon->Render(hdc,WINSIZE_X / 2 + 400,50+index * 70);  */
    rosterBg->Render(hdc,iconPos.x,iconPos.y);
    rosterIcon->Render(hdc,iconPos.x,iconPos.y);
    //Rectangle(hdc, iconRC.left, iconRC.top, iconRC.right, iconRC.bottom);
}

HRESULT Character::PartyInit()
{
    return E_NOTIMPL;
}

void Character::PartyRelease()
{
}

void Character::PartyUpdate()
{
}

void Character::PartyRender(HDC hdc)
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

void Character::HUpdate()
{
}

void Character::MUpdate()
{
   // mTime += TimerManager::GetSingleton()->GetElapsedTime();

    
 
    if (AbilOn == false) {
        IdleCombatUpdate();
        MswitchSprite();
       
    }
    abliiltyUpdate();
    if (pos.x < MonArrPos[index])
    {
        pos.x += 500*TimerManager::GetSingleton()->GetElapsedTime();//mTime * 1 / 10;
    }
    else if (pos.x > MonArrPos[index])
    {
        pos.x -= 500*TimerManager::GetSingleton()->GetElapsedTime();//mTime * 1 / 10;
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
    S_MGR->SetHClass(hClass);
    if (AbilOn == false) {
        IdleCombatUpdate();
        switchSprite();
        Move();
    }
    S_MGR->Update();
  
    abliiltyUpdate();


    if (pos.x < CharArrPos[index])
    {
        pos.x += eltimes * 1/10;
    }
    else if(pos.x>CharArrPos[index])
    {
        pos.x -= eltimes * 1/10;
    }
    else
    {
        eltimes = 0;
    }
       
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
    case SKILL1:
        currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(classArr[hClass] + "스킬1");
        AbilOn = true;
        depth = 3;
        break;
    case NONESTATE:
        break;
    default:
        break;
    }
  
}
void Character::MswitchSprite()
{
    switch (currstate)
    {

    case COMBAT:
        //  currFrameX = 0;

        img = ImageManager::GetSingleton()->FindImage(MonArr[mkinds] + "컴뱃");
        break;
    case SKILL1:
        currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(MonArr[mkinds] + "스킬1");
        
        break;
    case HURT:
        currFrameX = 0;
        img = ImageManager::GetSingleton()->FindImage(MonArr[mkinds] + "피격");
        AbilOn = true;
        depth = 2;
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
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)|| KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)||
        KeyManager::GetSingleton()->IsStayKeyDown('A')|| KeyManager::GetSingleton()->IsStayKeyDown('D')) {
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

    if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) || KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT)
        || KeyManager::GetSingleton()->IsOnceKeyUp('A') || KeyManager::GetSingleton()->IsOnceKeyUp('D'))
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
       
        size = 1.0f;
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
    S_MGR->Init(this);
    S_MGR->SetHClass(hClass);
    //S_MGR->AddSkill(new CombatAttack);
    //S_MGR->AddSkill(new Skill);
    //S_MGR->AddSkill(new Skill);
    //S_MGR->AddSkill(new Skill);
    //S_MGR->AddSkill(new Skill);

}

void Character::abliiltyUpdate()
{
    if (AbilOn)
    {
        AbilTime += TimerManager::GetSingleton()->GetElapsedTime();

        size -= AbilTime*0.001f;
        if (AbilTime > 1.3f)
        {
            AbilTime = 0;
            AbilOn = false;
            currstate = State::COMBAT;
            depth = 1;
        }
        
    }
}

void Character::Hurt()
{
    float Mtime;
    if (currstate != State::HURT)
    {
        Mtime = 0.0f;

       
        currstate = State::HURT;
    }
    if (currstate == State::HURT)
    {
        Mtime += TimerManager::GetSingleton()->GetElapsedTime();
        if (Mtime > 2.0f)
        {
            currstate = State::COMBAT;
            Mtime = 0.0f;

        }
    }
}

Character::Character()
{
    selecetedIcon = ImageManager::GetSingleton()->AddImage("선택아이콘", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
    targetIcon = ImageManager::GetSingleton()->AddImage("타겟아이콘", "resource/sharedUi/target.BMP", 197, 412, 1, 2, true, RGB(88, 88, 88));
    UiDataManager::GetSingleton()->SetClassArr(this->classArr);

    index = -1;
    img = nullptr;
    pos = { 0,WINSIZE_Y / 3 };
    uType = NONETYPE;
    hClass = NONEHCLASS;
    currstate = NONESTATE;
    mkinds = NONEKINDS;
    AbilOn = false;
    AbilTime = 0;
    currFrameX = 0;
    elapsed = 0.0f;
    mTime = 0.0f;
    walkElapsed = 0;
    target = false;
    selected = false;
    fixedTarget = false;
    alpha = 150;
    depth = 1;
    SetRect(&body, pos.x - 45, pos.y - 40, pos.x + 45, pos.y + 40);

}
