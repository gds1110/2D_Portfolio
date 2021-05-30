#pragma once
#include "config.h"
// 멤버 변수, 멤버 함수 원형 등이 선언

/*
	앞으로 만들어질 게임구조의 가장 기본이 되는 클래스
*/
class MapGenManager;
class GameNode
{
protected:
	DUNGEONINFO d_info;
	bool isDungeon = false;
public:
	virtual HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	virtual HRESULT DungoenInit(Tile* flowTile);			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	bool GetIsDungeon() { return this->isDungeon; }
	DUNGEONINFO GetDinfo() { return this->d_info; }
	void SetDinfo(DUNGEONINFO info) { this->d_info = info; }
	GameNode();
	virtual ~GameNode();
};

