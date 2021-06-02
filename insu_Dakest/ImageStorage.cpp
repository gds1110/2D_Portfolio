#include "ImageStorage.h"
#include "config.h"
HRESULT ImageStorage::Init()
{
	//cap
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒ∏∆æ ƒƒπÓ", "resource/monster/skeleton_captain/combat/combat.BMP", 3706, 400, 17, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒ∏∆æ ««∞›", "resource/monster/skeleton_captain/defend/hurt.BMP", 400, 500, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒ∏∆æ µ•µÂ", "resource/monster/skeleton_captain/defend/dead.BMP", 2480, 500, 6, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒ∏∆æ Ω∫≈≥1", "resource/monster/skeleton_captain/attack.BMP", 400, 500, 1, 1, true, RGB(88, 88, 88));
	//ar
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êæ∆√≥ ƒƒπÓ", "resource/monster/skeleton_arbalista/combat/combat.BMP", 2115, 250, 15, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êæ∆√≥ ««∞›", "resource/monster/skeleton_arbalista/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êæ∆√≥ µ•µÂ", "resource/monster/skeleton_arbalista/dead.BMP", 1980, 318, 10, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êæ∆√≥ Ω∫≈≥1", "resource/monster/skeleton_arbalista/attack.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	//common
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒø∏’ ƒƒπÓ", "resource/monster/skeleton_common/combat/combat.BMP", 2324, 250, 14, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒø∏’ ««∞›", "resource/monster/skeleton_common/defend/hurt.BMP", 300, 400, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒø∏’ µ•µÂ", "resource/monster/skeleton_common/dead.BMP", 1730, 400, 10, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ƒÃ∑π≈Êƒø∏’ Ω∫≈≥1", "resource/monster/skeleton_common/attack.BMP", 578, 551, 1, 1, true, RGB(88, 88, 88));

	ImageManager::GetSingleton()->AddImage("πÊºº∆Æ", "resource/dungeon/Stage1/rooms.BMP", 1920, 4320, 1, 6, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("¥¯¿¸¿‘±∏", "resource/dungeon/Stage1/Entrance.BMP", 1920, 720, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("ø¯∞≈∏ÆπË∞Ê", "resource/dungeon/Stage1/DistanceBG.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("±Ÿ∞≈∏Æ", "resource/dungeon/Stage1/NearBG.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("∫πµµπË∞Ê1", "resource/dungeon/Stage1/PassageBG1.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("∫πµµπË∞Ê2", "resource/dungeon/Stage1/PassageBG2.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("∫πµµπË∞Ê3", "resource/dungeon/Stage1/PassageBG3.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("∫πµµπË∞Ê4", "resource/dungeon/Stage1/PassageBG4.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("∫πµµπË∞Ê5", "resource/dungeon/Stage1/PassageBG5.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("∫πµµπË∞Ê6", "resource/dungeon/Stage1/PassageBG6.BMP", 4320, 720, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω√¿€ªÛ¡°", "resource/StartTown/townhome.bmp",WINSIZE_X , WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("∑ŒΩ∫≈ÕπË∞Ê", "resource/StartTown/rosterbg2.bmp",250 , 70);
	ImageManager::GetSingleton()->AddImage("√‚πﬂπˆ∆∞", "resource/StartTown/startButton.bmp",225 , 94,1,2,false);

	ImageManager::GetSingleton()->AddImage("Ω∫≈≥º±≈√", "resource/sharedUi/sel_skill.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("Ω∫ø“Ω∫≈≥", "resource/sharedUi/swap.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("≥Î≈œΩ∫≈≥", "resource/sharedUi/noturn.BMP", 60, 60, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("¿Øæ∆¿Ã", "resource/dungeon/UI/D_under_ui2.BMP", 1280, 240, false);
	ImageManager::GetSingleton()->AddImage("º±≈√æ∆¿Ãƒ‹", "resource/sharedUi/selected_2-down.BMP", 236, 412, 1, 2, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("≈∏∞Ÿæ∆¿Ãƒ‹", "resource/sharedUi/target.BMP", 197, 412, 1, 2, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("»˙æ∆¿Ãƒ‹", "resource/sharedUi/target_h.BMP", 175, 206, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("πÃ¥œ∏ πË∞Ê", "resource/sharedUi/downpanelmap.BMP", 480, 240, false);
	ImageManager::GetSingleton()->AddImage("√º∑¬πŸ", "resource/sharedUi/healthBar.BMP", 100, 10, false);
	ImageManager::GetSingleton()->AddImage("√º∑¬πŸπË∞Ê", "resource/sharedUi/healthBarBG.BMP", 100, 10, false);
	ImageManager::GetSingleton()->AddImage("≈œ∆Ω", "resource/sharedUi/turntick.BMP", 24, 27, true,RGB(255,0,255));
	ImageManager::GetSingleton()->AddImage("√º∑¬ƒ≠", "resource/sharedUi/health_pip.BMP", 8, 10, false);
	ImageManager::GetSingleton()->AddImage("πÃ¥œ∏ πË∞Êªˆ", "resource/mapui/mapbg.BMP", 1000, 1000, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("π´∫˘∑Î", "resource/mapui/movingrooom.BMP", 30, 30, 1, 1, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("πÊπÆ∑Î", "resource/mapui/roomvisited.BMP", 30, 30, 1, 1, true, RGB(88,88, 88));
	ImageManager::GetSingleton()->AddImage("πÊπÆ≈Î∑Œ", "resource/mapui/pathvisited.BMP", 20, 20, 1, 1, true, RGB(88, 88, 88));


	ImageManager::GetSingleton()->AddImage("∆–πË", "resource/sharedUi/scene/defeat.BMP", WINSIZE_X, WINSIZE_Y, false);
	ImageManager::GetSingleton()->AddImage("∑Œµ˘", "resource/sharedUi/scene/loding.BMP", WINSIZE_X, WINSIZE_Y, false);

	ImageManager::GetSingleton()->AddImage("»˙æ∆¿Ãƒ‹", "resource/sharedUi/fx/heal.BMP", 24, 24, true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("Ω∫≈œæ∆¿Ãƒ‹", "resource/sharedUi/fx/stun.BMP", 24, 24, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("∏∂≈©æ∆¿Ãƒ‹", "resource/sharedUi/fx/target.BMP", 24, 24, true, RGB(88, 88, 88));
	ImageManager::GetSingleton()->AddImage("»˙¿Ã∆Â∆Æ", "resource/sharedUi/fx/curefx.BMP", 7392, 493,22,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("Ω∫≈œ¿Ã∆Â∆Æ", "resource/sharedUi/fx/stunfx.BMP", 2210, 169,13,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("¡◊¿Ω¿Ã∆Â∆Æ", "resource/sharedUi/fx/deathfx.BMP", 6253, 481,22,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("««∞›¿Ã∆Â∆Æø¿", "resource/sharedUi/fx/hurtfx.BMP", 12519, 721,13,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("««∞›¿Ã∆Â∆Æøﬁ", "resource/sharedUi/fx/hurtfxL.BMP", 12519, 721,13,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("≈∏∞Ÿ¿Ã∆Â∆Æ", "resource/sharedUi/fx/marktarget.BMP", 6800, 369,17,1,true,RGB(88,88,88));
	ImageManager::GetSingleton()->AddImage("««¿Ã∆Â∆Æ", "resource/sharedUi/fx/blood.BMP", 6390, 292,18,1,true,RGB(88,88,88));

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
