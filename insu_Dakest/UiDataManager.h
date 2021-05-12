#pragma once
#include "config.h"
#include "Singleton.h"

class Character;
class UiDataManager : public Singleton<UiDataManager>
{
private:
	Character* selectedChr;


public:
	HRESULT Init();
	void Release();
	void Update();


	void SelectChar(Character* select) { this->selectedChr = select; }
	Character* GetSelectedChar() { if (selectedChr) { return this->selectedChr; } }
	
};

