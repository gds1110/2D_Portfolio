#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <map>
#include <string>

using namespace std;

class Dungeon_1_1;
class Tile;
class MapGenManager;
class GameNode;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameNode*>	mSceneDatas;

public:
	static GameNode* currentScene;
	static GameNode* loadingScene;
	static GameNode* readyScene;
	static Dungeon_1_1* prevDungeon;
	static Dungeon_1_1* currentDungeon;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	GameNode* AddScene(string key, GameNode* scene);
	HRESULT ChangeScene(string key);
	HRESULT ChangeScene2(string key,Tile* tile);

	HRESULT ChangeTile(Tile* tile);

};

