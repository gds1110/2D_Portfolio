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
	isPath = false;
	color = RGB(100, 100, 100);
	hBrush = CreateSolidBrush(color);
	size = 1;
	genCheck = false;

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
		if (isVisited == true)
		{

			tileImg = ImageManager::GetSingleton()->FindImage("방문통로");
		}
	}
	else if (type == TileType::Room)
	{
		tileImg = ImageManager::GetSingleton()->FindImage("던전방");
		rc.left = center.x - TILE_SIZE;
		rc.right = center.x + TILE_SIZE ;
		rc.top = center.y - TILE_SIZE;
		rc.bottom = center.y + TILE_SIZE ;
		if (isVisited == true)
		{

			tileImg = ImageManager::GetSingleton()->FindImage("방문룸");
		}
	}
	if (isCurrted==true)
	{
		tileIcon = ImageManager::GetSingleton()->FindImage("현재위치");
	}
	if (isDest == true)
	{
		tileIconFX=ImageManager::GetSingleton()->FindImage("무빙룸");
	}


	if (canWay)
	{
		size += TimerManager::GetSingleton()->GetElapsedTime();
		if (size > 1.2f)
		{
			size = 1.0f;
		}
		
	}
	
}

void Tile::Render(HDC hdc)
{
	if (tileImg) {
		tileImg->Render2(hdc, center.x, center.y, true, size);

		if (index > -1) {
	
		}
		if (tileIcon)
		{
			if (isCurrted) {
				tileIcon->Render(hdc, center.x, center.y, true);
				
	
			}
		}
		if (tileIconFX)
		{
			if (isDest == true) {
				tileIconFX->Render(hdc, center.x, center.y, true);
			}
		}
	}
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}


