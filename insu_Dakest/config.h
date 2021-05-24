// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "UiDataManager.h"

#define WINSIZE_X	1280
#define WINSIZE_Y	720
#define TILEMAPTOOLSIZE_X	1620
#define TILEMAPTOOLSIZE_Y	900
#define ASTARSIZE_X	1620
#define ASTARSIZE_Y	900
#define TILE_SIZE	20
#define TILE_COUNT	(ASTARSIZE_Y / TILE_SIZE)

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

extern enum State
{
	IDLE,
	WALK,
	COMBAT,
	SKILL1,
	SKILL2,
	SKILL3,
	SKILL4,
	SKILL5,
	SKILL6,
	SKILL7,
	HURT,
	DEAD,
	NONESTATE
};

extern enum UnitType
{
	HERO,
	MONSTER,
	NONETYPE
};

extern enum HCLASS
{
	CRUSADER,
	BOUNTYHUNTER,
	HIGHWAYMAN,
	LEAPER,
	VESTEL,
	NONEHCLASS
};

extern enum MonsterKinds
{
	SKELETON_ARBALISTAR,
	SKELETON_BEARER,
	SKELETON_CAPTAIN,
	SKELETON_COMMON,
	NONEKINDS
};
//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
