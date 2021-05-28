#include "ImageStorage.h"

HRESULT ImageStorage::Init()
{
	ImageManager::GetSingleton()->AddImage("���̷���ĸƾ �Ĺ�", "resource/monster/skeleton_captain/combat/combat.BMP", 3706, 400, 17, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���ĸƾ �ǰ�", "resource/monster/skeleton_captain/defend/hurt.BMP", 400, 500, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷����ó �Ĺ�", "resource/monster/skeleton_arbalista/combat/combat.BMP", 2115, 250, 15, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷����ó �ǰ�", "resource/monster/skeleton_arbalista/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���Ŀ�� �Ĺ�", "resource/monster/skeleton_common/combat/combat.BMP", 2324, 250, 14, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���Ŀ�� �ǰ�", "resource/monster/skeleton_common/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷��汳�� �Ĺ�", "resource/monster/skeleton_bearer/combat/combat.BMP", 5468, 500,17, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷��汳�� �ǰ�", "resource/monster/skeleton_bearer/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�漼Ʈ", "resource/dungeon/Stage1/rooms.BMP", 1920, 4320, 1, 6, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�����Ա�", "resource/dungeon/Stage1/Entrance.BMP", 1300, 480, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���Ÿ����", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�ٰŸ�", "resource/dungeon/Stage1/NearBG.BMP", 4320, 480, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�������1", "resource/dungeon/Stage1/PassageBG1.BMP", 2900, 480, true, RGB(88, 88, 88));

	return S_OK;
}

void ImageStorage::Release()
{
}

void ImageStorage::Update()
{
}

void ImageStorage::Render(HDC hdc)
{
}