void Tile::RandomSetTileInfo()
{
	int randomn = 0;
	int random2 = 0;
	int monrandom = 0;
	int randtype = 0;
	int monnum;
	if (isStarted)
	{
		/*isEnemyed = true;
		for (int i = 0; i < 4; i++)
		{
			enemyArr[i] = 0;
		}*/
		d_info.dType = DungeonType::START;
		d_info.infoDone = true;
		d_info.isCurrted = true;
	}
	if (!isStarted)
	{
		
		randomn = rand() % 2;
		random2 = rand() % 101;
		randtype = rand() % 6;
		if (type == TileType::Room)
		{
			d_info.dType = DungeonType::ROOM;
			d_info.isEnemyed = randomn;
			d_info.roomType = randtype;
		}
		if (type == TileType::Path)
		{
			d_info.dType = DungeonType::PATH;

			if (random2 > 66)
			{
				
				d_info.isEnemyed = true;
				d_info.roomType = randtype;
			}
			d_info.isEnemyed = true; // 지워야할거
		}
	}
	if (d_info.isEnemyed)
	{
		monnum = rand() % 3+1;
		d_info.enemySize = monnum;
		d_info.enemySize = 4; // 지워야할거
		for (int i = 0; i < d_info.enemySize; i++)
		{
			monrandom = rand() % 4;
	
			d_info.enemyArr[i] = monrandom;
			//d_info.enemyArr[i] = 1; //지워야할거
		}
		d_info.infoDone = true;

	}
	else
	{
		d_info.infoDone = true;

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
	/*MiniMap = new Image();
	MiniMap->Init(1000, 1000);*/
	MiniMap = ImageManager::GetSingleton()->FindImage("미니맵배경색");
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

		MakePath(*currTile);
	

	}
	else
		{
			minimapdone = true;
			//map[startPoint.y][startPoint.x].SetIsCurrted(true);
			map[startPoint.y][startPoint.x].SetIsStarted(true);

			for (int i = 0; i < openList.size(); i++)
			{
				openList[i]->SetPos(20+(openList[i]->GetIdX() * TILE_SIZE) - (minIndex.x * TILE_SIZE), 20+(openList[i]->GetIdY() * TILE_SIZE) - (minIndex.y * TILE_SIZE));
				openList[i]->RandomSetTileInfo();
					if (openList[i]->GetIsCurrted()) {
						//openList[i]->SetIsCurrted(true);
					}
			}
	}

	

	if (minimapdone == true)
	{
		//TODO : 여기서 가로 세로 prev and next 체크
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->GetGenCheck() == false) {
				if (openList[i]->GetType() == TileType::Room)

				{
					if (openList[i]->GetIdX() - 5 > 0 && map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].GetType() == TileType::Room)
					{
						if (map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1].GetType() == TileType::Path)
						{
							/*	Tile* Prev = &map[openList[i]->GetIdY()][openList[i]->GetIdX()];
								Tile* temp = (&map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1]);
								Tile* tempnext = (&map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5]);*/
							openList[i]->SetFourDir(0, map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].getindex());
							map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
							map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5].getindex() });
							map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1].SetPathDir(PathDir::LEFT);
							openList[i]->addWay(&map[openList[i]->GetIdY()][openList[i]->GetIdX() - 5]);
						}
					}
					if (openList[i]->GetIdX() + 5 < TILE_COUNT && map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].GetType() == TileType::Room)
					{
						if (map[openList[i]->GetIdY()][openList[i]->GetIdX() + 1].GetType() == TileType::Path)
						{

							openList[i]->SetFourDir(1, map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].getindex());
							map[openList[i]->GetIdY()][openList[i]->GetIdX() + 1].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
							map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5].getindex() });
							map[openList[i]->GetIdY()][openList[i]->GetIdX() - 1].SetPathDir(PathDir::RIGHT);
							openList[i]->addWay(&map[openList[i]->GetIdY()][openList[i]->GetIdX() + 5]);



						}
					}
					if (openList[i]->GetIdY() - 5 > 0 && map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()].GetType() == TileType::Room)
					{
						if (map[openList[i]->GetIdY() - 1][openList[i]->GetIdX()].GetType() == TileType::Path)
						{

							openList[i]->SetFourDir(2, map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()].getindex());
							map[openList[i]->GetIdY() - 1][openList[i]->GetIdX()].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
							map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()].getindex() });
							map[openList[i]->GetIdY() - 1][openList[i]->GetIdX()].SetPathDir(PathDir::TOP);
							openList[i]->addWay(&map[openList[i]->GetIdY() - 5][openList[i]->GetIdX()]);


						}
					}
					if (openList[i]->GetIdY() + 5 < TILE_COUNT && map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].GetType() == TileType::Room)
					{
						if (map[openList[i]->GetIdY() + 1][openList[i]->GetIdX()].GetType() == TileType::Path)
						{

							openList[i]->SetFourDir(3, map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].getindex());
							map[openList[i]->GetIdY() + 1][openList[i]->GetIdX()].SetPrevNnext({ map[openList[i]->GetIdY()][openList[i]->GetIdX()].getindex(),
							map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()].getindex() });
							map[openList[i]->GetIdY() + 1][openList[i]->GetIdX()].SetPathDir(PathDir::BOTTOM);
							openList[i]->addWay(&map[openList[i]->GetIdY() + 5][openList[i]->GetIdX()]);


						}
					}
				}
			}
			openList[i]->SetGenCheck(true);
		}

		Tile *tempTile = (currTile);
		UiDataManager::GetSingleton()->SetMiniMap(openList);
		UiDataManager::GetSingleton()->SetCurrtile(tempTile);
		UiDataManager::GetSingleton()->SetMapimg(MiniMap);
		UiDataManager::GetSingleton()->SetMin(minIndex);
		UiDataManager::GetSingleton()->SetMax(maxIndex);
		UiDataManager::GetSingleton()->SetMapGeN(this);
		UiDataManager::GetSingleton()->SetSceneInfo(UiDataManager::SceneInfo::MAPGEN, UiDataManager::SceneInfo::ROOM);
		SceneManager::GetSingleton()->ChangeTile(UiDataManager::GetSingleton()->GetTile());

		return;
	}

	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
	//{
	//	

	//	UiDataManager::GetSingleton()->SetSceneInfo(UiDataManager::SceneInfo::MAPGEN, UiDataManager::SceneInfo::ROOM);
	//	SceneManager::GetSingleton()->ChangeTile(UiDataManager::GetSingleton()->GetTile());

	//	return;
	//}

}

