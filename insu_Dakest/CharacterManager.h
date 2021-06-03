#pragma once
#include "GameNode.h"
#include <vector>

class Image;
class Character;
class CharacterManager : public GameNode
{
private:
	vector<Character*> v_Characters;
	vector<Character*>::iterator itChr;
	
	int index;
	int CharArrPos[4] = { 640,440,240,40 };
	float timers;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual HRESULT Init(int num);

	template <class ForwardIt1, class ForwardIt2>
	constexpr void iter_swap(ForwardIt1 a, ForwardIt2 b);

	vector<Character*> GetCharacters() { return this->v_Characters; }
	vector<Character*>* GetCharactersPointer() { return &(this->v_Characters); }

	void AddCharacter(Character* chr, UnitType type= UnitType::HERO);
	void AddCharacter2(Character* chr, int indexx, bool isroster = false, UnitType type = UnitType::HERO);
	//void AddCharacter(UnitType type,int CharIndex);
	void AddMonster(int charIndex);
	int GetCharPos();
	
	virtual ~CharacterManager() {};

};

template<class ForwardIt1, class ForwardIt2>
inline constexpr void CharacterManager::iter_swap(ForwardIt1 a, ForwardIt2 b)
{
	using std::swap;
	swap(*a, *b);
}
