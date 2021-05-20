#include "MapGenManager.h"
#include "CommonFunction.h"
#include "Image.h"
HRESULT Tile::Init()
{
	return E_NOTIMPL;
}

HRESULT Tile::Init(int idX, int idY)
{
	ImageManager::GetSingleton()->AddImage("통로", "resource/mapui/path1.BMP", 16, 16, true, RGB(88, 88, 88));;
	ImageManager::GetSingleton()->AddImage("던전방", "resource/mapui/room1.BMP", 32, 32, true, RGB(88, 88, 88));;
	isInOpenlist = false;
	isClosed = false;
	
	this->idX = idX;
	this->idY = idY;
	index = -1;
	center.x = idX *TILE_SIZE + (TILE_SIZE / 2);
	center.y = idY *TILE_SIZE + (TILE_SIZE / 2);

	rc.left = idX *TILE_SIZE;
	rc.right = rc.left + TILE_SIZE;
	rc.top = idY * TILE_SIZE;
	rc.bottom = rc.top + TILE_SIZE;

	costFromStart = 0.0f;
	costToGoal = 0.0f;
	totalCost = 0.0f;

	type = TileType::None;

	parentTile = nullptr;

	color = RGB(100, 100, 100);
	hBrush = CreateSolidBrush(color);

	return S_OK;
}

void Tile::Release()
{
	DeleteObject(hBrush);

}

void Tile::Update()
{
	if (type == TileType::Path)
	{
		tileImg = ImageManager::GetSingleton()->FindImage("통로");
	}
	else if (type == TileType::Room)
	{
		tileImg = ImageManager::GetSingleton()->FindImage("던전방");
	}
}

void Tile::Render(HDC hdc)
{
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	FillRect(hdc, &rc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	//wsprintf(szText, "%d", index);
	//TextOut(hdc, center.x,center.y, szText, strlen(szText));
	SelectObject(hdc, hOldBrush);
	if (tileImg) {
		tileImg->Render(hdc, center.x, center.y,true);
	}
}

void Tile::SetColor(COLORREF color)
{
	this->color = color;
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(color);
}

HRESULT MapGenManager::Init()
{
	

	SetClientRect(g_hWnd, ASTARSIZE_X, ASTARSIZE_Y);

	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Init(j, i);
		}
	}
	min = { 0,0 };

	startTile = &(map[TILE_COUNT / 2][TILE_COUNT / 2]);
	startTile->SetColor(RGB(255, 0, 0));
	startTile->SetType(TileType::Start);

	currTile = startTile;

	destTile = &(map[TILE_COUNT - 2][TILE_COUNT - 2]);
	destTile->SetColor(RGB(0, 0, 255));
	destTile->SetType(TileType::End);
	index = 0;
	currTile->SetParentTile(currTile);
	return S_OK;
}

void MapGenManager::Release()
{
}

void MapGenManager::Update()
{
	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		{
			if (map[i][j].GetIsClosed() == true)
			{
				map[i][j].SetColor(RGB(255, 0, 255));
				
			}
				map[i][j].Update();

		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		for (int i = 0; i < 4; i++) {
			MakePath(*currTile);
		}
		
		//for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
		//{
		//	for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		//	{
		//		if (map[i][j].GetIsClosed() == false)
		//		{
		//			map[i][j].Release();

		//		}

		//	}
		//}
		//*(*map)

		//currTile = startTile;
		//FindPath();
	}
	

}

void MapGenManager::Render(HDC hdc)
{
	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Render(hdc);
		}
	}
	Rectangle(hdc, 1000, 0, 2000, 1000);
	for (int i = 0; i < openList.size(); i++)
	{
		openList[i]->Render(hdc);
	}
	/*for (int i = 0; i < openList.size(); i++) {
		wsprintf(szText, "X : %d, Y : %d",openList[i]->getindex(), openList[i]->GetParentTile()->getindex());
		TextOut(hdc, 1000, 50*i, szText, strlen(szText));
		for (int j = 0; j < openList[i]->GetWay().size();j++)
		{
			wsprintf(szText, "X : %d", openList[i]->GetWay()[j]);
			TextOut(hdc, 1000+j*80, 40 * i, szText, strlen(szText));
			
		}
	}*/
}

void MapGenManager::MakePath(Tile& tile)
{
	int dirx = 0;
	int diry = 0;
	/*int currIdX = tile.GetIdX();
	int currIdY = tile.GetIdY();*/
	int currIdX = currTile->GetIdX();
	int currIdY = currTile->GetIdY();
	
	if (&tile == startTile)
	{
		currTile = &tile;
		currTile->SetParentTile(startTile);
		(currTile)->setindex(index);
		(currTile)->SetIsClosed(true);
		AddOpenList(currTile);
		index++;
	}
	for (int i = 0; i < 5; i++) {
		int rands = rand() % 4;
	
		switch (rands)
		{
		case 0:
			if (currIdX + 5 < TILE_COUNT) {
				for (int i = 1; i < 5; i++)
				{
					map[currIdY][currIdX + i].SetColor(RGB(0, 255, 0));
					map[currIdY][currIdX + i].SetType(TileType::Path);
				}
				map[currIdY][currIdX + 5].SetColor(RGB(255, 255, 0));
				currTile = &map[currIdY][currIdX + 5];

			}
			break;
		case 1:
			if (currIdX - 5 >= 0) {
				for (int i = 1; i < 5; i++)
				{
					map[currIdY][currIdX - i].SetColor(RGB(0, 255, 0));
					map[currIdY][currIdX - i].SetType(TileType::Path);

				}
				map[currIdY][currIdX - 5].SetColor(RGB(255, 255, 0));
				currTile = &map[currIdY][currIdX - 5];
			}

			break;
		case 2:
			if (currIdY + 5 < TILE_COUNT) {
				for (int i = 1; i < 5; i++)
				{
					map[currIdY + i][currIdX].SetColor(RGB(0, 255, 0));
					map[currIdY + i][currIdX].SetType(TileType::Path);

				}
				map[currIdY + 5][currIdX].SetColor(RGB(255, 255, 0));
				currTile = &map[currIdY + 5][currIdX];
			}

			break;
		case 3:
			if (currIdY - 5 >= 0) {
				for (int i = 1; i < 5; i++)
				{
					map[currIdY - i][currIdX].SetColor(RGB(0, 255, 0));
					map[currIdY - i][currIdX].SetType(TileType::Path);

				}
				map[currIdY - 5][currIdX].SetColor(RGB(255, 255, 0));
				currTile = &map[currIdY - 5][currIdX];
			}

			break;
		default:
			break;
		}
		if (currTile->GetIsClosed() == false) {
			currTile->SetType(TileType::Room);
			currTile->SetIsClosed(true);
			currTile->setindex(index);
			index = currTile->getindex();
			
			AddOpenList(currTile);
			index++;
		}
	}
		
}

void MapGenManager::FindPath()
{
}

void MapGenManager::AddOpenList(Tile* currTile)
{
	openList.push_back(currTile);
}

void MapGenManager::UpdateLower(Tile* tile)
{
}

void MapGenManager::Swap(Tile* tile1, Tile* tile2)
{
}

void MapGenManager::UpdateUpper(Tile* tile)
{
}

void MapGenManager::DeleteTileInOpenlist(Tile* tile)
{
}

void MapGenManager::MarkTileToType()
{
}
