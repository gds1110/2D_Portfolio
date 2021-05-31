#pragma once
#include "GameNode.h"


enum class TileType { Start, End, Path, Room, None };
class Image;
class Tile : public GameNode
{
private:
	struct TileStruct
	{
		bool isEnemyed = false;
		bool isSuddenEnemy = false;
		bool isCurios = false;
		int roomType=-1;
		int pathType=-1;
		int enemyArr[4] = { -1,-1,-1,-1 };
		bool tileDone = false;
	};
private:
	int idX, idY;
	POINT center;
	RECT rc;
	TileType type;
	int index = 0;
	int costFromStart;	// g : 시작점부터 현재 노드까지의 비용
	int costToGoal;		// h : 현재 노드부터 목적지까지의 예상비용
	int totalCost;		// f : g + h

	Tile* parentTile;	// g가 갱신될 때마다 이전 노드를 갱신
	Tile* prevTile;
	vector<Tile*> way;
	Image* tileImg;
	Image* tileIcon;
	bool isInOpenlist;
	bool isClosed;

	int fourDir[4] = { -1,-1,-1,-1 };

	POINT prevNnext = { 0,0 };
	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hOldBrush;

	bool startPoint;
	bool currtPoint;
	bool EnemyPoint;
	float size;

	TileStruct infoRoom;
	//출발위치, 현재위치, 적이있는가,기습유무,방 타입, 통로 타입, 골동품 유무, 
	bool roomInfo[7] = { 0,0,0,0,0,0,0 };
	char szText[128];
	bool isStarted = false;
	bool isCurrted = false;
	bool isEnemyed = false;
	bool isSuddenEnemy = false;
	bool isCurios = false;
	bool canWay = false;
	int roomType = -1;
	int pathType = -1;
	int enemyArr[4] = { -1,-1,-1,-1 };
	
	// heap 관련
	int heapIndex;

public:
	virtual HRESULT Init();
	HRESULT Init(int idX, int idY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPathDir(PathDir dir)
	{
		d_info.pathDir = dir;
	}

	void SetPrevNnext(POINT prNne) {
		this->prevNnext = prNne;
		this->d_info.prevAnNext = prNne;
	}
	POINT GetPrevNnext() { return this->prevNnext; }

	int* GetEnemyArr() { return this->enemyArr; }
	bool GetIsEnemyed() { return this->isEnemyed; }
	void SetIsStarted(bool is) { this->isStarted = is; }
	bool GetIsStarted() { return this->isStarted; }
	void SetIsCurrted(bool is) { this->isCurrted = is; }
	bool GetIsCurrted() { return this->isCurrted; }

	TileStruct GetTileinfo() { return this->infoRoom; }
	void RandomSetTileInfo();

	void setindex(int i) { this->index = i; }
	int getindex() { return this->index; }

	void SetColor(COLORREF color);
	void SetType(TileType type) { this->type = type; }

	TileType GetType() { return this->type; }

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


	void SetIsWay(bool b) { this->canWay = b; }
	bool GetIsWay() { return this->canWay; }

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

