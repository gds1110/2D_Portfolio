#pragma once
#include "GameNode.h"

class Image;
class Character : public GameNode
{
protected:
	enum State
	{
		IDLE,
		WALK,
		COMBAT,
		NONE
	};

private:




public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void SetPos(int num) {};
	virtual int GetPosx() { return 0; };

	virtual ~Character() {};
};

