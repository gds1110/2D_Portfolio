#include "Image.h"
#include "MapGenManager.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = 
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;


    imageInfo->hAlphaDC = CreateCompatibleDC(hdc);
    imageInfo->hAlphamap = CreateCompatibleBitmap(hdc, imageInfo->width, imageInfo->height);
    imageInfo->hOldAlpha = (HBITMAP)(SelectObject(imageInfo->hAlphaDC, imageInfo->hAlphamap));


    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = FALSE;
    this->transColor = FALSE;

    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height,
    bool isTransparent/* = FALSE*/, COLORREF transColor/* = FALSE*/)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = 
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    // ���� ����
    imageInfo->hBlendDC = CreateCompatibleDC(hdc);
    imageInfo->hBlendBit = CreateCompatibleBitmap(hdc, 
        imageInfo->width, imageInfo->height);
    imageInfo->hOldBlendBit = (HBITMAP)SelectObject(imageInfo->hBlendDC, 
        imageInfo->hBlendBit);

    imageInfo->hAlphaDC = CreateCompatibleDC(hdc);
    imageInfo->hAlphamap = CreateCompatibleBitmap(hdc, imageInfo->width, imageInfo->height);
    imageInfo->hOldAlpha = (HBITMAP)(SelectObject(imageInfo->hAlphaDC, imageInfo->hAlphamap));



    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap =
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;


    imageInfo->hAlphaDC = CreateCompatibleDC(hdc);
    imageInfo->hAlphamap = CreateCompatibleBitmap(hdc, imageInfo->width, imageInfo->height);
    imageInfo->hOldAlpha = (HBITMAP)(SelectObject(imageInfo->hAlphaDC, imageInfo->hAlphamap));


    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;


    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;


    return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        BitBlt(
            hdc,                // ���� ������ DC
            x, y,               // ���� ���� ��ġ
            imageInfo->width,   // �������� ����� ����ũ��
            imageInfo->height,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );     
    }

  
}

void Image::MinimapRender(HDC hdc, int destX, int destY, Tile* currTile, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        //BitBlt(
        //    hdc,                // ���� ������ DC
        //    x, y,               // ���� ���� ��ġ
        //    imageInfo->width,   // �������� ����� ����ũ��
        //    imageInfo->height,  // �������� ����� ����ũ��
        //    imageInfo->hMemDC,  // ���� DC
        //    0, 0,               // �������� ���� ���� ��ġ
        //    SRCCOPY             // ���� �ɼ�
        //);
        GdiTransparentBlt(
            imageInfo->hMemDC,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
        StretchBlt(
            hdc,
            x, y,
            430,
            200,
            imageInfo->hMemDC,
            currTile->getPos().x-215,//-215
            currTile->getPos().y-100,//-100,
            //hdc,
            /*minP.x * TILE_SIZE,
            minP.y * TILE_SIZE,*/
            //(maxP.x+1 - minP.x) * TILE_SIZE , (maxP.y+1 - minP.y) * TILE_SIZE,
            430,
            200,
            SRCCOPY);


    }

}

void Image::Render2(HDC hdc, int destX, int destY, bool isCenterRenderring, float size)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width * size, imageInfo->height * size,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        if (size > 0)
        {
            StretchBlt(hdc,
                x, y,
                imageInfo->width*size, imageInfo->height*size,
                imageInfo->hMemDC,
                0,
                0,
                imageInfo->width, imageInfo->height,

                SRCCOPY);
        }
        else
        {
            // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
            BitBlt(
                hdc,                // ���� ������ DC
                x, y,               // ���� ���� ��ġ
                imageInfo->width,   // �������� ����� ����ũ��
                imageInfo->height,  // �������� ����� ����ũ��
                imageInfo->hMemDC,  // ���� DC
                0, 0,               // �������� ���� ���� ��ġ
                SRCCOPY             // ���� �ɼ�
            );
        }
    }


}


