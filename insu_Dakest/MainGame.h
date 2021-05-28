#pragma once
#include "GameNode.h"

class Image;
class DataManager;
class ImageStorage;

class MainGame : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	char szText[128] = "";
	//DataManager* Main_DM;
	Image* backBuffer;
	ImageStorage* istorage;
public:
	HRESULT Init();		// �������̵� : ������
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

