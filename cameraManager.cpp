#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}

// 초기 세팅, _L, _T가 카메라의 LEFT, TOP
void cameraManager::setConfig(float L, float T, float width, float height, float minL, float minT, float maxL, float maxT)
{
	_L = L;
	_T = T;
	_width = width;
	_height = height;
	_originMinL = _minL = minL;
	_originMinT = _minT = minT;
	_originMaxL = _maxL = maxL;
	_originMaxT = _maxT = maxT;

	_x = _L + (_width / 2);
	_y = _T + (_height / 2);
	_originMinX = _minX = _minL + (_width / 2);
	_originMinY = _minY = _minT + (_height / 2);
	_originMaxX = _maxX = _maxL + (_width / 2);
	_originMaxY = _maxY = _maxT + (_height / 2);
}

void cameraManager::setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_originMinX = _minX = minX;
	_originMinY = _minY = minY;
	_originMaxX =_maxX = maxX;
	_originMaxY = _maxY = maxY;

	_L = _x - (width / 2);
	_T = _y - (height / 2);
	_originMinL = _minL = _minX - (width / 2);
	_originMinT = _minT = _minY - (height / 2);
	_originMaxL = _maxL = _maxX - (width / 2);
	_originMaxT = _maxT = _minY - (height / 2);
}

float cameraManager::getL()
{
	return _L;
}

float cameraManager::getT()
{
	return _T;
}

float cameraManager::getX()
{
	return _x;
}

float cameraManager::getY()
{
	return _y;
}

void cameraManager::setL(float newL)
{
	newL = min(_maxL, newL);
	newL = max(_minL, newL);
	_L = floor(newL);
	_x = _L + (_width / 2);
}

void cameraManager::setT(float newT)
{
	newT = min(_maxT, newT);
	newT = max(_minT, newT);
	_T = floor(newT);
	_y = _T + (_height / 2);
}

// 카메라의 기준점 X을 정함
void cameraManager::setX(float newX)
{
	newX = min(_maxX, newX);
	newX = max(_minX, newX);
	_x = floor(newX);
	_L = _x - (_width / 2);
}

// 카메라의 기준점 Y을 정함
void cameraManager::setY(float newY)
{
	newY = min(_maxY, newY);
	newY = max(_minY, newY);
	_y = floor(newY);
	_T = _y - (_height / 2);
}

// 카메라의 기준점을 이동시킴
void cameraManager::movePivot(float offsetX, float offsetY)
{
	setL(_L + offsetX);
	setT(_T + offsetY);
	setX(_x + offsetX);
	setY(_y + offsetY);
}

// 카메라의 LEFT를 기준으로 상대좌표 left값을 구함
float cameraManager::getRelativeL(float left)
{
	float newL = left - _L;
	return newL;
}

LONG cameraManager::getRelativeL(LONG left)
{
	LONG newL = left - _L;
	return newL;
}


// 카메라의 TOP을 기준으로 상대좌표 top값을 구함
float cameraManager::getRelativeT(float top)
{
	float newT = top - _T;
	return  newT;
}

LONG cameraManager::getRelativeT(LONG top)
{
	LONG newT = top - _T;
	return  newT;
}

float cameraManager::getAbsoluteL(float left)
{
	float newL = _L + left;
	return newL;
}

LONG cameraManager::getAbsoluteL(LONG left)
{
	LONG newL = _L + left;
	return newL;
}

float cameraManager::getAbsoluteT(float top)
{
	float newT = _T + top;
	return newT;
}

LONG cameraManager::getAbsoluteT(LONG top)
{
	LONG newT = _T + top;
	return newT;
}

// 사각형 그리기 MYRECT 사용
void cameraManager::rectangle(HDC hdc, TTYONE_UTIL::MYRECT mrec)
{
	RECT rect = { getRelativeL(mrec.left), getRelativeT(mrec.top), getRelativeL(mrec.right), getRelativeT(mrec.bottom) };
	Rectangle(hdc, rect);
}

void cameraManager::rectangle(HDC hdc, RECT rec)
{
	RECT rect = { getRelativeL(rec.left), getRelativeT(rec.top), getRelativeL(rec.right), getRelativeT(rec.bottom) };
	Rectangle(hdc, rect);
}

