#include "stdafx.h"
#include "image.h"

//#pragma <- �����Ϸ� ���ñ�
#pragma comment(lib, "msimg32.lib")

//��� �̴ϼȶ�����
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//����ó��
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ������ �����ؼ� ����۰� NULL�̸�
	if (_imageInfo == NULL)
	{
		//�޸� ���� ��
		release();

		//�����ߴ� �޼����� ȣ���ض�
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//�̹��� ������ Ȥ�ó� �����ִٸ� �����ض�
	if (_imageInfo != NULL) release();

	//DC������ ������ ����ϰ� ������
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC���� �ϳ� ����
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//��Ʈ�� ������ ������ ���� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�̹��� ������ Ȥ�ó� �����ִٸ� �����ض�
	if (_imageInfo != NULL) release();

	//DC������ ������ ����ϰ� ������
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC���� �ϳ� ����
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//��Ʈ�� ������ ������ ���� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�̹��� ������ Ȥ�ó� �����ִٸ� �����ض�
	if (_imageInfo != NULL) release();

	//DC������ ������ ����ϰ� ������
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC���� �ϳ� ����
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//��Ʈ�� ������ ������ ���� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ���� DC
			_imageInfo->x,					//����� ��ǥ X
			_imageInfo->y,					//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			0, 0,					//�����ؿ� ��ǥ X,Y
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_transColor);			//�����Ҷ� ������ �ȼ���
	}
	else
	{
		//DC���� ���� ��Ӻ��縦 ���ִ� �Լ� BitBlt
		BitBlt(hdc,					//������ DC
			_imageInfo->x,			//������ X��ǥ(left)
			_imageInfo->y,			//������ Y��ǥ(top)
			_imageInfo->width,		//������ ũ��
			_imageInfo->height,		//������ ũ��
			_imageInfo->hMemDC,		//����� DC
			0, 0,					//����� X,Y(left, top)
			SRCCOPY);				//�������� �����ϰڴ�
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ���� DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			0, 0,					//�����ؿ� ��ǥ X,Y
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_transColor);			//�����Ҷ� ������ �ȼ���
	}
	else
	{
		//DC���� ���� ��Ӻ��縦 ���ִ� �Լ� BitBlt
		BitBlt(hdc,					//������ DC
			destX,					//������ X��ǥ(left)
			destY,					//������ Y��ǥ(top)
			_imageInfo->width,		//������ ũ��
			_imageInfo->height,	//������ ũ��
			_imageInfo->hMemDC,	//����� DC
			0, 0,					//����� X,Y(left, top)
			SRCCOPY);				//�������� �����ϰڴ�
	}


}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ���� DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			sourWidth,				//����� ũ�� (����)
			sourHeight,				//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			sourX, sourY,			//�����ؿ� ��ǥ X,Y
			sourWidth,				//������ ����ũ��
			sourHeight,				//������ ����ũ��
			_transColor);			//�����Ҷ� ������ �ȼ���
	}
	else
	{
		//DC���� ���� ��Ӻ��縦 ���ִ� �Լ� BitBlt
		BitBlt(hdc,					//������ DC
			destX,					//������ X��ǥ(left)
			destY,					//������ Y��ǥ(top)
			sourWidth,				//������ ũ��
			sourHeight,				//������ ũ��
			_imageInfo->hMemDC,		//����� DC
			sourX, sourY,			//����� X,Y(left, top)
			SRCCOPY);				//�������� �����ϰڴ�
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, bool leftRightInverse)
{
	if (_trans)
	{
		if (leftRightInverse)
		{
			HDC tempDc = CreateCompatibleDC(_imageInfo->hMemDC);
			HBITMAP tempBitMap = CreateCompatibleBitmap(_imageInfo->hMemDC, sourWidth, sourHeight);
			HBITMAP origin = static_cast<HBITMAP>(SelectObject(tempDc, tempBitMap));

			StretchBlt(
				tempDc,					//����� ���� DC
				sourWidth - 1,					//����� ��ǥ X
				0,					//����� ��ǥ Y
				-sourWidth,				//����� ũ�� (����)
				sourHeight,				//����� ũ�� (����)
				_imageInfo->hMemDC,		//�����ؿ� DC
				sourX, sourY,			//�����ؿ� ��ǥ X,Y
				sourWidth,				//������ ����ũ��
				sourHeight,				//������ ����ũ��
				SRCCOPY);			//�����Ҷ� ������ �ȼ���

			GdiTransparentBlt(hdc, destX, destY, sourWidth, sourHeight,
				tempDc, 0, 0, sourWidth, sourHeight,
				_transColor);

			DeleteObject(tempBitMap);
			DeleteObject(tempDc);
			DeleteObject(origin);
		}
		else
		{
			GdiTransparentBlt(
				hdc,					//����� ���� DC
				destX,					//����� ��ǥ X
				destY,					//����� ��ǥ Y
				sourWidth,				//����� ũ�� (����)
				sourHeight,				//����� ũ�� (����)
				_imageInfo->hMemDC,		//�����ؿ� DC
				sourX, sourY,			//�����ؿ� ��ǥ X,Y
				sourWidth,				//������ ����ũ��
				sourHeight,				//������ ����ũ��
				_transColor);			//�����Ҷ� ������ �ȼ���
		}
	}
	else
	{
		if (leftRightInverse)
		{
			StretchBlt(hdc,							//������ DC
				destX + sourWidth,							//������ X��ǥ(left)
				destY,							//������ Y��ǥ(top)
				-sourWidth,			//������ ũ��
				sourHeight,		//������ ũ��
				_imageInfo->hMemDC,				//����� DC
				sourX,
				sourY,		//����� X,Y(left, top)
				sourWidth,								//������ ����ũ��
				sourHeight,							// ������ ���� ũ��
				SRCCOPY);				//�������� �����ϰڴ�
		}
		else
		{
			//DC���� ���� ��Ӻ��縦 ���ִ� �Լ� BitBlt
			BitBlt(hdc,					//������ DC
				destX,					//������ X��ǥ(left)
				destY,					//������ Y��ǥ(top)
				sourWidth,				//������ ũ��
				sourHeight,				//������ ũ��
				_imageInfo->hMemDC,		//����� DC
				sourX, sourY,			//����� X,Y(left, top)
				SRCCOPY);				//�������� �����ϰڴ�
		}
	}

}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ���� DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			_imageInfo->frameWidth,	//����� ũ�� (����)
			_imageInfo->frameHeight,//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//�����ؿ� ��ǥ X,Y
			_imageInfo->frameWidth,								//������ ����ũ��
			_imageInfo->frameHeight,							//������ ����ũ��
			_transColor);			//�����Ҷ� ������ �ȼ���
	}
	else
	{
		//DC���� ���� ��Ӻ��縦 ���ִ� �Լ� BitBlt
		BitBlt(hdc,							//������ DC
			destX,							//������ X��ǥ(left)
			destY,							//������ Y��ǥ(top)
			_imageInfo->frameWidth,			//������ ũ��
			_imageInfo->frameHeight,		//������ ũ��
			_imageInfo->hMemDC,				//����� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//����� X,Y(left, top)
			SRCCOPY);				//�������� �����ϰڴ�
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ���� DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			_imageInfo->frameWidth,	//����� ũ�� (����)
			_imageInfo->frameHeight,//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//�����ؿ� ��ǥ X,Y
			_imageInfo->frameWidth,								//������ ����ũ��
			_imageInfo->frameHeight,							//������ ����ũ��
			_transColor);			//�����Ҷ� ������ �ȼ���
	}
	else
	{
		//DC���� ���� ��Ӻ��縦 ���ִ� �Լ� BitBlt
		BitBlt(hdc,							//������ DC
			destX,							//������ X��ǥ(left)
			destY,							//������ Y��ǥ(top)
			_imageInfo->frameWidth,			//������ ũ��
			_imageInfo->frameHeight,		//������ ũ��
			_imageInfo->hMemDC,				//����� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//����� X,Y(left, top)
			SRCCOPY);				//�������� �����ϰڴ�
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, bool leftRightInverse)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	float sourWidth = _imageInfo->frameWidth;
	float sourHeight = _imageInfo->frameHeight;
	float sourX = _imageInfo->currentFrameX * _imageInfo->frameWidth;
	float sourY = _imageInfo->currentFrameY * _imageInfo->frameHeight;

	render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, leftRightInverse);
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//������ ����ó���� �Ҷ� ������ �����ڸ� �� �̿��սô�
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;					//�׷��� ���� left
	int drawAreaY = drawArea->top;					//�׷��� ���� top
	int drawAreaW = drawArea->right - drawAreaX;	//�׷��� ���� width
	int drawAreaH = drawArea->bottom - drawAreaY;	//�׷��� ���� height

	//���κ���
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ�� �� ���� ���� Ȯ��
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}


		//ȭ������� ����������ŭ�� �����Ѵ�
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::loopRender(HDC hdc, RECT drawArea, int offSetX, int offSetY)
{
	//������ ����ó���� �Ҷ� ������ �����ڸ� �� �̿��սô�
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea.left;					//�׷��� ���� left
	int drawAreaY = drawArea.top;					//�׷��� ���� top
	int drawAreaW = drawArea.right - drawAreaX;	//�׷��� ���� width
	int drawAreaH = drawArea.bottom - drawAreaY;	//�׷��� ���� height

	//���κ���
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ�� �� ���� ���� Ȯ��
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}


		//ȭ������� ����������ŭ�� �����Ѵ�
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		// 1. ���� hdc �׸� ���� -> blendImage
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		// 2. hMemDC�� �̹��� �׸���(���� ó��)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		// 3. ���� ������ ó���ؼ� �̹��� hdc�� �׸��� (hMemDC�� blt�� transparent ���󰡼� �̹����� �׷�����)
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}
}

