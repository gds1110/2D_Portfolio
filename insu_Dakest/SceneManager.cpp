#include "SceneManager.h"
#include "GameNode.h"
#include "Dungeon_1_1.h"
#include "MapGenManager.h"

GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

HRESULT SceneManager::Init()
{
    return S_OK;
}

void SceneManager::Release()
{
    map<string, GameNode*>::iterator it;
    for (it = mSceneDatas.begin(); it != mSceneDatas.end(); it++)
    {
        if (it->second)
        {
            SAFE_RELEASE(it->second);
        }
    }
    mSceneDatas.clear();

    ReleaseSingleton();
}

void SceneManager::Update()
{
    if (currentScene)
    {
        currentScene->Update();
    }
}

void SceneManager::Render(HDC hdc)
{
    if (currentScene)
    {
        currentScene->Render(hdc);
    }
}

GameNode* SceneManager::AddScene(string key, GameNode* scene)
{
    if (scene == nullptr)
    {
        return nullptr;
    }

    map<string, GameNode*>::iterator it = mSceneDatas.find(key);
    if (it != mSceneDatas.end())
    {
        return it->second;
    }

    mSceneDatas.insert(pair<string, GameNode*>(key, scene));

    return scene;
}

HRESULT SceneManager::ChangeScene(string key)
{
    //try
    //{

    //}
    //catch (const std::exception&)
    //{

    //}

    map<string, GameNode*>::iterator it = mSceneDatas.find(key);
    if (it == mSceneDatas.end())
    {
        return E_FAIL;
    }

    if (it->second == currentScene)
    {
        return S_OK;
    }

    if (SUCCEEDED(it->second->Init()))
    {
        // ���� �� -> Ÿ��Ʋ ��
        // �ٲٰ� ���� �� -> ��Ʋ ��
        if (currentScene)
        {
            currentScene->Release();
        }
        currentScene = it->second;

        return S_OK;
    }

    return E_FAIL;
}

HRESULT SceneManager::ChangeScene2(string key, Tile* tile)
{
    map<string, GameNode*>::iterator it = mSceneDatas.find(key);
    if (it == mSceneDatas.end())
    {
        return E_FAIL;
    }

    /*if (currentScene)
    {
        currentScene->Release();
        
    }*/
    //if (it->second == currentScene)
    //{
    //    return S_OK;
    //}
    if (it->second->GetIsDungeon()) {
        if (SUCCEEDED(it->second->DungoenInit(tile)))
        {
            // ���� �� -> Ÿ��Ʋ ��
            // �ٲٰ� ���� �� -> ��Ʋ ��
            {
                currentScene->Release();

            }
            currentScene = it->second;

            return S_OK;
        }
    }
    else {
        if (SUCCEEDED(it->second->Init()))
        {
            // ���� �� -> Ÿ��Ʋ ��
            // �ٲٰ� ���� �� -> ��Ʋ ��
            if (currentScene)
            {
                currentScene->Release();
            }
            currentScene = it->second;

            return S_OK;
        }
    }

    return E_FAIL;
}

HRESULT SceneManager::ChangeTile(Tile* tile)
{


    return S_OK;
}

