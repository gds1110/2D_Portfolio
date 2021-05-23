#include "MapGenManager.h"
#include "CommonFunction.h"
#include "Image.h"
HRESULT Tile::Init()
{
	return E_NOTIMPL;
}

HRESULT Tile::Init(int idX, int idY)
{
	ImageManager::GetSingleton()->AddImage("통로", "resource/mapui/path1.BMP", 12, 12, true, RGB(88, 88, 88));;
	ImageManager::GetSingleton()->AddImage("던전방", "resource/mapui/room1.BMP", 18, 18, true, RGB(88, 88, 88));;
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
{/*
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	FillRect(hdc, &rc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);*/
	//wsprintf(szText, "%d", idX);
	//TextOut(hdc, center.x, center.y, szText, strlen(szText));
	/*wsprintf(szText, "%d", idY);
	TextOut(hdc, center.x-5, center.y-5, szText, strlen(szText));*/
	//SelectObject(hdc, hOldBrush);
	if (tileImg) {
		tileImg->Render(hdc, center.x, center.y, true);
		if (index > -1) {
			//wsprintf(szText, "%d", index);
			//TextOut(hdc, center.x, center.y, szText, strlen(szText));
		}
	}
}

void Tile::Render2(HDC hdc,int x,int y)
{
	if (tileImg)
	{
		tileImg->Render(hdc,500+center.x,center.y, true);
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
	roomnum = 0;
	currTile = startTile;
	minimapdone = false;
	MiniMap = new Image();
	MiniMap->Init(ASTARSIZE_X, ASTARSIZE_Y);

	//destTile = &(map[TILE_COUNT - 2][TILE_COUNT - 2]);
	destTile = &(map[1][1]);
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

	if (roomnum < 8) {
		for (int i = 0; i < 4; i++) {
			MakePath(*currTile);
			if (!openList.empty()) {
				for (int i = 0; i < openList.size(); i++)
				{
				
						if (map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].getindex() != -1)
						{
							if (map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1].GetType() == TileType::Path)
							{
								openList[i]->SetFourDir(0, map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].getindex());
							}
						}
						if (map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].getindex() != -1)
						{
							if (map[openList[i]->GetIdY()][openList[i]->GetIdX() + 1].GetType() == TileType::Path)
							{
								openList[i]->SetFourDir(1, map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].getindex());
							}
						}
						if (map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()].getindex() != -1)
						{
							if (map[openList[i]->GetIdY() - 1][openList[i]->GetIdX()].GetType() == TileType::Path)
							{
								openList[i]->SetFourDir(2, map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()].getindex());
							}
						}
						if (map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].getindex() != -1)
						{
							if (map[openList[i]->GetIdY() + 1][openList[i]->GetIdX()].GetType() == TileType::Path)
							{
								openList[i]->SetFourDir(3, map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].getindex());
							}
						}

					
				}
			}

		}
		UiDataManager::GetSingleton()->SetMiniMap(openList);

			//SetRect(&mapview, minIndex.x, minIndex.y, maxIndex.x + 1, maxIndex.y + 1);
			SetRect(&mapview, minIndex.x, minIndex.y, maxIndex.x + 1, maxIndex.y + 1);
			//MiniMap->Init(ASTARSIZE_X, ASTARSIZE_Y);

			//MiniMap->Init(((mapview.right - mapview.left) * TILE_SIZE), ((mapview.bottom - mapview.top) * TILE_SIZE));
			//MiniMap->Init(((mapview.right - mapview.left) * TILE_SIZE), ((mapview.bottom - mapview.top) * TILE_SIZE));

	}
	else
	{
		

		//
	}
		//if (minimapdone == false)
		//{
		//	minimapdone = true;
		//	//MiniMap->Init(((maxIndex.x + 1) - minIndex.x)* TILE_SIZE, ((maxIndex.y + 1) - minIndex.y)* TILE_SIZE);
		//	MiniMap->Init(((mapview.right - mapview.left) * TILE_SIZE), ((mapview.bottom - mapview.top) * TILE_SIZE));
		//	//MiniMap->Init(2000,2000);

		//}

	
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
	UiDataManager::GetSingleton()->SetMapimg(MiniMap);
	UiDataManager::GetSingleton()->SetMin(minIndex);
	UiDataManager::GetSingleton()->SetMax(maxIndex);
	SceneManager::GetSingleton()->ChangeScene("스테이지1");
}