void image::alphaRedRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	HDC tempDC = CreateCompatibleDC(_imageInfo->hMemDC);
	HBITMAP tempBitMap = CreateCompatibleBitmap(_imageInfo->hMemDC, _imageInfo->width, _imageInfo->height);
	HBITMAP tempOrigin = static_cast<HBITMAP>(SelectObject(tempDC, tempBitMap));

	HDC redDC = CreateCompatibleDC(_imageInfo->hMemDC);
	HBITMAP redBitMap = CreateCompatibleBitmap(_imageInfo->hMemDC, _imageInfo->width, _imageInfo->height);
	HBITMAP redOrigin = static_cast<HBITMAP>(SelectObject(redDC, redBitMap));

	if (_trans)
	{
		// 1. redDC�� ������ DC ���� (bitblt : IMAGE_MANAGER(origin redDC) -> redDC)
		// 2. tempDC�� ������ DC ���� (bitblt : redDC -> tempDC)
		// 3. tempDC�� ĳ���� �׸���(transparent(RGB(255, 0, 255)) : imageDC -> tempDC)
		// 4. redDC�� alpharender�� �׸��� (alphaBlend : tempDC -> redDC) 
		// 5. ���� �׸����� DC�� �̹��� �׸���(transparent(255, 0, 0) : redDC -> hdc)

		BitBlt(redDC, 0, 0, _imageInfo->width, _imageInfo->height,
			IMAGEMANAGER->findImage("redDC")->getMemDC(), 0, 0, SRCCOPY);

		BitBlt(tempDC, 0, 0, _imageInfo->width, _imageInfo->height,
			redDC, 0, 0, SRCCOPY);

		GdiTransparentBlt(tempDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(redDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			tempDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);

		GdiTransparentBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			redDC, 0, 0, _imageInfo->width, _imageInfo->height, RGB(255, 0, 0));
	}
	else // ����� ���� ���߽��ϴ�.
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}

	DeleteObject(tempDC);
	DeleteObject(tempBitMap);
	DeleteObject(tempOrigin);

	DeleteObject(redDC);
	DeleteObject(redBitMap);
	DeleteObject(redOrigin);
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ���� DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			sourWidth,				//����� ũ�� (����)
			sourHeight,				//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			sourX, sourY,			//�����ؿ� ��ǥ X,Y
			sourWidth,				//������ ����ũ��
			sourHeight,				//������ ����ũ��
			_transColor);			//�����Ҷ� ������ �ȼ���
	}
	else
	{
		//DC���� ���� ��Ӻ��縦 ���ִ� �Լ� BitBlt
		BitBlt(hdc,					//������ DC
			destX,					//������ X��ǥ(left)
			destY,					//������ Y��ǥ(top)
			sourWidth,				//������ ũ��
			sourHeight,				//������ ũ��
			_imageInfo->hMemDC,		//����� DC
			sourX, sourY,			//����� X,Y(left, top)
			SRCCOPY);				//�������� �����ϰڴ�
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC,  // origin DC
			0, // origin x
			0, // origin y
			_imageInfo->frameWidth, // origin width
			_imageInfo->frameHeight, // origin height
			hdc, // source DC
			destX, // source x
			destY,  // source y
			SRCCOPY);
		// ����� DC�� ���� DC�� �׸� ����

		GdiTransparentBlt(
			_blendImage->hMemDC,					// origin DC
			0,					// origin X
			0,					// origin Y
			_imageInfo->frameWidth,	// origin width
			_imageInfo->frameHeight,// origin height
			_imageInfo->hMemDC,		// source DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,  // source x
			_imageInfo->currentFrameY * _imageInfo->frameHeight, // source y
			_imageInfo->frameWidth,								// source width
			_imageInfo->frameHeight,							// source height
			_transColor);			// transparent RGB
		// ����� DC�� �̹��� �׸�(transparent RGB ����)

		AlphaBlend(hdc, // origin DC
			destX,  // origin x
			destY, // origin y
			_imageInfo->frameWidth, // origin width
			_imageInfo->frameHeight, // origin height
			_blendImage->hMemDC,  // source DC
			0,  // source x
			0,  // source y
			_imageInfo->frameWidth, // source width
			_imageInfo->frameHeight, // source height
			_blendFunc); // blend function
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, // origin width
			_imageInfo->frameHeight, // origin height
			_blendImage->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,  // source x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,  // source y
			_imageInfo->frameWidth, // source width
			_imageInfo->frameHeight, // source height
			_blendFunc);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{	
	int maxFrameX = getMaxFrameX();
	int maxFrameY = getMaxFrameY();
	int currentFrameX = 0;
	int currentFrameY = 0;

	for (int i = 0; i <= maxFrameX; i++)
	{
		if (ani->getFramePos().x == i * ani->getFrameWidth())
		{
			currentFrameX = i;
			break;
		}
	}
	for (int i = 0; i <= maxFrameY; i++)
	{
		if (ani->getFramePos().y == i * ani->getFrameHeight())
		{
			currentFrameY = i;
			break;
		}
	}

	alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}
