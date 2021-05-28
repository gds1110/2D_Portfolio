#include "MapGenManager.h"
#include "CommonFunction.h"
#include "Image.h"
HRESULT Tile::Init()
{
	return E_NOTIMPL;
}

HRESULT Tile::Init(int idX, int idY)
{
	ImageManager::GetSingleton()->AddImage("통로", "resource/mapui/path1.BMP", 20, 20, true, RGB(88, 88, 88));;
	ImageManager::GetSingleton()->AddImage("던전방", "resource/mapui/room1.BMP", 30, 30, true, RGB(88, 88, 88));;
	tileIcon=ImageManager::GetSingleton()->AddImage("현재위치", "resource/mapui/indicator.BMP", 20, 20, true, RGB(88, 88, 88));;
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
	size = 1;

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
	if (isCurrted==true)
	{
		tileIcon = ImageManager::GetSingleton()->FindImage("현재위치");
	}
	if (canWay)
	{
		size += 0.01f;
		if (size > 2.1f)
		{
			size = 0;
		}
	}
	//if (openList[i]->GetIsCurrted() == true)
	//{
	//	for (int j = 0; j < openList[i]->GetWay().size(); j++)
	//	{
	//		openList[i]->GetWay()[j]->SetIsWay(true);
	//	}
	//}
}

void Tile::Render(HDC hdc)
{
	//hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	//FillRect(hdc, &rc, hBrush);
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	//SelectObject(hdc, hOldBrush);
	//wsprintf(szText, "%d", idX);
	//TextOut(hdc, center.x, center.y, szText, strlen(szText));
	/*wsprintf(szText, "%d", idY);
	TextOut(hdc, center.x-5, center.y-5, szText, strlen(szText));*/
	if (tileImg) {
		tileImg->Render2(hdc, center.x, center.y, true, size);
		if (index > -1) {
			wsprintf(szText, "%d", index);
			TextOut(hdc, center.x, center.y, szText, strlen(szText));
		}
		if (tileIcon)
		{
			if (isCurrted) {
				tileIcon->Render(hdc, center.x, center.y, true);
			}
		}
	}
}


void Tile::RandomSetTileInfo()
{
	int randomn = 0;
	int random2 = 0;
	int monrandom = 0;
	int randtype = 0;
	if (!isStarted)
	{
		randomn = rand() % 2;
		random2 = rand() % 101;
		randtype = rand() % 7;
		if (type == TileType::Room)
		{
			this->isEnemyed = randomn;
			this->roomType = randtype;
		}
		if (type == TileType::Path)
		{
			if (random2 > 66)
			{
				this->isEnemyed = true;
				this->pathType = randtype;
			}
		}
	}
	if (isEnemyed)
	{
		for (int i = 0; i < 4; i++)
		{
			monrandom = rand() % 4;
			enemyArr[i] = monrandom;
		}
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
	MiniMap->Init(1620, 900);

	destTile = &(map[1][1]);
	destTile->SetColor(RGB(0, 0, 255));
	destTile->SetType(TileType::End);
	index = 0;
	currTile->SetParentTile(currTile);
	return S_OK;
}

void MapGenManager::Release()
{
	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Release();
		}
	}
}

void MapGenManager::Update()
{
	for (int i = 0; i < TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < TILE_COUNT; j++)	// 가로반복 (x)
		{
			if (map[j][i].GetIsClosed() == true)
			{
				map[j][i].SetColor(RGB(255, 0, 255));

			}
			map[j][i].Update();

		}
	}

	if (roomnum < 10) {
		
		/*for (int i = 0; i < 4; i++) {
			

		}*/
		MakePath(*currTile);
		UiDataManager::GetSingleton()->SetMiniMap(openList);

		SetRect(&mapview, minIndex.x, minIndex.y, maxIndex.x + 1, maxIndex.y + 1);
	
	}
	else
	{
		if (minimapdone == false)
		{
			minimapdone = true;
			map[startPoint.y][startPoint.x].SetIsCurrted(true);
			map[startPoint.y][startPoint.x].SetIsStarted(true);

			for (int i = 0; i < openList.size(); i++)
			{
				openList[i]->RandomSetTileInfo();
			}

		}
		
		//
	}

		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->GetType() == TileType::Room) {
				if (openList[i]->GetIdX() - 5 > 0 && map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].GetType()==TileType::Room )
				{
					if (map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1].GetType() == TileType::Path)
					{
						openList[i]->SetFourDir(0, map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].getindex());
						map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
						map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].getindex() });
						openList[i]->addWay(&map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5]);
					}
				}
				if ( openList[i]->GetIdX() + 5 < TILE_COUNT && map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].GetType() == TileType::Room)
				{
					if (map[openList[i]->GetIdY()][openList[i]->GetIdX() + 1].GetType() == TileType::Path)
					{
						openList[i]->SetFourDir(1, map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].getindex());
						map[openList[i]->GetIdY()][openList[i]->GetIdX() + 1].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
						map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].getindex() });
						openList[i]->addWay(&map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5]);

					}
				}
				if (openList[i]->GetIdY() - 5 > 0 && map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()].GetType() == TileType::Room)
				{
					if (map[openList[i]->GetIdY() - 1][openList[i]->GetIdX()].GetType() == TileType::Path)
					{
						openList[i]->SetFourDir(2, map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()].getindex());
						map[openList[i]->GetIdY()-1][openList[i]->GetIdX()].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
						map[openList[i]->GetIdY()-5][openList[i]->GetIdX() ].getindex() });
						openList[i]->addWay(&map[openList[i]->GetIdY()-5][openList[i]->GetIdX()]);

					}
				}
				if ( openList[i]->GetIdY() + 5 < TILE_COUNT && map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].GetType() == TileType::Room )
				{
					if (map[openList[i]->GetIdY() + 1][openList[i]->GetIdX()].GetType() == TileType::Path)
					{
						openList[i]->SetFourDir(3, map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].getindex());
						map[openList[i]->GetIdY()+ 1][openList[i]->GetIdX()].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
						map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].getindex() });
						openList[i]->addWay(&map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()]);

					}
				}
			}
			/*		if (min(openList[i]->GetIdX(), startPoint.x))
					{

						startPoint = { openList[i]->GetIdX() ,openList[i]->GetIdY() };


					}*/


		}
	


	UiDataManager::GetSingleton()->SetMapimg(MiniMap);
	UiDataManager::GetSingleton()->SetMin(minIndex);
	UiDataManager::GetSingleton()->SetMax(maxIndex);
	UiDataManager::GetSingleton()->SetMapGeN(this);
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
	{
		
		SceneManager::GetSingleton()->ChangeScene("스테이지1");
		return;
	}
}

