#include "MainGame.h"
#include "Image.h"
#include "Dungeon_1_1.h"
#include "MapGenManager.h"
#include <ctime>
#include "DataManager.h"
#include "ImageStorage.h"
#include "DungeonPath.h"
#include "DungeonRoom.h"
#include "DungeonConnect.h"
#include "Home.h"
HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);
	//Main_DM = new DataManager();

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	UiDataManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();

	// 이미지를 미리 로드한다
	istorage = new ImageStorage();
	istorage->Init();

	// 메인게임의 초기화 함수
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// 백버퍼 이미지
	int maxWidth, maxHeight;
	maxWidth = max(WINSIZE_X, TILEMAPTOOLSIZE_X);
	maxHeight = max(WINSIZE_Y, TILEMAPTOOLSIZE_Y);

	backBuffer = new Image(); 
	backBuffer->Init(maxWidth, maxHeight);
	SceneManager::GetSingleton()->AddScene("맵생성", new MapGenManager());

	SceneManager::GetSingleton()->AddScene("스테이지1", new Dungeon_1_1());
	SceneManager::GetSingleton()->AddScene("통로", new DungeonPath());
	SceneManager::GetSingleton()->AddScene("마을", new Home());
	SceneManager::GetSingleton()->AddScene("던전방", new DungeonRoom());
	SceneManager::GetSingleton()->AddScene("던전연결기", new DungeonConnect());

	//SceneManager::GetSingleton()->ChangeScene("던전방");
	SceneManager::GetSingleton()->ChangeScene("마을");
	//SceneManager::GetSingleton()->ChangeScene("스테이지1");
	//SceneManager::GetSingleton()->ChangeScene("맵생성");

	isInited = true;
	//srand(time(NULL));
	srand(time(NULL));

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();
	SAFE_RELEASE(istorage);
	SAFE_RELEASE(backBuffer);
	 
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	SceneManager::GetSingleton()->Render(hBackDC);

	//// 인사
	//TextOut(hBackDC, 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	////// 마우스 좌표
	//wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x, g_ptMouse.y);
	//TextOut(hBackDC, 200, 20, szText, strlen(szText));
	// FPS
	TimerManager::GetSingleton()->Render(hBackDC);
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
