#include "ImageStorage.h"
#include "config.h"
HRESULT ImageStorage::Init()
{
	//cap
	ImageManager::GetSingleton()->AddImage("스켈레톤캡틴 컴뱃", "resource/monster/skeleton_captain/combat/combat.BMP", 3706, 400, 17, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤캡틴 피격", "resource/monster/skeleton_captain/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤캡틴 데드", "resource/monster/skeleton_captain/defend/dead.BMP", 2480, 500, 6, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤캡틴 스킬1", "resource/monster/skeleton_captain/attack.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	//ar
	ImageManager::GetSingleton()->AddImage("스켈레톤아처 컴뱃", "resource/monster/skeleton_arbalista/combat/combat.BMP", 2115, 300, 15, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤아처 피격", "resource/monster/skeleton_arbalista/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤아처 데드", "resource/monster/skeleton_arbalista/dead.BMP", 1980, 318, 10, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤아처 스킬1", "resource/monster/skeleton_arbalista/attack.BMP", 300, 300, 1, 1, true, RGB(88, 88, 88));
	//common
	ImageManager::GetSingleton()->AddImage("스켈레톤커먼 컴뱃", "resource/monster/skeleton_common/combat/combat.BMP", 2324, 250, 14, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤커먼 피격", "resource/monster/skeleton_common/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤커먼 데드", "resource/monster/skeleton_common/dead.BMP", 1730, 400, 10, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스켈레톤커먼 스킬1", "resource/monster/skeleton_common/attack.BMP", 400, 400, 1, 1, true, RGB(88, 88, 88));

	ImageManager::GetSingleton()->AddImage("방세트", "resource/dungeon/Stage1/rooms.BMP", 1920, 4320, 1, 6, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("던전입구", "resource/dungeon/Stage1/Entrance.BMP", 1920, 720, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("원거리배경", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("근거리", "resource/dungeon/Stage1/NearBG.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("복도배경1", "resource/dungeon/Stage1/PassageBG1.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("복도배경2", "resource/dungeon/Stage1/PassageBG2.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("복도배경3", "resource/dungeon/Stage1/PassageBG3.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("복도배경4", "resource/dungeon/Stage1/PassageBG4.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("복도배경5", "resource/dungeon/Stage1/PassageBG5.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("복도배경6", "resource/dungeon/Stage1/PassageBG6.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("시작상점", "resource/StartTown/townhome.bmp",WINSIZE_X , WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("로스터배경", "resource/StartTown/rosterbg2.bmp",250 , 70);
	ImageManager::GetSingleton()->AddImage("출발버튼", "resource/StartTown/startButton.bmp",225 , 94,1,2,false);

	ImageManager::GetSingleton()->AddImage("스킬선택", "resource/sharedUi/sel_skill.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("스왑스킬", "resource/sharedUi/swap.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("노턴스킬", "resource/sharedUi/noturn.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("선택아이콘2", "resource/sharedUi/seliconlist.BMP", 525, 69, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("타겟아이콘", "resource/sharedUi/target1.BMP", 179, 88, 1, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("힐선택아이콘", "resource/sharedUi/seliconlist.BMP", 525, 69, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("유아이", "resource/dungeon/UI/D_under_ui2.BMP", 1280, 240, false);
	ImageManager::GetSingleton()->AddImage("미니맵배경", "resource/sharedUi/downpanelmap.BMP", 480, 240, false);
	ImageManager::GetSingleton()->AddImage("체력바", "resource/sharedUi/healthBar.BMP", 100, 10, false);
	ImageManager::GetSingleton()->AddImage("체력바배경", "resource/sharedUi/healthBarBG.BMP", 100, 10, false);
	ImageManager::GetSingleton()->AddImage("턴틱", "resource/sharedUi/turntick.BMP", 24, 27, true,RGB(255,0,255));
	ImageManager::GetSingleton()->AddImage("체력칸", "resource/sharedUi/health_pip.BMP", 8, 10, false);
	ImageManager::GetSingleton()->AddImage("미니맵배경색", "resource/mapui/mapbg.BMP", 1000, 1000, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("무빙룸", "resource/mapui/movingrooom.BMP", 30, 30, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("방문룸", "resource/mapui/roomvisited.BMP", 30, 30, 1, 1, true, RGB(88,88, 88));
	ImageManager::GetSingleton()->AddImage("방문통로", "resource/mapui/pathvisited.BMP", 20, 20, 1, 1, true, RGB(88, 88, 88));


	ImageManager::GetSingleton()->AddImage("패배", "resource/sharedUi/scene/defeat.BMP", WINSIZE_X, WINSIZE_Y, false);
	ImageManager::GetSingleton()->AddImage("로딩", "resource/sharedUi/scene/loding.BMP", WINSIZE_X, WINSIZE_Y, false);

	ImageManager::GetSingleton()->AddImage("힐아이콘", "resource/sharedUi/fx/heal.BMP", 24, 24, true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("스턴아이콘", "resource/sharedUi/fx/stun.BMP", 24, 24, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("마크아이콘", "resource/sharedUi/fx/target.BMP", 24, 24, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("힐이펙트", "resource/sharedUi/fx/curefx22.BMP", 7392, 493,22,1,true,RGB(88,88,88));
	//ImageManager::GetSingleton()->AddImage("스턴이펙트", "resource/sharedUi/fx/stunfx.BMP", 2210, 169,13,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("스턴이펙트", "resource/sharedUi/fx/stunfx22.BMP", 2210, 169,13,1,true,RGB(114,114,114));
	ImageManager::GetSingleton()->AddImage("죽음이펙트", "resource/sharedUi/fx/deathfx.BMP", 6253, 481,13,1,true,RGB(0,0,0));
	//ImageManager::GetSingleton()->AddImage("피격이펙트오", "resource/sharedUi/fx/hurtfx.BMP", 12519, 721,13,1,true,RGB(88,88,88));
	//ImageManager::GetSingleton()->AddImage("피격이펙트오", "resource/sharedUi/fx/hurtfx.BMP", 12519, 721,13,1,true,RGB(88,88,88));
//	ImageManager::GetSingleton()->AddImage("피격이펙트오2", "resource/sharedUi/fx/hurtfx22.BMP", 12519, 721,13,1,true,RGB(82,93,116));
	ImageManager::GetSingleton()->AddImage("피격이펙트오", "resource/sharedUi/fx/right.BMP", 4500, 721,9,1,true,RGB(0,0,0));
//ImageManager::GetSingleton()->AddImage("피격이펙트왼", "resource/sharedUi/fx/hurtfxL.BMP", 12519, 721,13,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("피격이펙트왼", "resource/sharedUi/fx/left.BMP", 4500, 721,9,1,true,RGB(0,0,0));
	ImageManager::GetSingleton()->AddImage("타겟이펙트", "resource/sharedUi/fx/marktarget.BMP", 6800, 369,17,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("피이펙트", "resource/sharedUi/fx/blood.BMP", 6390, 292,18,1,true,RGB(88,88,88));


	ImageManager::GetSingleton()->AddImage("스킬위치", "resource/sharedUi/skillstrength2.BMP", 120, 30, 4, 1, true, RGB(0, 0, 0));
	//ImageManager::GetSingleton()->AddImage("스킬위치", "resource/sharedUi/skillstrength.BMP", 156, 52, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("인벤토리", "resource/sharedUi/inventory.BMP", 480, 240, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("아이템목록", "resource/sharedUi/itemlist.BMP", 150, 100, 3, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("스킬툴팁", "resource/sharedUi/skilltooltip2.BMP", 200, 128, 1, 1, true, RGB(88, 88, 88));
	//ImageManager::GetSingleton()->AddImage("스킬툴팁", "resource/sharedUi/skilltooltip2.BMP", 128, 128, 1, 1, true, RGB(88, 88, 88));
	//ImageManager::GetSingleton()->AddImage("스킬툴팁", "resource/sharedUi/skilltooltip.BMP", 103, 105, 1, 1, true, RGB(255, 255, 255));


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
