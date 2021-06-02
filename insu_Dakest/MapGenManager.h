#pragma once
#include "GameNode.h"


enum class TileType { Start, End, Path, Room, None };
class Image;
class Tile : public GameNode
{
private:

private:
	int idX, idY;
	POINT center;
	RECT rc;
	TileType type;
	int index = 0;
	int costFromStart;	// g : 시작점부터 현재 노드까지의 비용
	int costToGoal;		// h : 현재 노드부터 목적지까지의 예상비용
	int totalCost;		// f : g + h

	bool genCheck;

	Tile* parentTile;	// g가 갱신될 때마다 이전 노드를 갱신
	vector<Tile*> way;
	vector<Tile*> Path;
	Image* tileImg;
	Image* tileIcon;
	Image* tileIconFX;
	bool isInOpenlist;
	bool isClosed;
	char szText[128];

	int fourDir[4] = { -1,-1,-1,-1 };

	POINT prevNnext = { 0,0 };
	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hOldBrush;

	bool isDest;
	bool isStarted;
	bool isCurrted;
	bool canWay;
	bool isPath;
	bool isVisited;

	float size;

	Tile* prevTile;
	Tile* nextTile;
	// heap 관련
	int heapIndex;

public:
	virtual HRESULT Init();
	HRESULT Init(int idX, int idY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	
	void SetIsEnemy(bool is) { this->d_info.isEnemyed = is; }

	void SetIsVisited(bool is) { this->isVisited = is; }
	void SetIsDest(bool is) { this->isDest = is; }

	void SetIsPath(bool is) { this->isPath = is; }
	bool GetIsPath() { return this->isPath; }

	void SetGenCheck(bool is) { this->genCheck = is; }
	bool GetGenCheck() { return this->genCheck; }

	void SetIsCurrted(bool is) { this->isCurrted = is; }
	bool GetIsCurrted() { return this->isCurrted; }
	void SetIsStarted(bool is) { this->isStarted = is; }
	bool GetIsStarted() { return this->isStarted; }
	void SetIsWay(bool is) { this->canWay = true; }

	void SetPathDir(PathDir dir)
	{
		d_info.pathDir = dir;
	}
	Tile* GetPrevTile() { return this->prevTile; }
	Tile* GetNextTile() { return this->nextTile; }

	void SetPrevAndNextTile(Tile* prev, Tile* next)
	{
		this->prevTile = prev;
		this->nextTile = next;
	}
	void SetPrevNnext(POINT prNne) {
		this->prevNnext = prNne;
		this->d_info.prevAnNext = prNne;
	}
	POINT GetPrevNnext() { return this->prevNnext; }

	void RandomSetTileInfo();

	void setindex(int i) { this->index = i; }
	int getindex() { return this->index; }

	void SetColor(COLORREF color);
	void SetType(TileType type) { this->type = type; }
	TileType GetType() { return this->type; }
	void SetDinfoDtype(DungeonType type) { this->d_info.dType = type; }
	DungeonType GetDungeonTypes() { return this->d_info.dType; }
	int GetIdX() { return this->idX; }
	int GetIdY() { return this->idY; }

	POINT getPos() { return this->center; }
	POINT getPos2() { return this->d_info.pos; }
	void SetPos(int x, int y)
	{
		center.x = x;
		center.y = y;
		d_info.pos.x = x;
		d_info.pos.y = y;
	}

	int* GetFourDir() { return this->fourDir; }
	void SetFourDir(int a, int b) { this->fourDir[a] = b; }

	void addWay(Tile* i) { way.push_back(i); }
	vector<Tile*> GetWay() { return this->way; }

	void addPath(Tile* i) { Path.push_back(i); }
	vector<Tile*> GetPath() { return this->Path; }

	void SetParentTile(Tile* parent) { this->parentTile = parent; }
	Tile* GetParentTile() { return this->parentTile; }

	void SetG(int g) { this->costFromStart = g; }
	int GetG() { return this->costFromStart; }

	void SetH(int h) { this->costToGoal = h; }
	int GetH() { return this->costToGoal; }

	void SetF(int f) { this->totalCost = f; }
	int GetF() { return this->totalCost; }

	void SetIsInOpenlist(bool b) { this->isInOpenlist = b; }
	bool GetIsInOpenlist() { return this->isInOpenlist; }

	void SetIsClosed(bool b) { this->isClosed = b; }
	bool GetIsClosed() { return this->isClosed; }



	void SetHeapIndex(int id) { this->heapIndex = id; }
	int GetHeapIndex() { return this->heapIndex; }

	RECT GetRC() { return this->rc; }

	virtual ~Tile() {};

};

class Image;
class MapGenManager : public GameNode
{
	// 이차원 배열 맵을 구성
	Tile map[TILE_COUNT][TILE_COUNT];

	Tile* startTile;	// 빨간색
	Tile* destTile;	// 파란색
	int index = 0;
	Tile* currTile;	// (녹색) 후보타일을 선정할 때의 기준타일
	POINT min;
	vector<Tile*> openList;
	vector<Tile*> closeList;
	vector<Tile*> heap;
	char szText[128];
	int roomnum;
	POINT minIndex = { 99,99 };
	POINT maxIndex = { -1,-1 };
	RECT mapview;
	POINT startPoint = { 999,999 };
	Image* MiniMap;
	bool minimapdone;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void Render2(HDC hdc);
	void MakePath(Tile& tile);
	void FindPath();
	void AddOpenList(Tile* currTile);

	void UpdateLower(Tile* tile);
	void Swap(Tile* tile1,Tile* tile2);
	void UpdateUpper(Tile* tile);

	void DeleteTileInOpenlist(Tile* tile);

	void MarkTileToType();

	virtual ~MapGenManager() {};


};