void MapGenManager::Render(HDC hdc)
{
	
	HDC miniDC = MiniMap->GetMemDC();
	UiDataManager::GetSingleton()->SetHdc(miniDC);
	

	//for (int i = 0; i < openList.size(); i++)
	//{
	//	openList[i]->Render(hdc);
	//}

	//for (int i = 0; i < openList.size(); i++) {
	//
	//	if (openList[i]->GetType() == TileType::Room) {
	//		for (int j = 0; j < 4; j++)
	//		{
	//			wsprintf(szText, "r : %d, w : %d", openList[i]->getindex(), openList[i]->GetFourDir()[j]);
	//			TextOut(hdc, 1000 + 90 * j, 20 * i, szText, strlen(szText));
	//		}
	//	}
	//}
	//for (int i = 0; i < openList.size(); i++)
	//{
	//	if (openList[i]->GetType() == TileType::Path) {
	//		//openList[i]->Render(miniDC);
	//		openList[i]->Render(miniDC);
	//	}
	//}
	//for (int i = 0; i < openList.size(); i++)
	//{
	//	if (openList[i]->GetType() == TileType::Room) {
	//		//openList[i]->Render(miniDC);
	//		openList[i]->Render(miniDC);
	//	}
	//}
	//Rectangle(miniDC, mapview.left * TILE_SIZE, mapview.top * TILE_SIZE, mapview.right * TILE_SIZE, mapview.bottom * TILE_SIZE);
	//MiniMap->Render3(hdc, 1100, 0,false,1,minIndex.x* TILE_SIZE,minIndex.y* TILE_SIZE);
	//MiniMap->Render4(miniDC, WINSIZE_X/2, WINSIZE_Y/3,false,1,minIndex,maxIndex);
	//MiniMap->Render4(hdc, WINSIZE_X/2, WINSIZE_Y - WINSIZE_Y / 3+10,false,1,minIndex,maxIndex);
	
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
	//int currIdX = tile.GetIdX();
	//int currIdY = tile.GetIdY();
	int currIdX = currTile->GetIdX();
	int currIdY = currTile->GetIdY();
	
	if (&tile == startTile&&tile.GetIsClosed()==false)
	{
		currTile = &tile;
		currTile->SetType(TileType::Room);

		(currTile)->setindex(index);
		(currTile)->SetIsClosed(true);
		AddOpenList(currTile);
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
				
				map[currIdY][currIdX + 5].SetColor(RGB(255, 255, 0));
				
				if (map[currIdY][currIdX + 5].GetIsClosed() == false) {
					currTile = &map[currIdY][currIdX + 5];

				}

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
		
				map[currIdY][currIdX - 5].SetColor(RGB(255, 255, 0));
				if (map[currIdY][currIdX - 5].GetIsClosed() == false) {
					currTile = &map[currIdY][currIdX - 5];
				}

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
	
				map[currIdY + 5][currIdX].SetColor(RGB(255, 255, 0));

				if (map[currIdY + 5][currIdX].GetIsClosed() == false) {
					currTile = &map[currIdY + 5][currIdX];
				}
				
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
		
				map[currIdY - 5][currIdX].SetColor(RGB(255, 255, 0));
				if (map[currIdY - 5][currIdX].GetIsClosed() == false) {
					currTile = &map[currIdY - 5][currIdX];
				}
			}

			break;
		default:
			break;
		}
		if (currTile->GetIsClosed() == false) {
			index++;
			currTile->SetType(TileType::Room);
			currTile->SetIsClosed(true);
			currTile->setindex(index);
			currTile->getindex();
			index = currTile->getindex();
			minIndex.x = min(minIndex.x, currTile->GetIdX());
			minIndex.y = min(minIndex.y, currTile->GetIdY());
			maxIndex.x = max(maxIndex.x, currTile->GetIdX());
			maxIndex.y = max(maxIndex.y, currTile->GetIdY());
			AddOpenList(currTile);
			roomnum = index;
			startPoint = { currTile->GetIdX(),currTile->GetIdY() };
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