void MapGenManager::Render(HDC hdc)
{
	/*
	HDC miniDC = MiniMap->GetMemDC();
	UiDataManager::GetSingleton()->SetHdc(miniDC);
	if (minimapdone) {
		for (int i = 0; i < openList.size(); i++)
		{
			openList[i]->Render(miniDC);
		}
	}
	MiniMap->Render(hdc);*/
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->GetIsPath()) {
			wsprintf(szText, "X : %d, Y : %d", openList[i]->GetPrevNnext().x, openList[i]->GetPrevNnext().y);
			TextOut(hdc, i * 20, 30*i%10, szText, strlen(szText));
		}
	}

	
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
					map[currIdY][currIdX + i].SetDinfoDtype(DungeonType::PATH);
					if (map[currIdY][currIdX + i].GetIsInOpenlist() == false) {
						map[currIdY][currIdX + 1].addPath(&map[currIdY][currIdX + i]);

						map[currIdY][currIdX + i].SetIsInOpenlist(true);
						if (i == 1) {
							map[currIdY][currIdX + 1].SetPrevAndNextTile(&map[currIdY][currIdX], &map[currIdY][currIdX + 5]);
							map[currIdY][currIdX + 1].SetIsPath(true);
							
						}
						AddOpenList(&map[currIdY][currIdX + i]);
					}
				}
				
				
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
					map[currIdY][currIdX - i].SetDinfoDtype(DungeonType::PATH);

					if (map[currIdY][currIdX - i].GetIsInOpenlist() == false) {
						map[currIdY][currIdX - 1].addPath(&map[currIdY][currIdX - i]);

						map[currIdY][currIdX - i].SetIsInOpenlist(true);
						if (i == 1) {
							map[currIdY][currIdX - 1].SetPrevAndNextTile(&map[currIdY][currIdX], &map[currIdY][currIdX - 5]);
							map[currIdY][currIdX - 1].SetIsPath(true);
						}
						AddOpenList(&map[currIdY][currIdX - i]);
					}

				}
		
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
					map[currIdY + i][currIdX].SetDinfoDtype(DungeonType::PATH);

					if (map[currIdY + i][currIdX].GetIsInOpenlist() == false) {
						map[currIdY+1][currIdX ].addPath(&map[currIdY+i][currIdX ]);

						map[currIdY + i][currIdX].SetIsInOpenlist(true);
						if (i == 1) {

							map[currIdY + 1][currIdX].SetPrevAndNextTile(&map[currIdY][currIdX], &map[currIdY + 5][currIdX]);
							map[currIdY + 1][currIdX].SetIsPath(true);
						}
						AddOpenList(&map[currIdY + i][currIdX]);
					}

				}
	

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
					map[currIdY - i][currIdX].SetDinfoDtype(DungeonType::PATH);

					if (map[currIdY - i][currIdX].GetIsInOpenlist() == false) {
						map[currIdY - 1][currIdX].addPath(&map[currIdY - i][currIdX]);

						map[currIdY - i][currIdX].SetIsInOpenlist(true);
						if (i == 1) {
							map[currIdY - 1][currIdX].SetPrevAndNextTile(&map[currIdY][currIdX], &map[currIdY - 5][currIdX]);
							map[currIdY - 1][currIdX].SetIsPath(true);
						}
						AddOpenList(&map[currIdY - i][currIdX]);
					}

				}
		
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
			currTile->SetDinfoDtype(DungeonType::ROOM);
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