// 동그라미 그리기 MYRECT 사용
void cameraManager::ellipse(HDC hdc, TTYONE_UTIL::MYRECT mrec)
{
	RECT rect = { getRelativeL(mrec.left), getRelativeT(mrec.top), getRelativeL(mrec.right), getRelativeT(mrec.bottom) };
	Ellipse(hdc, rect);
}

void cameraManager::ellipse(HDC hdc, RECT rec)
{
	RECT rect = { getRelativeL(rec.left), getRelativeT(rec.top), getRelativeL(rec.right), getRelativeT(rec.bottom) };
	Ellipse(hdc, rect);
}

void cameraManager::render(HDC hdc, image * img)
{
	float newL = getRelativeL(static_cast<float>(0));
	float newT = getRelativeT(static_cast<float>(0));
	if (img) img->render(hdc, newL, newT);
}

void cameraManager::render(HDC hdc, image * img, float destX, float destY)
{
	float newL = getRelativeL(destX);
	float newT = getRelativeT(destY);
	if (img) img->render(hdc, newL, newT);
}

void cameraManager::render(HDC hdc, image * img, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	float newL = getRelativeL(destX);
	float newT = getRelativeT(destY);
	if (img) img->render(hdc, newL, newT, sourX, sourY, sourWidth, sourHeight);
}

void cameraManager::render(HDC hdc, HDC originDC, float destX, float destY, float width, float height, bool trans, COLORREF rgb)
{
	float newL = getRelativeL(destX);
	float newT = getRelativeT(destY);
	if (trans)
	{
		TransparentBlt(hdc, newL, newT, width, height, originDC, 0, 0, width, height, rgb);
	}
	else
	{
		BitBlt(hdc, newL, newT, width, height, originDC, 0, 0, SRCCOPY);
	}
}

void cameraManager::loopRender(HDC hdc, image* img, RECT drawArea, int offSetX, int offSetY)
{
	RECT newRECT = { getRelativeL(drawArea.left), getRelativeT(drawArea.top), getRelativeL(drawArea.right) , getRelativeT(drawArea.bottom) };
	img->loopRender(hdc, newRECT, offSetX, offSetY);
}

void cameraManager::frameRender(HDC hdc, image * img, float destX, float destY)
{
	float newL = getRelativeL(destX);
	float newT = getRelativeT(destY);
	if (img) img->frameRender(hdc, newL, newT);
}

void cameraManager::frameRender(HDC hdc, image * img, float destX, float destY, int frameX, int frameY)
{
	float newL = getRelativeL(destX);
	float newT = getRelativeT(destY);
	if (img) img->frameRender(hdc, newL, newT, frameX, frameY);
}

void cameraManager::frameRender(HDC hdc, image* img, float destX, float destY, int frameX, int frameY, bool leftRightInverse)
{
	float newL = getRelativeL(destX);
	float newT = getRelativeT(destY);
	if (img) img->frameRender(hdc, newL, newT, frameX, frameY, leftRightInverse);
}

void cameraManager::aniRender(HDC hdc, image * img, int destX, int destY, animation * ani, bool leftRightInverse)
{
	float newL = getRelativeL(static_cast<float>(destX));
	float newT = getRelativeT(static_cast<float>(destY));

	img->render(hdc, newL, newT, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), leftRightInverse);
}

void cameraManager::zoom(HDC hdc, float ratio)
{
	if (ratio == 1) return;

	float newWidth = (float)_width / ratio;
	float newHeight = (float)_height / ratio;

	float widthDistance = (_width - newWidth) / 2;
	float heightDistance = (_height - newHeight) / 2;

	_minL = _originMinL - widthDistance;
	_maxL = _originMaxL + widthDistance;
	_minT = _originMinT - heightDistance;
	_maxT = _originMaxT + heightDistance;

	_minX = _originMinX - widthDistance;
	_maxX = _originMaxX + widthDistance;
	_minY = _originMinY - heightDistance;
	_maxY = _originMaxY + heightDistance;

	float zoomL = WINSIZEX / 2 - (newWidth / 2);
	float zoomT = WINSIZEY / 2 - (newHeight / 2);

	StretchBlt(hdc, 0, 0, _width, _height,
		hdc, zoomL, zoomT, newWidth, newHeight,
		SRCCOPY);
}