void Image::Render3(HDC hdc, int destX, int destY, bool isCenterRenderring, float size, int posX, int posY, int sizeX, int sizeY, bool battle)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        if (size > 0)
        {
            if (battle)
            {
                StretchBlt(hdc,
                    x, y,
                    imageInfo->width * size, imageInfo->height * size,
                    imageInfo->hMemDC,
                    0,
                    0,
                    imageInfo->width, imageInfo->height,

                    SRCCOPY);
            }
            else {
                StretchBlt(hdc,
                    x, y,
                    imageInfo->width + 100 * size, imageInfo->height * size,
                    imageInfo->hMemDC,
                    0,
                    0,
                    imageInfo->width, imageInfo->height,

                    SRCCOPY);
            }
        }
        else
        {
            // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
            BitBlt(
                hdc,                // ���� ������ DC
                x, y,               // ���� ���� ��ġ
                imageInfo->width,   // �������� ����� ����ũ��
                imageInfo->height,  // �������� ����� ����ũ��
                imageInfo->hMemDC,  // ���� DC
                0, 0,               // �������� ���� ���� ��ġ
                SRCCOPY             // ���� �ɼ�
            );
        }
    }
}
void Image::FrameRender(HDC hdc, int destX, int destY,
    int currFrameX, int currFrameY, bool isCenterRenderring, float size)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->frameWidth / 2);
        y = destY - (imageInfo->frameHeight / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,                // ������ DC
            x, y,               // ���� ��ġ
            imageInfo->frameWidth * size,
            imageInfo->frameHeight * size,  // ���� ũ��

            imageInfo->hMemDC,  // ���� DC
            imageInfo->frameWidth * imageInfo->currFrameX,  // ���� X ��ġ
            imageInfo->frameHeight * imageInfo->currFrameY, // ���� Y ��ġ
            imageInfo->frameWidth, imageInfo->frameHeight,  // ���� ũ��
            transColor  // ������ ����
        );
    }
    else
    {
        if (size > 1)
        {
            StretchBlt(hdc,
                x, y,
                imageInfo->frameWidth * size,
                imageInfo->frameHeight * size,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY);        
        }       
        else
        {
            BitBlt(
                hdc,
                x, y,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                SRCCOPY
            );
        }
    }
}

void Image::AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    // 1. ������ DC(hdc)�� �׷��� �ִ� ������ BlendDC�� ����
    BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
        hdc, x, y, SRCCOPY);

    //GdiTransparentBlt(imageInfo->)

    // 2. ����� �̹��� DC�� ������ BlendDC�� ������ ������ �����ϸ鼭 ����


    // 3.
    AlphaBlend(hdc, x, y, imageInfo->width, imageInfo->height,
        imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);



}

void Image::AlphaFrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring, float size)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

        // 1. ������ DC�� �ִ� ������ blendDC�� ����
  
    if (size > 1)
    {
        StretchBlt(imageInfo->hAlphaDC,
            0, 0,
            imageInfo->frameWidth * size,
            imageInfo->frameHeight * size,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth,
            imageInfo->frameHeight,
            SRCCOPY);
    }
    else
    {
        BitBlt(imageInfo->hAlphaDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, hdc, x, y, SRCCOPY);

    }



    //2. ����� �̹��� DC�� �ִ� ������ BlendDC�� ������ ������ �����ϸ鼭 ����
    GdiTransparentBlt(imageInfo->hAlphaDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, imageInfo->hMemDC, imageInfo->frameWidth * imageInfo->currFrameX, imageInfo->frameHeight * imageInfo->currFrameY, imageInfo->frameWidth, imageInfo->frameHeight, transColor);
    // 3. ���
    AlphaBlend(hdc, x, y, imageInfo->frameWidth, imageInfo->frameHeight, imageInfo->hAlphaDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, blendFunc);

}

void Image::AlphaFrameRenders(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring, float size, int Alphas)
{

    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    // 1. ������ DC�� �ִ� ������ blendDC�� ����

    if (size > 1)
    {
        StretchBlt(imageInfo->hAlphaDC,
            0, 0,
            imageInfo->frameWidth * size,
            imageInfo->frameHeight * size,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth,
            imageInfo->frameHeight,
            SRCCOPY);
    }
    else
    {
        BitBlt(imageInfo->hAlphaDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, hdc, x, y, SRCCOPY);

    }



    //2. ����� �̹��� DC�� �ִ� ������ BlendDC�� ������ ������ �����ϸ鼭 ����
    GdiTransparentBlt(imageInfo->hAlphaDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, imageInfo->hMemDC, imageInfo->frameWidth * imageInfo->currFrameX, imageInfo->frameHeight * imageInfo->currFrameY, imageInfo->frameWidth, imageInfo->frameHeight, transColor);
    // 3. ���

    blendFunc.SourceConstantAlpha = Alphas;
    AlphaBlend(hdc, x, y, imageInfo->frameWidth, imageInfo->frameHeight, imageInfo->hAlphaDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, blendFunc);
}


