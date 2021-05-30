#pragma once
#include "config.h"
// ��� ����, ��� �Լ� ���� ���� ����

/*
	������ ������� ���ӱ����� ���� �⺻�� �Ǵ� Ŭ����
*/
class MapGenManager;
class GameNode
{
protected:
	DUNGEONINFO d_info;
	bool isDungeon = false;
public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual HRESULT DungoenInit(Tile* flowTile);			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	bool GetIsDungeon() { return this->isDungeon; }
	DUNGEONINFO GetDinfo() { return this->d_info; }
	void SetDinfo(DUNGEONINFO info) { this->d_info = info; }
	GameNode();
	virtual ~GameNode();
};

