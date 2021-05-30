#include "ImageStorage.h"
#include "config.h"
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
	ImageManager::GetSingleton()->AddImage("�����Ա�", "resource/dungeon/Stage1/Entrance.BMP", 1920, 720, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���Ÿ����", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�ٰŸ�", "resource/dungeon/Stage1/NearBG.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�������1", "resource/dungeon/Stage1/PassageBG1.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�������2", "resource/dungeon/Stage1/PassageBG2.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�������3", "resource/dungeon/Stage1/PassageBG3.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�������4", "resource/dungeon/Stage1/PassageBG4.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�������5", "resource/dungeon/Stage1/PassageBG5.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�������6", "resource/dungeon/Stage1/PassageBG6.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���ۻ���", "resource/StartTown/townhome.bmp",WINSIZE_X , WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("�ν��͹��", "resource/StartTown/rosterbg2.bmp",250 , 70);
	ImageManager::GetSingleton()->AddImage("��߹�ư", "resource/StartTown/startButton.bmp",225 , 94,1,2,false);




	ImageManager::GetSingleton()->AddImage("���þ�����", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ÿ�پ�����", "resource/sharedUi/target.BMP", 197, 412, 1, 2, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("��������", "resource/sharedUi/target_h.BMP", 175, 206, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�̴ϸʹ���", "resource/mapui/mapbg.BMP", 600, 600, 1, 1, true, RGB(255, 0, 255));
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