void Image::Render4(HDC hdc, int destX, int destY, bool isCenterRenderring, float size, POINT minP, POINT maxP, int sizeX, int sizeY)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            minP.x, minP.y,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        //int maximum = max(maxP.x, maxP.y);
        //float XX = maximum;

        //float WidthSize = ((maxP.x - minP.x) * TILE_SIZE);
        //float HeightSize = ((maxP.y - minP.y) * TILE_SIZE);
        //float offsetx = 1.0f;
        //float offsety = 1.0f;

        //if (WidthSize > 440/*|| WidthSize < 440*/) {
        //   // offsetx = (WidthSize / 440) * 100;
        //    offsetx = (440 / WidthSize);
        //    //WidthSize *= offsetx;
        //   // HeightSize = (HeightSize / 440) * 100;

        //}
        ///* if () {

        //    offsetx = (440 / WidthSize);
        //}*/
        // if (HeightSize > 230/*|| HeightSize < 230*/)
        //{
        //   // HeightSize = (HeightSize / (WINSIZE_Y / 3)) * 100;

        //    //offsety = (HeightSize / 240) * 100;
        //    offsety = ( 230/HeightSize);
        //    //HeightSize *= offsety;
        //    //WidthSize = (WidthSize / (WINSIZE_Y / 3)) * 100;

        //}
        //  // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        //StretchBlt(
        //    hdc,
        //    x, y,
        //    //imageInfo->width * size, imageInfo->height * size,
        //    (WidthSize) *size* offsetx, (HeightSize)* size* offsety,
        //    //440,(WINSIZE_Y/3),
        //    imageInfo->hMemDC,
        //    //hdc,
        //    minP.x * TILE_SIZE,
        //    minP.y * TILE_SIZE,
        //    (maxP.x+1 - minP.x) * TILE_SIZE , (maxP.y+1 - minP.y) * TILE_SIZE,

        //    SRCCOPY);
        BitBlt(
            //imageInfo->hMemDC,                // ���� ������ DC
            imageInfo->hMemDC,
            0, 0,               // ���� ���� ��ġ
            (maxP.x + 1 - minP.x) * TILE_SIZE,   // �������� ����� ����ũ��
            (maxP.y + 1 - minP.y) * TILE_SIZE,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            minP.x * TILE_SIZE, minP.y * TILE_SIZE,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );

        BitBlt(
            //imageInfo->hMemDC,                // ���� ������ DC
            hdc,
            x, y,               // ���� ���� ��ġ
            (maxP.x + 1 - minP.x) * TILE_SIZE,   // �������� ����� ����ũ��
            (maxP.y + 1 - minP.y) * TILE_SIZE,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );
        //BitBlt(
        //    //imageInfo->hMemDC,                // ���� ������ DC
        //    hdc,
        //    x, y,               // ���� ���� ��ġ
        //    (maxP.x + 1 - minP.x) * TILE_SIZE,   // �������� ����� ����ũ��
        //    (maxP.y + 1 - minP.y) * TILE_SIZE,  // �������� ����� ����ũ��
        //    imageInfo->hMemDC,  // ���� DC
        //    minP.x * TILE_SIZE, minP.y * TILE_SIZE,               // �������� ���� ���� ��ġ
        //    SRCCOPY             // ���� �ɼ�
        //);

    }
}

