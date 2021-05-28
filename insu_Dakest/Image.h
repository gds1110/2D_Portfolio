#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// 프로젝트 자체에 포함 시킬 이미지
		FILE,			// 외부에서 로드할 이미지
		EMPTY,			// 자체 생산 이미지
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// 리소스의 고유한 ID
		HDC hMemDC;			// 그리기를 주관하는 핸들
		HBITMAP hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int width;			// 이미지 가로 크기
		int height;			// 이미지 세로 크기
		BYTE loadType;		// 로드 타입

		// 알파블랜드
		HDC hBlendDC;
		HBITMAP hBlendBit;
		HBITMAP hOldBlendBit;

		HDC hAlphaDC;		// 알파 블랜더 DC
		HBITMAP hAlphamap;	// 이미지 정보
		HBITMAP hOldAlpha;	// 기존 이미지 정보

		// 애니메이션 관련 (프레임데이터)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			hBlendDC = NULL;
			hBlendBit = NULL;
			hOldBlendBit = NULL;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;		// 이미지 정보 구조체 포인터
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

	BLENDFUNCTION blendFunc;

public:
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 화면에 출력
	void Render(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false);
	void Render2(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false, float size = 1);
	void FrameRender(HDC hdc, int destX, int destY,
		int currFrameX, int currFrameY, bool isCenterRenderring = false, float size = 1);
	void AlphaRender(HDC hdc, int destX, int destY,
		bool isCenterRenderring = false);
	void AlphaFrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring = true, float size=1);
	void AlphaFrameRenders(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring = true, float size = 1,int Alphas=255);

	void Render3(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false, float size = 1, int posX = 0, int posY = 0, int sizeX = 0,int sizeY=0,bool battle=false);
	void Render4(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false, float size = 1, POINT minP = { 0 }, POINT maxP = { 0 }, int sizeX = 0, int sizeY = 0);

	void Render5(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false, float size = 1, POINT minP = { 0 }, POINT maxP = { 0 }, int sizeX = 0, int sizeY = 0);

	void Render6(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false, float size = 1, POINT minP = { 0 }, POINT maxP = { 0 }, int sizeX = 0, int sizeY = 0,Tile* tile=nullptr);

	void Release();

	// get, set
	HDC GetMemDC()
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}

	BLENDFUNCTION* GetBlendFunc() { return &(this->blendFunc); }

	int GetWidth() { return this->imageInfo->width; }
	int GetHeight() { return this->imageInfo->height; }
	int GetFrameWidth() { return this->imageInfo->frameWidth; }
	int GetFrameHeight() { return this->imageInfo->frameHeight; }

	IMAGE_INFO* const  GetImageInfo() { return this->imageInfo; }
};

