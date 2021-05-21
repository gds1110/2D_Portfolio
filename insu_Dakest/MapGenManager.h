#pragma once
#include "GameNode.h"


enum class TileType { Start, End, Path, Room, None };
class Image;
class Tile : public GameNode
{
private:
	int idX, idY;
	POINT center;
	RECT rc;
	TileType type;
	int index = 0;
	int costFromStart;	// g : ���������� ���� �������� ���
	int costToGoal;		// h : ���� ������ ������������ ������
	int totalCost;		// f : g + h

	Tile* parentTile;	// g�� ���ŵ� ������ ���� ��带 ����
	Tile* prevTile;
	vector<int> way;
	Image* tileImg;
	bool isInOpenlist;
	bool isClosed;

	int fourDir[4] = { -1,-1,-1,-1 };

	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hOldBrush;

	char szText[128];

	// heap ����
	int heapIndex;

public:
	virtual HRESULT Init();
	HRESULT Init(int idX, int idY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void Render2(HDC hdc,int x,int y);
	void setindex(int i) { this->index = i; }
	int getindex() { return this->index; }
	void SetColor(COLORREF color);
	void SetType(TileType type) { this->type = type; }
	TileType GetType() { return this->type; }
	int GetIdX() { return this->idX; }
	int GetIdY() { return this->idY; }

	POINT getPos() { return this->center; }
	void SetPos(int x, int y)
	{
		center.x = x;
		center.y = y;
	}

	int* GetFourDir() { return this->fourDir; }
	void SetFourDir(int a, int b) { this->fourDir[a] = b; }

	void addWay(int i) { way.push_back(i); }
	vector<int> GetWay() { return this->way; }

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

	virtual ~Tile() {};

};

class MapGenManager : public GameNode
{
	// ������ �迭 ���� ����
	Tile map[TILE_COUNT][TILE_COUNT];

	Tile* startTile;	// ������
	Tile* destTile;	// �Ķ���
	int index = 0;
	Tile* currTile;	// (���) �ĺ�Ÿ���� ������ ���� ����Ÿ��
	POINT min;
	vector<Tile*> openList;
	vector<Tile*> closeList;
	vector<Tile*> heap;
	char szText[128];
	int roomnum;

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

