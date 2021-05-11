#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Character;
class CharacterManager : public GameNode
{
private:
	vector<Character*> v_Heros;
	vector<Character*>::iterator itHero;
	int index;
	//int posarray[4] = { 100,200,375,500 };
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual HRESULT Init(int num);

	template <class It1, class It2>
	constexpr void swaps(It1 chr1, It2 chr2);

	void AddHero(Character* chr);
	int GetHeroPos();

	virtual ~CharacterManager() {};

};

template<class It1, class It2>
constexpr void CharacterManager::swaps(It1 chr1, It2 chr2)
{

	using std::swap;
	swap((chr1), (chr2));
}
