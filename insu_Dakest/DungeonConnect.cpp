#include "DungeonConnect.h"

HRESULT DungeonConnect::Init()
{


	return S_OK;
}

HRESULT DungeonConnect::Init(DUNGEONINFO info)
{

	return S_OK;
}

void DungeonConnect::Release()
{
}

void DungeonConnect::Update()
{
	if (UiDataManager::GetSingleton()->GetPrevScene() == UiDataManager::SceneInfo::TOWN)
	{
		SceneManager::GetSingleton()->ChangeScene("¸Ê»ý¼º");
	}
	else if (UiDataManager::GetSingleton()->GetPrevScene() == UiDataManager::SceneInfo::MAPGEN)
	{
		SceneManager::GetSingleton()->ChangeTile(UiDataManager::GetSingleton()->GetTile());
	}
	else
	{
		SceneManager::GetSingleton()->ChangeTile(UiDataManager::GetSingleton()->GetTile());
	}
}

void DungeonConnect::Render(HDC hdc)
{
}
