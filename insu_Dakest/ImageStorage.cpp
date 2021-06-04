#include "ImageStorage.h"
#include "config.h"
HRESULT ImageStorage::Init()
{
	//cap
	ImageManager::GetSingleton()->AddImage("���̷���ĸƾ �Ĺ�", "resource/monster/skeleton_captain/combat/combat.BMP", 3706, 400, 17, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���ĸƾ �ǰ�", "resource/monster/skeleton_captain/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���ĸƾ ����", "resource/monster/skeleton_captain/defend/dead.BMP", 2480, 500, 6, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���ĸƾ ��ų1", "resource/monster/skeleton_captain/attack.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	//ar
	ImageManager::GetSingleton()->AddImage("���̷����ó �Ĺ�", "resource/monster/skeleton_arbalista/combat/combat.BMP", 2115, 300, 15, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷����ó �ǰ�", "resource/monster/skeleton_arbalista/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷����ó ����", "resource/monster/skeleton_arbalista/dead.BMP", 1980, 318, 10, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷����ó ��ų1", "resource/monster/skeleton_arbalista/attack.BMP", 300, 300, 1, 1, true, RGB(88, 88, 88));
	//common
	ImageManager::GetSingleton()->AddImage("���̷���Ŀ�� �Ĺ�", "resource/monster/skeleton_common/combat/combat.BMP", 2324, 250, 14, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���Ŀ�� �ǰ�", "resource/monster/skeleton_common/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���Ŀ�� ����", "resource/monster/skeleton_common/dead.BMP", 1730, 400, 10, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���̷���Ŀ�� ��ų1", "resource/monster/skeleton_common/attack.BMP", 400, 400, 1, 1, true, RGB(88, 88, 88));

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

	ImageManager::GetSingleton()->AddImage("��ų����", "resource/sharedUi/sel_skill.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���ҽ�ų", "resource/sharedUi/swap.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���Ͻ�ų", "resource/sharedUi/noturn.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("���þ�����2", "resource/sharedUi/seliconlist.BMP", 525, 69, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Ÿ�پ�����", "resource/sharedUi/target1.BMP", 179, 88, 1, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("�����þ�����", "resource/sharedUi/seliconlist.BMP", 525, 69, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("������", "resource/dungeon/UI/D_under_ui2.BMP", 1280, 240, false);
	ImageManager::GetSingleton()->AddImage("�̴ϸʹ��", "resource/sharedUi/downpanelmap.BMP", 480, 240, false);
	ImageManager::GetSingleton()->AddImage("ü�¹�", "resource/sharedUi/healthBar.BMP", 100, 10, false);
	ImageManager::GetSingleton()->AddImage("ü�¹ٹ��", "resource/sharedUi/healthBarBG.BMP", 100, 10, false);
	ImageManager::GetSingleton()->AddImage("��ƽ", "resource/sharedUi/turntick.BMP", 24, 27, true,RGB(255,0,255));
	ImageManager::GetSingleton()->AddImage("ü��ĭ", "resource/sharedUi/health_pip.BMP", 8, 10, false);
	ImageManager::GetSingleton()->AddImage("�̴ϸʹ���", "resource/mapui/mapbg.BMP", 1000, 1000, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("������", "resource/mapui/movingrooom.BMP", 30, 30, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�湮��", "resource/mapui/roomvisited.BMP", 30, 30, 1, 1, true, RGB(88,88, 88));
	ImageManager::GetSingleton()->AddImage("�湮���", "resource/mapui/pathvisited.BMP", 20, 20, 1, 1, true, RGB(88, 88, 88));


	ImageManager::GetSingleton()->AddImage("�й�", "resource/sharedUi/scene/defeat.BMP", WINSIZE_X, WINSIZE_Y, false);
	ImageManager::GetSingleton()->AddImage("�ε�", "resource/sharedUi/scene/loding.BMP", WINSIZE_X, WINSIZE_Y, false);

	ImageManager::GetSingleton()->AddImage("��������", "resource/sharedUi/fx/heal.BMP", 24, 24, true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("���Ͼ�����", "resource/sharedUi/fx/stun.BMP", 24, 24, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("��ũ������", "resource/sharedUi/fx/target.BMP", 24, 24, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("������Ʈ", "resource/sharedUi/fx/curefx22.BMP", 7392, 493,22,1,true,RGB(88,88,88));
	//ImageManager::GetSingleton()->AddImage("��������Ʈ", "resource/sharedUi/fx/stunfx.BMP", 2210, 169,13,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("��������Ʈ", "resource/sharedUi/fx/stunfx22.BMP", 2210, 169,13,1,true,RGB(114,114,114));
	ImageManager::GetSingleton()->AddImage("��������Ʈ", "resource/sharedUi/fx/deathfx.BMP", 6253, 481,13,1,true,RGB(0,0,0));
	//ImageManager::GetSingleton()->AddImage("�ǰ�����Ʈ��", "resource/sharedUi/fx/hurtfx.BMP", 12519, 721,13,1,true,RGB(88,88,88));
	//ImageManager::GetSingleton()->AddImage("�ǰ�����Ʈ��", "resource/sharedUi/fx/hurtfx.BMP", 12519, 721,13,1,true,RGB(88,88,88));
//	ImageManager::GetSingleton()->AddImage("�ǰ�����Ʈ��2", "resource/sharedUi/fx/hurtfx22.BMP", 12519, 721,13,1,true,RGB(82,93,116));
	ImageManager::GetSingleton()->AddImage("�ǰ�����Ʈ��", "resource/sharedUi/fx/right.BMP", 4500, 721,9,1,true,RGB(0,0,0));
//ImageManager::GetSingleton()->AddImage("�ǰ�����Ʈ��", "resource/sharedUi/fx/hurtfxL.BMP", 12519, 721,13,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("�ǰ�����Ʈ��", "resource/sharedUi/fx/left.BMP", 4500, 721,9,1,true,RGB(0,0,0));
	ImageManager::GetSingleton()->AddImage("Ÿ������Ʈ", "resource/sharedUi/fx/marktarget.BMP", 6800, 369,17,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("������Ʈ", "resource/sharedUi/fx/blood.BMP", 6390, 292,18,1,true,RGB(88,88,88));


	ImageManager::GetSingleton()->AddImage("��ų��ġ", "resource/sharedUi/skillstrength2.BMP", 120, 30, 4, 1, true, RGB(0, 0, 0));
	//ImageManager::GetSingleton()->AddImage("��ų��ġ", "resource/sharedUi/skillstrength.BMP", 156, 52, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("�κ��丮", "resource/sharedUi/inventory.BMP", 480, 240, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("�����۸��", "resource/sharedUi/itemlist.BMP", 150, 100, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("��ų����", "resource/sharedUi/skilltooltip2.BMP", 200, 128, 1, 1, true, RGB(88, 88, 88));
	//ImageManager::GetSingleton()->AddImage("��ų����", "resource/sharedUi/skilltooltip2.BMP", 128, 128, 1, 1, true, RGB(88, 88, 88));
	//ImageManager::GetSingleton()->AddImage("��ų����", "resource/sharedUi/skilltooltip.BMP", 103, 105, 1, 1, true, RGB(255, 255, 255));


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
