#pragma once
#include "GameNode.h"

class UI;
class OverUi;
class UnderUi;
class Image;
class Character;
class CharacterManager;
class SkillManager;

class Dungeon_1_1 : public GameNode
{
private:
	Image* Ip_Bg_First;
	Image* Ip_Bg_Second;
	Image* Ip_BG_Passage;
	UnderUi* underUI;
	OverUi* overUi;

	Image* CamBuffer;

	int battlePos[4];

	float test = 0.0f;
	int CamPos;
	CharacterManager* C_MGR;
	CharacterManager* M_MGR;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	

	virtual ~Dungeon_1_1() {};
};