void Image::Render5(HDC hdc, int destX, int destY, bool isCenterRenderring, float size, POINT minP, POINT maxP, int sizeX, int sizeY)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            minP.x, minP.y,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        //int maximum = max(maxP.x, maxP.y);
        //float XX = maximum;

        //float WidthSize = ((maxP.x - minP.x) * TILE_SIZE);
        //float HeightSize = ((maxP.y - minP.y) * TILE_SIZE);
        //float offsetx = 1.0f;
        //float offsety = 1.0f;

        //if (WidthSize > 440/*|| WidthSize < 440*/) {
        //   // offsetx = (WidthSize / 440) * 100;
        //    offsetx = (440 / WidthSize);
        //    //WidthSize *= offsetx;
        //   // HeightSize = (HeightSize / 440) * 100;

        //}
        ///* if () {

        //    offsetx = (440 / WidthSize);
        //}*/
        // if (HeightSize > 230/*|| HeightSize < 230*/)
        //{
        //   // HeightSize = (HeightSize / (WINSIZE_Y / 3)) * 100;

        //    //offsety = (HeightSize / 240) * 100;
        //    offsety = ( 230/HeightSize);
        //    //HeightSize *= offsety;
        //    //WidthSize = (WidthSize / (WINSIZE_Y / 3)) * 100;

        //}
        //  // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����


        StretchBlt(
            hdc,
            x, y,
            //imageInfo->width * size, imageInfo->height * size,
            //440,320,
            //440,(WINSIZE_Y/3),
            //(maxP.x + 1 - minP.x) * TILE_SIZE, (maxP.y + 1 - minP.y) * TILE_SIZE,
            430,
            200,
            imageInfo->hMemDC,
            //hdc,
            minP.x * TILE_SIZE,
            minP.y * TILE_SIZE,
            //(maxP.x+1 - minP.x) * TILE_SIZE , (maxP.y+1 - minP.y) * TILE_SIZE,
            430,
            200,
            SRCCOPY);
      

        //BitBlt(
        //    //imageInfo->hMemDC,                // ���� ������ DC
        //    hdc,
        //    x, y,               // ���� ���� ��ġ
        //    (maxP.x + 1 - minP.x) * TILE_SIZE,   // �������� ����� ����ũ��
        //    (maxP.y + 1 - minP.y) * TILE_SIZE,  // �������� ����� ����ũ��
        //    imageInfo->hMemDC,  // ���� DC
        //    0, 0,               // �������� ���� ���� ��ġ
        //    SRCCOPY             // ���� �ɼ�
        //);
        //BitBlt(
        //    //imageInfo->hMemDC,                // ���� ������ DC
        //    hdc,
        //    x, y,               // ���� ���� ��ġ
        //    (maxP.x + 1 - minP.x) * TILE_SIZE,   // �������� ����� ����ũ��
        //    (maxP.y + 1 - minP.y) * TILE_SIZE,  // �������� ����� ����ũ��
        //    imageInfo->hMemDC,  // ���� DC
        //    minP.x * TILE_SIZE, minP.y * TILE_SIZE,               // �������� ���� ���� ��ġ
        //    SRCCOPY             // ���� �ɼ�
        //);

    }
}

void Image::Render6(HDC hdc, int destX, int destY, bool isCenterRenderring, float size, POINT minP, POINT maxP, int sizeX, int sizeY, Tile* tile)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2);
        y = destY - (imageInfo->height / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            minP.x, minP.y,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        /*GdiTransparentBlt(
            imageInfo->hMemDC,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            minP.x, minP.y,
            imageInfo->width, imageInfo->height,
            RGB(255, 255, 255)
        );
*/

        StretchBlt(
            hdc,
            x, y,
            430,
            200,
            imageInfo->hMemDC,
            tile->GetIdX()*TILE_SIZE,//-215,
            tile->GetIdY()*TILE_SIZE,//-100,
            //hdc,
            /*minP.x * TILE_SIZE,
            minP.y * TILE_SIZE,*/
            //(maxP.x+1 - minP.x) * TILE_SIZE , (maxP.y+1 - minP.y) * TILE_SIZE,
            516,
            240,
            SRCCOPY);


      

    }
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        if (imageInfo->hBlendDC != NULL)
        {
            SelectObject(imageInfo->hBlendDC, imageInfo->hOldBlendBit);
            DeleteObject(imageInfo->hBlendBit);
            DeleteDC(imageInfo->hBlendDC);
        }

        delete imageInfo;
        imageInfo = nullptr;
    }
}