void MapGenManager::Render(HDC hdc)
{
	
	HDC miniDC = MiniMap->GetMemDC();
	UiDataManager::GetSingleton()->SetHdc(miniDC);
	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Render(hdc);
		}
	}
	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Render(miniDC);
		}
	}


	Rectangle(hdc, mapview.left*TILE_SIZE, mapview.top * TILE_SIZE, mapview.right * TILE_SIZE, mapview.bottom * TILE_SIZE);
	Rectangle(hdc, 1000, 0, 2000, 1000);
	for (int i = 0; i < openList.size(); i++)
	{
		openList[i]->Render(hdc);
	}

	for (int i = 0; i < openList.size(); i++) {
		/*wsprintf(szText, "X : %d, Y : %d",openList.size()), openList[i]->GetParentTile()->getindex());
		TextOut(hdc, 1000, 50*i, szText, strlen(szText));*/
		for (int j = 0; j < openList[i]->GetWay().size();j++)
		{
	/*		if (!openList[i]->GetWay().empty()) {
				wsprintf(szText, "r : %d, w : %d",i ,openList[i]->GetWay()[j]);
				TextOut(hdc,1000+90*j, 80 * i, szText, strlen(szText));
			}*/
		}
		/*for (int j = 0; j < 4; j++)
		{
			wsprintf(szText, "r : %d, w : %d", i, openList[i]->GetFourDir()[j]);
			TextOut(hdc, 1000 + 90 * j, 80 * i, szText, strlen(szText));
		}*/
	}
	for (int i = 0; i < openList.size(); i++)
	{
		openList[i]->Render(miniDC);
	}
	//Rectangle(miniDC, mapview.left * TILE_SIZE, mapview.top * TILE_SIZE, mapview.right * TILE_SIZE, mapview.bottom * TILE_SIZE);
	//MiniMap->Render3(hdc, 1100, 0,false,1,minIndex.x* TILE_SIZE,minIndex.y* TILE_SIZE);
	MiniMap->Render4(hdc, 1100, 0,false,1,minIndex,maxIndex);
	//MiniMap->Render3(hdc, 1000, 600,false,1,(maxIndex.x)* TILE_SIZE,(maxIndex.y)* TILE_SIZE);
	/*MiniMap->Render3(hdc, 1200, 100,false,1, mapview.left, mapview.top );*/
}

void MapGenManager::Render2(HDC hdc)
{
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
		currTile->SetType(TileType::Room);

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

					if (map[currIdY][currIdX + i].GetIsInOpenlist() == false) {
						map[currIdY][currIdX + i].SetIsInOpenlist(true);
						AddOpenList(&map[currIdY][currIdX + i]);
					}
				}
				
				map[currIdY][currIdX].addWay(map[currIdY][currIdX + 5].getindex());
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

					if (map[currIdY][currIdX - i].GetIsInOpenlist() == false) {
						map[currIdY][currIdX - i].SetIsInOpenlist(true);
						AddOpenList(&map[currIdY][currIdX - i]);
					}

				}
		
				map[currIdY][currIdX].addWay(map[currIdY][currIdX-5].getindex());
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

					if (map[currIdY + i][currIdX].GetIsInOpenlist() == false) {
						map[currIdY + i][currIdX].SetIsInOpenlist(true);
						AddOpenList(&map[currIdY + i][currIdX]);
					}

				}
	
				map[currIdY][currIdX].addWay(map[currIdY + 5][currIdX].getindex());
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

					if (map[currIdY - i][currIdX].GetIsInOpenlist() == false) {
						map[currIdY - i][currIdX].SetIsInOpenlist(true);
						AddOpenList(&map[currIdY - i][currIdX]);
					}

				}
		
				map[currIdY][currIdX].addWay(map[currIdY - 5][currIdX].getindex());
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
			minIndex.x = min(minIndex.x, currTile->GetIdX());
			minIndex.y = min(minIndex.y, currTile->GetIdY());
			maxIndex.x = max(maxIndex.x, currTile->GetIdX());
			maxIndex.y = max(maxIndex.y, currTile->GetIdY());
			AddOpenList(currTile);
			index++;
			roomnum = index;
		
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
